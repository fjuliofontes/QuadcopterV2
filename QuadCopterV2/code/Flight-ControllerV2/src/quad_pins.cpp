#include <quad_pins.h>
#include <Arduino.h>
#include <sysctl.h>
#include <eeprom.h>
#include <pin_map.h>

void quad_init(){
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    analogReadResolution(12);
}

float quad_readBatteryVoltage(){
    return analogRead(PD_3)*(14.355/4095.0);
}

void quad_redOn(){
    digitalWrite(GREEN_LED, 0);
    digitalWrite(BLUE_LED, 0);
    digitalWrite(RED_LED, 1);
}

void quad_greenOn(){
    digitalWrite(GREEN_LED, 1);
    digitalWrite(BLUE_LED, 0);
    digitalWrite(RED_LED, 0);
}

void quad_blueOn(){
    digitalWrite(GREEN_LED, 0);
    digitalWrite(BLUE_LED, 1);
    digitalWrite(RED_LED, 0);
}

void quad_ledOff(){
    digitalWrite(GREEN_LED, 0);
    digitalWrite(BLUE_LED, 0);
    digitalWrite(RED_LED, 0);
}

void quad_setColor(uint8_t red, uint8_t green, uint8_t blue){

}

void quad_blinkLed(uint32_t blink_rate, uint32_t blink_ms, uint8_t led){
    quad_ledOff();  

    unsigned long curr_time  = millis();
    unsigned long last_blink = millis();
    uint8_t state = 1;

    digitalWrite(led, state);
    
    while(millis() - curr_time < blink_ms){

        if(millis() - last_blink >= blink_rate){
            last_blink = millis();
            state = !state;
            digitalWrite(led, state);
        }

    }

}

void quad_led(uint8_t led, uint8_t state){
    digitalWrite(led,state);
}

uint8_t quad_init_eeprom(){
    uint32_t ui32EEPROMInit;
    //
    // Enable the EEPROM module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    //
    // Wait for the EEPROM module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0));
    //
    // Wait for the EEPROM Initialization to complete
    //
    ui32EEPROMInit = EEPROMInit();
    //
    // Check if the EEPROM Initialization returned an error
    // and inform the application
    //
    if(ui32EEPROMInit != EEPROM_INIT_OK) return QUAD_NOT_OK;

    return QUAD_OK;
}

uint8_t quad_write_eeprom(uint32_t addr, uint32_t * data, uint32_t len){
    uint32_t stored_data[len];
    //
    // Program some data into the EEPROM at address addr.
    //
    EEPROMProgram(data, addr, len);
    //
    // Read it back.
    //
    EEPROMRead(stored_data, addr, len);
    //
    // Check if data was correctly saved
    //
    for(uint32_t i = 0; i < len; i ++){
        if(data[i] != stored_data[i]) return QUAD_NOT_OK;
    }
    
    return QUAD_OK;
}

uint8_t quad_read_eeprom(uint32_t addr, uint32_t * data, uint32_t len){
    //
    // Read data
    //
    EEPROMRead(data, addr, len);
    
    return QUAD_OK;
}

uint8_t quad_eeprom_get_bytes_pear_block(){
    uint32_t eeprom_bytes = EEPROMSizeGet(); // size in bytes
    uint32_t eeprom_blocks = EEPROMBlockCountGet(); // get nr of blocks

    uint8_t eeprom_bytes_pear_block = (eeprom_bytes/eeprom_blocks);

    return eeprom_bytes_pear_block;
}

uint32_t quad_eeprom_get_size(){
    return EEPROMSizeGet(); // size in bytes
}


void quad_esc_motors_init(){
    /*This function enables the peripherals. It takes a value in the form of a pre-defined string found
    within sysctl.h. For the purposes of enabling PWM on the pins, SYSCTL_PERIPH_GPIOB is
    used to enable the B set of GPIO pins and SYSCTL_PERIPH_PWM0 is used to enable PWM0,
    which is the PWM module that can be used by the B and D GPIO pins.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    /*This function allows the default clock tied to the PWM to be divided. SYSCTL_PWMDIV_2
    would divide the clock by 2, SYSCTL_PWMDIV_4 would divide the clock by 4, etc.*/
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

    /*This function allows the lock placed on the pins of the GPIO module to be removed so that
    additional functionality may be used, in this case PWM. Without this, the pin will not be
    available for use by any other module besides the module it is linked with.*/

    //HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   
    //HWREG(GPIO_PORTB_BASE + GPIO_O_CR) |= 0x01;
    //HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   
    //HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x01;

    /*This function configures to use a specific pin on the PWM module. GPIO_PB6_M0PWM0 reads
    as GPIO pin B6, PWM module 0 pin 0. This ties the pin 0 output of the PWM module to the
    GPIO pin 6.*/
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    GPIOPinConfigure(GPIO_PD0_M0PWM6);
    GPIOPinConfigure(GPIO_PD1_M0PWM7);

    /*This function sets the functionality of the GPIO pin within the GPIO module. The “|” character is
    a logical OR. The pins relate to binary values. An example would be the values 1001 and 1010.
    The OR will choose a 1 if either value has a 1 in that position or a 0 if both are 0. For this
    example the output would be 1011. As this function only takes 1 value for multiple pins, the OR
    is required.*/
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* This function configures the PWM generator on the module. The generator creates the pulses
    needed for PWM output. PWM0_BASE is the base of the module being used. PWM_GEN_0 is
    the generator for the module tied to PMW pins 0 and 1, PWM_GEN_3 is for pins 6 and 7.
    PWM_GEN_MODE_DOWN counts the values for the generator down, creating a saw-tooth
    wave whereas PWM_GEN_MODE_UP_DOWN would create a triangle wave.
    PWM_GEN_MODE_NO_SYNC is used so that the generator gives immediate updates rather
    than synchronizing with the clock to update. */
    PWMGenConfigure(PWM0_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE,PWM_GEN_3,PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    /* This function sets the period of the PWM output. PWM0_BASE is the base of the module being
    used. PWM_GEN_0 is the generator for the module tied to PMW pins 0 and 1, PWM_GEN_3 is
    for pins 6 and 7. 25000 in this example is the period, measured in clock ticks. 25000 would be 25000
    clock ticks as a period which represents a period of 50Hz - 20ms. */
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 25000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 25000);

    /* This function sets the pulse width, or duty cycle of the output to the PWM pins. PWM0_BASE is
    the base of the module being used. PWM_OUT_0 is the PWM output to modify, which is tied to
    a pin. 12500 is the clock ticks of the width of the pulse. 12500 would be a 50% duty cycle for the 25000
    clock tick period. */
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1250); // throttle to zero
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1250);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1250);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1250);

    /*This function enables the PWM generator. Now that the previous values have been set, the
    generator may now be turned on. PWM0_BASE is the base of the module being used.
    PWM_GEN_0 is the generator for the module tied to PMW pins 0 and 1, PWM_GEN_3 is for
    pins 6 and 7. */
    PWMGenEnable(PWM0_BASE,PWM_GEN_0);
    PWMGenEnable(PWM0_BASE,PWM_GEN_3);

    /*This function enables the PWM module to start modify the pins set for PWM output. With all of
    the previous values set, the output to the physical pins of the microcontroller can be turned on.
    PWM0_BASE is the base of the module being used. PWM_OUT_0_BIT | PWM_OUT_1_BIT |
    PWM_OUT_6_BIT | PWM_OUT_7_BIT are the bits needed to OR together for this single
    value. true or false in the last field determines if the signal is enabled or disabled.*/
    PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT, true);

}

void quad_esc_set_thrust(uint32_t motor, uint16_t thrust){
    /**
     * Change the thrust of a sigle motor
     *         FRONT
     * _____            _____
     * | 1 |            | 2 |
     * -----            -----
     *      \          /
     *       /         \       
     * _____            _____
     * | 3 |            | 4 |
     * -----            -----
     * 
     * Motor 1: CW
     * Motor 2: CCW
     * Motor 3: CCW
     * Motor 4: CW
     * 
    */

    // limit thrust to max allowed value
    thrust = (thrust > 1250) ? 1250 : thrust;

    // return if motor is unknown
    switch (motor){
    case MOTOR1:
    case MOTOR2:
    case MOTOR3:
    case MOTOR4:
       break;
   
    default:
        return;
    }

    // set the pwm value
    PWMPulseWidthSet(PWM0_BASE, motor, 1250 + thrust);
}