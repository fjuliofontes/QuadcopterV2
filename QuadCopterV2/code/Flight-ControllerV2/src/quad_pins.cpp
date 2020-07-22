#include <quad_pins.h>
#include <Arduino.h>

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