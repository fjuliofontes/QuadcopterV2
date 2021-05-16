#include "MS5611.h"


MS5611::MS5611() {
  ;
}

uint8_t MS5611::init(uint8_t address) {  
    // set ms5611 addr
    _ms5611_addr = address;
    // Reset MS5611 for forcing factory calibration parameteres to be 
    // written to eeprom
    I2Cdev::writeBytes(_ms5611_addr, MS6511_RESET, 0 , NULL);
    delay(100); // wait reboot

    // Read factory calibration values
    // C1 C2 C3 C4 C5 C6
    Serial.println("Reading factory calibration values ...");
    uint8_t result[2];
    for (int i = 1; i <= 6; i ++ ) {
        // request C[x]
        if (I2Cdev::readBytes(_ms5611_addr, MS6511_PROM_START_ADDR + i*2 , 2 , result) != 2) return MS5611_NOT_OK;
        C[i] = (result[0] << 8) | result[1];
        // debug C[x]
        Serial.print("C["); Serial.print(i); Serial.print("] : "); Serial.println(C[i]);
    }

    // Fill buffers
    /// Fill pressures
    Serial.println("Populating pressure_movavg_buff ...");
    for (int i = 0; i < MS5611_PRESSURE_MOVAVG_SIZE; i++ ) {
        startPressureConversion();
        delay(10);
        if ( getRawDataFromADC(&raw_pressure) == MS5611_NOT_OK ) Serial.println("Reading pressure too soon!");
        pushAvg(pressure_movavg_buff,raw_pressure,&pressure_movavg_i,MS5611_PRESSURE_MOVAVG_SIZE);
    }
    Serial.println("Populating temperature_movavg_buff ...");
    /// Fill temperatures
    for (int i = 0; i < MS5611_TEMPERATURE_MOVAVG_SIZE; i++ ) {
        startTemperatureConversion();
        delay(10);
        if ( getRawDataFromADC(&raw_temperature) == MS5611_NOT_OK ) Serial.println("Reading temperature too soon!");
        pushAvg(temperature_movavg_buff,raw_temperature,&temperature_movavg_i,MS5611_TEMPERATURE_MOVAVG_SIZE);
    }
    Serial.println("Populating altitude_movavg_buff ...");
    /// Get current altitude
    calculate();
    for (int i = 0; i < MS5611_ALTITUDE_MOVAVG_SIZE; i++ ) {
        pushAvg(altitude_movavg_buff,altitude,&altitude_movavg_i,MS5611_ALTITUDE_MOVAVG_SIZE);
    }
    Serial.println("Everything was well populated! Init Done!"); 
    Serial.print("MS5611 Temperature: "); Serial.print(temperature/100.f); Serial.println(" C");
    Serial.print("MS5611 Pressure: "); Serial.print(pressure/100.f); Serial.println(" hPa");
    Serial.print("MS5611 Altitude: "); Serial.print(altitude/100.f); Serial.println(" m");

    return MS5611_OK;
}

void MS5611::startPressureConversion() {
    /// Start pressure conversion
    I2Cdev::writeBytes(_ms5611_addr, MS6511_PRESSURE, 0 , NULL);
}

void MS5611::startTemperatureConversion() {
    /// Start temperature conversion
    I2Cdev::writeBytes(_ms5611_addr, MS6511_TEMPERATURE, 0 , NULL);
}

uint8_t MS5611::getRawDataFromADC(uint32_t * raw_data) {
    /// Start ADC transaction
    uint8_t result[3];
    if ( I2Cdev::readBytes(_ms5611_addr, MS6511_READ_ADC, 3 , result) != 3 ) return MS5611_NOT_OK;
    *raw_data = (result[0] << 16) | (result[1] << 8) | result[2];
    /// Check value
    if (*raw_data == 0) return MS5611_NOT_OK;
    else return MS5611_OK;
}

void MS5611::pushAvg(uint32_t * buffer, uint32_t value, uint16_t * movavg_i, uint16_t MOVAVG_SIZE) {
    buffer[*movavg_i] = value;
    *movavg_i = (*movavg_i + 1) % MOVAVG_SIZE;
}

uint32_t MS5611::getAvg(uint32_t * buffer, int16_t MOVAVG_SIZE) {
    float sum = 0.0;
    for(int i=0; i<MOVAVG_SIZE; i++) {
        sum += buffer[i];
    }
    return (uint32_t) (sum / MOVAVG_SIZE);
}

void MS5611::calculate() {
    //// get average temperature & pressure
    raw_temperature = getAvg(temperature_movavg_buff,MS5611_TEMPERATURE_MOVAVG_SIZE);
    raw_pressure = getAvg(pressure_movavg_buff,MS5611_PRESSURE_MOVAVG_SIZE);
    //// corrections
    dT = raw_temperature - (((int32_t)C[5]) << 8);
    temperature = 2000 +  ( ( dT * C[6] ) >> 23 ); 
    OFFSET = (((int64_t)C[2]) << 16) + ((C[4] * dT) >> 7);
    SENSITIVITY = (((int64_t)C[1]) << 15) + ((C[3] * dT) >> 8);
    /// extra calibration for lower temps
    if ( temperature < 2000 ) {
        temperature2 = ((dT*dT) >> 31);
        OFFSET2 = 5 * (((temperature-2000)*(temperature-2000)) >> 1) ;
        SENSITIVITY2 = 5 * (((temperature-2000)*(temperature-2000)) >> 2);
        if ( temperature < -1500 ) {
            OFFSET2 = OFFSET2 + 7 * (temperature-1500)*(temperature-1500);
            SENSITIVITY2 = SENSITIVITY2 + 11 * (((temperature-1500)*(temperature-1500)) >> 1);
        }
        // apply correction
        temperature -= temperature2;
        OFFSET -= OFFSET2;
        SENSITIVITY -= SENSITIVITY2;
    }
    pressure = (((raw_pressure * SENSITIVITY) >> 21) - OFFSET) >> 15;
    altitude = (uint32_t) ((float)((powf((SEA_LEVEL_PRESURE/((float)pressure)),0.1902226f) - 1) * (( temperature / 100.f) + 273.15) * 153.8461538462f) * 100.f);
}

/*
 * @Name: iterateSensorAndGetAltitude()
 * @Brief: This function was designed to be called each 4 ms.
 *         The selected OSR requires at least 9.04ms for completing the reading.
 *         The maximum allowed periodicity would be aprox. 3 ms
 * @Input: void
 * @Output: Current calculated altitude
 */
uint32_t MS5611::iterateSensorAndGetAltitude() {
    uint32_t retval = altitude;

    switch (cnt)
    {
        case 0:
            /// Start temperature conversion
            startTemperatureConversion();
            break;
        case 3:
            /// Start ADC transaction for temperature
            // Serial.printf("reading temperature after: %lu \n", last_loop - startCMD);
            getRawDataFromADC(&raw_temperature);
            /// Start pressure conversion
            startPressureConversion();
            /// Insert to buffer
            pushAvg(temperature_movavg_buff,raw_temperature,&temperature_movavg_i,MS5611_TEMPERATURE_MOVAVG_SIZE);
            break;
        
        case 6:
        case 9: 
        case 12:
        case 15:
            /// Start ADC transaction for pessure
            // Serial.printf("reading pressure after: %lu \n", last_loop - startCMD);
            getRawDataFromADC(&raw_pressure);
            if (cnt == 15) {
                /// Start temperature conversion
                startTemperatureConversion();
            } else {
                /// Start pressure conversion
                startPressureConversion();
            }
            /// Insert to buffer
            pushAvg(pressure_movavg_buff,raw_pressure,&pressure_movavg_i,MS5611_PRESSURE_MOVAVG_SIZE);
            /// Calculations
            calculate();
            /// Insert to buffer
            pushAvg(altitude_movavg_buff,altitude,&altitude_movavg_i,MS5611_ALTITUDE_MOVAVG_SIZE);
            /// Calculate new altitude value
            retval = getAvg(altitude_movavg_buff,MS5611_ALTITUDE_MOVAVG_SIZE);
            break;

        default:
            break;
    }

    if ( cnt == 15) {
        cnt = 1;
    } else {
        cnt ++;
    }

    return retval;
}

/*
 * @Name: getSensorTemperature()
 * @Brief: This function was designed to be called after the iterateSensorAndGetAltitude (if desired).
 * @Input: void
 * @Output: Current calculated temperature
 */
uint32_t MS5611::getSensorTemperature() {
    return (uint32_t)temperature;
}
