#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>
#include <gpio.h>

#define HC_SR04_0K 0
#define HC_SR04_NOT_OK 1

#define HC_SR04_EXPECTED_HEIGHT 5 // expected to be 5cm

#define HC_SR04_WAITING_MEASUREMENT 1
#define HC_SR04_READ_OK 0

#define HC_SR04_TRIG_PIN PE_1
#define HC_SR04_ECHO_PIN PE_2
#define HC_SR04_ISR_BASE GPIO_PORTE_BASE
#define HC_SR04_ISR_PIN GPIO_PIN_2

#define HC_SR04_MAX_ECHO_TIME 23529 // 4 meter
#define HC_SR04_MIN_ECHO_TIME 118 // 2 cm

extern volatile float distance;

void hc_sr04_trigger();
uint8_t hc_sr04_init(uint16_t expected_height);
uint8_t hc_sr04_read(float *res);
void hc_sr04_isr();

#endif