#ifndef MS5611_h
#define MS5611_h

#include <Wire.h>
#include <Arduino.h>
#include "I2Cdev.h"

#define MS5611_ADDR 0x77  
#define MS6511_PROM_START_ADDR 0xA0
#define MS6511_RESET 0x1E
#define MS6511_TEMPERATURE 0x58
#define MS6511_PRESSURE 0x48
#define MS6511_READ_ADC 0x00
#define SEA_LEVEL_PRESURE 101325.f // in hPa * 10
#define MS5611_OK 0
#define MS5611_NOT_OK 1

#define MS5611_PRESSURE_MOVAVG_SIZE 32 
#define MS5611_TEMPERATURE_MOVAVG_SIZE 16 
#define MS5611_ALTITUDE_MOVAVG_SIZE 16 


class MS5611 {
    public:
        MS5611();
        uint8_t init(uint8_t addr);
        uint32_t iterateSensorAndGetAltitude();
        uint32_t getSensorTemperature();
    
    private:
        uint8_t _ms5611_addr = MS5611_ADDR;
        uint16_t C[7] = {0};
        uint32_t raw_pressure;
        uint32_t raw_temperature;
        uint8_t cnt = 0;
        int32_t dT ,temperature;
        int64_t OFFSET,SENSITIVITY;
        int32_t temperature2;
        int64_t OFFSET2,SENSITIVITY2;
        int64_t pressure;
        uint32_t altitude;

        // for averaging the readings
        uint32_t temperature_movavg_buff[MS5611_TEMPERATURE_MOVAVG_SIZE] = {0};
        uint32_t pressure_movavg_buff[MS5611_PRESSURE_MOVAVG_SIZE] = {0};
        uint32_t altitude_movavg_buff[MS5611_ALTITUDE_MOVAVG_SIZE] = {0};
        uint16_t temperature_movavg_i = 0, pressure_movavg_i = 0, altitude_movavg_i = 0;

        void startPressureConversion();
        void startTemperatureConversion();
        uint8_t getRawDataFromADC(uint32_t * raw_data);
        void pushAvg(uint32_t * buffer, uint32_t value, uint16_t * movavg_i, uint16_t MOVAVG_SIZE);
        uint32_t getAvg(uint32_t * buffer, int16_t MOVAVG_SIZE);
        void calculate();
};

#endif // MS5611_h