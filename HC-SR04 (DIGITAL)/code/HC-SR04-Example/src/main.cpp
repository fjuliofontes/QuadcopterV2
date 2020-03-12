#include <Arduino.h>
#include "hc-sr04.h"

unsigned long last = 0;
uint16_t period = 1000;

void setup() {
    Serial.begin(115200); // Starts the serial communication
    hc_sr04_init();
}
void loop() {
    if((millis()-last) > period){
        last = millis();
        hc_sr04_trigger();
        while(hc_sr04_read() == 0);
        Serial.println(distance);
    }
}
