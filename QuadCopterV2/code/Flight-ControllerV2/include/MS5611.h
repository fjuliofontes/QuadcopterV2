/*
MS5611-01BA.h - Interfaces a Measurement Specialities MS5611
*/

#ifndef MS5611_h
#define MS5611_h

#include <Wire.h>
#include <Arduino.h>
#include "I2Cdev.h"

//#define DEBUG_V
//#define DEBUG
//#include <DebugUtils.h>

#define MS5611_OK 0
#define MS5611_NOT_OK 1
#define MS5611_MOVAVG_SIZE 32
#define MS5611_STATE_IDLE 0
#define MS5611_STATE_BUSY 1
#define MS5611_STATE_TEMPERATURE 2
#define MS5611_STATE_PRESSURE 3

// addresses of the device
#define MS5611_ADDR_CSB_HIGH  0x76   //CBR=1 0x76 I2C address when CSB is connected to HIGH (VCC)
#define MS5611_ADDR_CSB_LOW   0x77   //CBR=0 0x77 I2C address when CSB is connected to LOW (GND)

// registers of the device
#define MS5611_D1 0x40
#define MS5611_D2 0x50
#define MS5611_RESET 0x1E

// D1 and D2 result size (bytes)
#define MS5611_D1D2_SIZE 3

// OSR (Over Sampling Ratio) constants
#define MS5611_OSR_256 0x00
#define MS5611_OSR_512 0x02
#define MS5611_OSR_1024 0x04
#define MS5611_OSR_2048 0x06
#define MS5611_OSR_4096 0x08

#define MS5611_PROM_BASE_ADDR 0xA2 // by adding ints from 0 to 6 we can read all the prom configuration values. 
// C1 will be at 0xA2 and all the subsequent are multiples of 2
#define MS5611_PROM_REG_COUNT 6 // number of registers in the PROM
#define MS5611_PROM_REG_SIZE 2 // size in bytes of a prom registry.



class MS5611 {
  public:
    MS5611();
    uint8_t init(uint8_t addr);
    float getPressure();
    float getTemperature();
    int64_t getDeltaTemp();
    int32_t rawPressure(uint8_t OSR);
    int32_t rawTemperature(uint8_t OSR);
    uint8_t readPROM();
    void reset();
    float getAltitude();
  private:
    void pushAvg(float val);
    float getAvg(float * buff, int size);

    uint8_t _addr;
    uint16_t _CREGS[MS5611_PROM_REG_COUNT];
    const float _sea_press = 1013.25;
    float _movavg_buff[MS5611_MOVAVG_SIZE];
    uint8_t _movavg_i = 0;
    float _ms5611_altitude = 0.0;
    uint8_t _ms5611_state = MS5611_STATE_IDLE;
    int32_t _ms5611_rawPressure = -1;
    int32_t _ms5611_rawTemperature = -1;
    unsigned long _ms5611_conversion_started = micros();
    unsigned long _ms5611_last_altitude = micros();
    bool _flag = true;
};

#endif // MS5611_h