/*
MS5611-01BA.cpp - Interfaces a Measurement Specialities MS5611
*/

#include "MS5611.h"
#define EXTRA_PRECISION 5 // trick to add more precision to the pressure and temp readings

MS5611::MS5611() {
  ;
}

uint8_t MS5611::init(uint8_t address) {  
    _addr =  address;
    reset(); // reset the device to populate its internal PROM registers
    delay(1000); // some safety time 
    return readPROM(); // reads the PROM into object variables for later use
}

float MS5611::getPressure(uint8_t OSR) {
    // see datasheet page 7 for formulas
    int64_t dT   = getDeltaTemp(OSR);
    int64_t off  = (((int64_t)_CREGS[1]) << 16) + ((_CREGS[3] * dT) >> 7);
    int64_t sens = (((int64_t)_CREGS[0]) << 15) + ((_CREGS[2] * dT) >> 8);
    return ((((rawPressure(OSR) * sens) >> 21) - off) >> (15-EXTRA_PRECISION)) / ((1<<EXTRA_PRECISION) * 100.0);
}

float MS5611::getTemperature(uint8_t OSR) {
    // see datasheet page 7 for formulas
    return ((1<<EXTRA_PRECISION)*2000l + ((getDeltaTemp(OSR) * _CREGS[5]) >> (23-EXTRA_PRECISION))) / ((1<<EXTRA_PRECISION) * 100.0);
}

int64_t MS5611::getDeltaTemp(uint8_t OSR) {
    return rawTemperature(OSR) - (((int32_t)_CREGS[4]) << 8);
}

int32_t MS5611::rawPressure(uint8_t OSR) {
    return doConversion(MS5611_D1 + OSR);
}

int32_t MS5611::rawTemperature(uint8_t OSR) {
    return doConversion(MS5611_D2 + OSR);
}


uint32_t MS5611::doConversion(uint8_t command) {
    uint32_t conversion = 0;
    
    // see page 11 of the datasheet
    
    // initialize pressure conversion
    I2Cdev::writeBytes(_addr, command, 0 , NULL);
    
    delay(10); // the conversion will take a time <= 9.04 ms to have the output ready
    // TODO: make the delay dependant on the OSR requested in the command
    
    // start read sequence
    uint8_t result[MS5611_D1D2_SIZE];
    if(I2Cdev::readBytes(_addr, 0 ,(uint8_t) MS5611_D1D2_SIZE , result) == MS5611_D1D2_SIZE){
        conversion = result[0] << 16 | result[1] << 8 | result[2];
    }else{
        conversion = -1;
    }
    
    return conversion;
}


/**
 * Reads factory calibration and store it into object variables.
*/
uint8_t MS5611::readPROM() {
    uint8_t result[MS5611_PROM_REG_SIZE];
    for (uint8_t i=0; i<MS5611_PROM_REG_COUNT; i++) {
        if(I2Cdev::readBytes(_addr, MS5611_PROM_BASE_ADDR + (i * MS5611_PROM_REG_SIZE) , (uint8_t) MS5611_PROM_REG_SIZE , result) == MS5611_PROM_REG_SIZE){
            _CREGS[i] = result[0] << 8 | result[1];
        }else{
            return MS5611_NOT_OK;
        }
    }
    return MS5611_OK;
}


/**
 * Send a reset command to the device. With the reset command the device
 * populates its internal registers with the values read from the PROM.
*/
void MS5611::reset() {
    I2Cdev::writeBytes(_addr, MS5611_RESET, 0 , NULL);
}
