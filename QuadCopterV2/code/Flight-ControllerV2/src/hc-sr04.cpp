#include "hc-sr04.h"

unsigned long pulseStart, pulseStop;
volatile float distance = 0;

void hc_sr04_init(){
    pinMode(HC_SR04_TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(HC_SR04_ECHO_PIN, INPUT); // Sets the echoPin as an Input
    attachInterrupt(HC_SR04_ECHO_PIN,hc_sr04_isr, RISING);
}

void hc_sr04_trigger(){
    distance = 0;
    //TODO: remove delay
    digitalWrite(HC_SR04_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(HC_SR04_TRIG_PIN, LOW);
}

float hc_sr04_read(){
    return distance;
}

void hc_sr04_isr(){
    if(GPIOPinRead(HC_SR04_ISR_BASE,HC_SR04_ISR_PIN)){
        pulseStart = micros();
        GPIOIntTypeSet(HC_SR04_ISR_BASE, HC_SR04_ISR_PIN, GPIO_FALLING_EDGE);
    }else{
        pulseStop = micros();
        GPIOIntTypeSet(HC_SR04_ISR_BASE, HC_SR04_ISR_PIN, GPIO_RISING_EDGE);
        // read ok
        if(((pulseStop-pulseStart) <= HC_SR04_MAX_ECHO_TIME) && ((pulseStop-pulseStart) >= HC_SR04_MIN_ECHO_TIME)){
            distance = (pulseStop-pulseStart) * 0.034 / 2;
        }
    }    
}