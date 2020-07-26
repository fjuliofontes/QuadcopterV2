#include <quad_pins.h>
#include <Arduino.h>
#include <sysctl.h>
#include <eeprom.h>

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
