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
    float getPressure(uint8_t OSR);
    float getTemperature(uint8_t OSR);
    int64_t getDeltaTemp(uint8_t OSR);
    int32_t rawPressure(uint8_t OSR);
    int32_t rawTemperature(uint8_t OSR);
    uint8_t readPROM();
    void reset();
  private:
    uint32_t doConversion(uint8_t command);
    uint8_t _addr;
    uint16_t _CREGS[MS5611_PROM_REG_COUNT];
};

#endif // MS5611_h