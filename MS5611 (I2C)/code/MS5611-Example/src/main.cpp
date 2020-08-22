#include <Arduino.h>
#include "I2Cdev.h"
#include "MS5611.h"
#include "Wire.h"

#define MOVAVG_SIZE 32

MS5611 baro = MS5611();

float movavg_buff[MOVAVG_SIZE];
int movavg_i=0;

const float sea_press = 1013.25;
float press, temp;

float getAltitude(float press, float temp);
void pushAvg(float val);
float getAvg(float * buff, int size);

void setup() {
    // Init i2c pins
    Wire = TwoWire(1);
    Wire.begin(); // set - ROM_I2CMasterInitExpClk(MASTER_BASE, F_CPU, true); 

    // Config baudrate
    Serial.begin(115200);

    // configure Arduino LED pin for output
    pinMode(RED_LED, OUTPUT);

    // Embedded adventures module CSB is VCC so HIGH
    // 
    if(baro.init(MS5611_ADDR_CSB_LOW) == MS5611_OK) Serial.println("OK");
    else Serial.println("NOT OK");
    delay(100);
  
    // populate movavg_buff before starting loop
    for(int i=0; i< MOVAVG_SIZE; i++) {
        movavg_buff[i] = baro.getPressure(MS5611_OSR_4096);
    }
}

void loop() {
    Serial.print(" temp: ");
    temp = baro.getTemperature(MS5611_OSR_4096);
    Serial.print(temp);
    Serial.print(" degC pres: ");
    pushAvg(baro.getPressure(MS5611_OSR_4096));
    press = getAvg(movavg_buff, MOVAVG_SIZE);
    Serial.print(press);
    Serial.print(" mbar altitude: ");
    Serial.print(getAltitude(press, temp));
    Serial.println(" m");
    delay(100);
}

float getAltitude(float press, float temp) {
  return ((pow((sea_press / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
}

void pushAvg(float val) {
  movavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}

float getAvg(float * buff, int size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}