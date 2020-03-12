#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>
#include <gpio.h>

#define HC_SR04_TRIG_PIN PB_1
#define HC_SR04_ECHO_PIN PD_1

#define HC_SR04_MAX_ECHO_TIME 23529 // 4 meter
#define HC_SR04_MIN_ECHO_TIME 118 // 2 cm

extern volatile float distance;

void hc_sr04_trigger();
void hc_sr04_init();
float hc_sr04_read();
void hc_sr04_isr();

#endif