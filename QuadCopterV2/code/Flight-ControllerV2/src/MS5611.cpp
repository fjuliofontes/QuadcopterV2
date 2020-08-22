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
    uint8_t retval = readPROM(); // reads the PROM into object variables for later use
    // populate movavg_buff before start new readings
    if(retval == MS5611_OK){
        for(uint8_t i = 0; i < MS5611_MOVAVG_SIZE; i++) {
            rawTemperature(MS5611_OSR_4096); delay(10); rawTemperature(MS5611_OSR_4096); // read temperature
            rawPressure(MS5611_OSR_4096); delay(10); rawPressure(MS5611_OSR_4096); // read pressure
            _movavg_buff[i] = getPressure(); // upd circular buffer
        }
    }
    return retval;
}

float MS5611::getPressure() {
    // see datasheet page 7 for formulas
    int64_t dT   = getDeltaTemp();
    int64_t off  = (((int64_t)_CREGS[1]) << 16) + ((_CREGS[3] * dT) >> 7);
    int64_t sens = (((int64_t)_CREGS[0]) << 15) + ((_CREGS[2] * dT) >> 8);
    return ((((_ms5611_rawPressure * sens) >> 21) - off) >> (15-EXTRA_PRECISION)) / ((1<<EXTRA_PRECISION) * 100.0);
}

float MS5611::getTemperature() {
    // see datasheet page 7 for formulas
    return ((1<<EXTRA_PRECISION)*2000l + ((getDeltaTemp() * _CREGS[5]) >> (23-EXTRA_PRECISION))) / ((1<<EXTRA_PRECISION) * 100.0);
}

int64_t MS5611::getDeltaTemp() {
    return _ms5611_rawTemperature - (((int32_t)_CREGS[4]) << 8);
}

int32_t MS5611::rawPressure(uint8_t OSR) {
    if(_ms5611_state == MS5611_STATE_IDLE){
        _ms5611_state = MS5611_STATE_PRESSURE; // change state to busy
        // see page 11 of the datasheet
        // initialize pressure conversion
        I2Cdev::writeBytes(_addr, MS5611_D1+OSR, 0 , NULL);
        _ms5611_conversion_started = micros();
    }else if (_ms5611_state == MS5611_STATE_PRESSURE){
        // the conversion will take a time <= 9.04 ms to have the output ready
        // TODO: make the delay dependant on the OSR requested in the command
        if((micros()-_ms5611_conversion_started) >= 9500){
            _ms5611_state = MS5611_STATE_IDLE; // change state back again to idle
            
            // start read sequence
            uint8_t result[MS5611_D1D2_SIZE];
            if(I2Cdev::readBytes(_addr, 0 ,(uint8_t) MS5611_D1D2_SIZE , result) == MS5611_D1D2_SIZE){
                _ms5611_rawPressure = (uint32_t)(result[0] << 16 | result[1] << 8 | result[2]);
            }
        }
    } 
    return _ms5611_rawPressure;
}

int32_t MS5611::rawTemperature(uint8_t OSR) {
    if(_ms5611_state == MS5611_STATE_IDLE){
        _ms5611_state = MS5611_STATE_TEMPERATURE; // change state to busy
        // see page 11 of the datasheet
        // initialize pressure conversion
        I2Cdev::writeBytes(_addr, MS5611_D2+OSR, 0 , NULL);
        _ms5611_conversion_started = micros();
    }else if (_ms5611_state == MS5611_STATE_TEMPERATURE){
        // the conversion will take a time <= 9.04 ms to have the output ready
        // TODO: make the delay dependant on the OSR requested in the command
        if((micros()-_ms5611_conversion_started) >= 9500){
            _ms5611_state = MS5611_STATE_IDLE; // change state back again to idle
            
            // start read sequence
            uint8_t result[MS5611_D1D2_SIZE];
            if(I2Cdev::readBytes(_addr, 0 ,(uint8_t) MS5611_D1D2_SIZE , result) == MS5611_D1D2_SIZE){
                _ms5611_rawTemperature = (uint32_t)(result[0] << 16 | result[1] << 8 | result[2]);
            }
        }
    } 
    return _ms5611_rawTemperature;
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


float MS5611::getAltitude() {
    // readings needed for altitude
    /// rawTemperature()
    /// rawPressure()
    if(_ms5611_state == MS5611_STATE_IDLE){
        if(_flag) rawTemperature(MS5611_OSR_4096);
        else rawPressure(MS5611_OSR_4096);
        _flag = !_flag;
    }else{
        if(_ms5611_state == MS5611_STATE_TEMPERATURE) rawTemperature(MS5611_OSR_4096);
        else{
            rawPressure(MS5611_OSR_4096);
            if(_ms5611_state == MS5611_STATE_IDLE){
                pushAvg(getPressure());
                _ms5611_altitude = ((powf((_sea_press / getAvg(_movavg_buff,MS5611_MOVAVG_SIZE)), 1/5.257f) - 1.0f) * (getTemperature() + 273.15f)) / 0.0065f;
            }
        }
    }
    
    return _ms5611_altitude;
    //return ((pow((_sea_press / press), 1/5.257) - 1.0) * (temp + 273.15)) / 0.0065;
}

void MS5611::pushAvg(float val) {
    _movavg_buff[_movavg_i] = val;
    _movavg_i = (_movavg_i + 1) % MS5611_MOVAVG_SIZE;
}

float MS5611::getAvg(float * buff, int size) {
    float sum = 0.0;
    for(int i=0; i<size; i++) {
        sum += buff[i];
    }
    return sum / size;
}