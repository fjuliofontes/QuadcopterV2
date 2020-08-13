#include <Arduino.h>
#include "hc-sr04.h"

unsigned long last = 0;
float res = 0;
uint16_t period = 1000;

void setup() {
    Serial.begin(115200); // Starts the serial communication
    if(hc_sr04_init(HC_SR04_EXPECTED_HEIGHT) == HC_SR04_0K) Serial.println("Init Ok");
    else Serial.println("Not ok");
}
void loop() {
    if((millis()-last) > period){
        last = millis();
        hc_sr04_trigger(); 
        while(hc_sr04_read(&res) == HC_SR04_WAITING_MEASUREMENT);
        Serial.println(res);
    }
}
