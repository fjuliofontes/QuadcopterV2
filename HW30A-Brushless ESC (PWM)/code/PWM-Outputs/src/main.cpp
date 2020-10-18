#include <Arduino.h>

#include <pwm.h>
#include <sysctl.h>
#include <rom.h>
#include <pin_map.h>
#include <stdint.h>
#include <hw_memmap.h>
#include <hw_GPIO.h>
#include <gpio.h>

#define GPIO_PB6_M0PWM0         0x00011804
#define GPIO_PB7_M0PWM1         0x00011C04
#define GPIO_PD0_M0PWM6         0x00030004
#define GPIO_PD1_M0PWM7         0x00030404

void setup() {
    Serial.begin(115200);

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
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1250);
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

    /* Config GPIO PD3 as analog input */
    //analogReadResolution(12); // 12 bit resolution

}

void loop() {
    // put your main code here, to run repeatedly:
    if(Serial.available()){
        switch (Serial.read())
        {
        case '0':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1250);
            break;
        case '1':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1375);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1375);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1375);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1375);
            break;
        case '2':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1500);
            break;
        case '3':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1625);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1625);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1625);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1625);
            break;
        case '4':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1750);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1750);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1750);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1750);
            break;
        case '5':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 1875);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1875);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1875);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1875);
            break;
        case '6':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 2000);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 2000);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 2000);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 2000);
            break;
        case '7':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 2125);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 2125);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 2125);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 2125);
            break;
        case '8':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 2250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 2250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 2250);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 2250);
            break;
        case '9':
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, 2500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 2500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 2500);
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 2500);
            break;
        
        default:
            break;
        }
    }
    //Serial.println("ADC VAL = " + String(analogRead(PD_3)));
}