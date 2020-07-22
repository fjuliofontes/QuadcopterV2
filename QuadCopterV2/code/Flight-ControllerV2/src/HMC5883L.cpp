/*
 *
 * 
 * 
 */

#include <limits.h>
#include "HMC5883L.h"
#include "quad_pins.h"

static float _hmc5883_Gauss_LSB_XY = 1100.0F; // Varies with gain
static float _hmc5883_Gauss_LSB_Z = 980.0F;   // Varies with gain

/***************************************************************************
 MAGNETOMETER
 ***************************************************************************/
/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void HMC5883L::write8(byte address, byte reg, byte value) {
    I2Cdev::writeByte(address, (uint8_t)reg, (uint8_t)value);
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
byte HMC5883L::read8(byte address, byte reg) {
    byte value;
    // read byte
    I2Cdev::readByte(address, (uint8_t)reg, (uint8_t*)&value);
    return value;
}

/**************************************************************************/
/*!
    @brief  Reads the raw data from the sensor
*/
/**************************************************************************/
void HMC5883L::read() {
    static uint8_t data[6];
    I2Cdev::readBytes((byte)HMC5883_ADDRESS_MAG, (uint8_t)HMC5883_REGISTER_MAG_OUT_X_H_M, 6 , data);

    uint8_t xhi = data[0];
    uint8_t xlo = data[1];
    uint8_t zhi = data[2];
    uint8_t zlo = data[3];
    uint8_t yhi = data[4];
    uint8_t ylo = data[5];

    // Shift values to create properly formed integer (low byte first)
    _magData.x = (int16_t)(xlo | ((int16_t)xhi << 8));
    _magData.y = (int16_t)(ylo | ((int16_t)yhi << 8));
    _magData.z = (int16_t)(zlo | ((int16_t)zhi << 8));

    // ToDo: Calculate orientation
    _magData.orientation = 0.0;
}

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Instantiates a new Adafruit_HMC5883 class
*/
/**************************************************************************/
HMC5883L::HMC5883L(int32_t sensorID) {
    _sensorID = sensorID;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Setups the HW
*/
/**************************************************************************/
bool HMC5883L::begin() {
    // (8-average, 75 Hz measurement)
    write8(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_CRA_REG_M, HMC5883_MAGSAMPLES_8 | HMC5883_MAGRATE_75);

    // Set the gain to a known level
    setMagGain(HMC5883_MAGGAIN_1_3);

    // Enable the magnetometer (Continuous-measurement mode)
    write8(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_MR_REG_M, 0x00);

    return true;
}

/**************************************************************************/
/*!
    @brief  Sets the magnetometer's gain
*/
/**************************************************************************/
void HMC5883L::setMagGain(hmc5883MagGain gain) {
    write8(HMC5883_ADDRESS_MAG, HMC5883_REGISTER_MAG_CRB_REG_M, (byte)gain);

    _magGain = gain;

    switch (gain) {
    case HMC5883_MAGGAIN_1_3:
        _hmc5883_Gauss_LSB_XY = 1100;
        _hmc5883_Gauss_LSB_Z = 980;
        break;
    case HMC5883_MAGGAIN_1_9:
        _hmc5883_Gauss_LSB_XY = 855;
        _hmc5883_Gauss_LSB_Z = 760;
        break;
    case HMC5883_MAGGAIN_2_5:
        _hmc5883_Gauss_LSB_XY = 670;
        _hmc5883_Gauss_LSB_Z = 600;
        break;
    case HMC5883_MAGGAIN_4_0:
        _hmc5883_Gauss_LSB_XY = 450;
        _hmc5883_Gauss_LSB_Z = 400;
        break;
    case HMC5883_MAGGAIN_4_7:
        _hmc5883_Gauss_LSB_XY = 400;
        _hmc5883_Gauss_LSB_Z = 255;
        break;
    case HMC5883_MAGGAIN_5_6:
        _hmc5883_Gauss_LSB_XY = 330;
        _hmc5883_Gauss_LSB_Z = 295;
        break;
    case HMC5883_MAGGAIN_8_1:
        _hmc5883_Gauss_LSB_XY = 230;
        _hmc5883_Gauss_LSB_Z = 205;
        break;
    }
}

void HMC5883L::getMotion(float *x, float *y, float *z, float *orientation){
    HMC5883L::read();

    *x = (_magData.x / _hmc5883_Gauss_LSB_XY) * SENSORS_GAUSS_TO_MICROTESLA;
    *y = (_magData.y / _hmc5883_Gauss_LSB_XY) * SENSORS_GAUSS_TO_MICROTESLA;
    *z = (_magData.z / _hmc5883_Gauss_LSB_Z)  * SENSORS_GAUSS_TO_MICROTESLA;

    if(_hmc5883l_calibrated){
        *x = (*x + _hmc5883l_x_off)*_hmc5883l_x_scf;
        *y = (*y + _hmc5883l_y_off)*_hmc5883l_y_scf;
        *z = (*z + _hmc5883l_z_off)*_hmc5883l_z_scf;
    }
}

bool HMC5883L::calibrate(uint8_t seconds){
    // flag calibration entry
    quad_ledOff();
    // start by re-setting the _calibration state
    _hmc5883l_calibrated = false;
    // define variables
    float magnetic_x, magnetic_y, magnetic_z, first_mag_z;
    uint16_t h = 10, i = 0; // worst case scenario refresh rate of 75Hz
    bool blinkState = false; // for animation
    long last_time = millis();
    // get a new sensor read
    getMotion(&magnetic_x,&magnetic_y,&magnetic_z);
    // init max and min vars and first magnetic field on z axis
    _hmc5883l_max_x = magnetic_x,_hmc5883l_max_y = magnetic_y,_hmc5883l_max_z = magnetic_z;
    _hmc5883l_min_x = magnetic_x,_hmc5883l_min_y = magnetic_y,_hmc5883l_min_z = magnetic_z;
    first_mag_z = magnetic_z;
    // loop until reach seconds
    while(millis()-last_time < seconds*1000){
        // get a new sensor read
        getMotion(&magnetic_x,&magnetic_y,&magnetic_z); // Get a new sensor event 
        // get minimum for all the axis, but ignore readings where mag_z are high for x and y axis
        if((magnetic_x<_hmc5883l_min_x) && (magnetic_z*0.7 < first_mag_z) && (magnetic_z*1.3 > first_mag_z)) _hmc5883l_min_x = magnetic_x;
        if((magnetic_y<_hmc5883l_min_y) && (magnetic_z*0.7 < first_mag_z) && (magnetic_z*1.3 > first_mag_z)) _hmc5883l_min_y = magnetic_y;
        if(magnetic_z<_hmc5883l_min_z) _hmc5883l_min_z = magnetic_z;
        // get maximum for all the axis, but ignore readings where mag_z are high for x and y axis
        if((magnetic_x>_hmc5883l_max_x) && (magnetic_z*0.7 < first_mag_z) && (magnetic_z*1.3 > first_mag_z)) _hmc5883l_max_x = magnetic_x;
        if((magnetic_y>_hmc5883l_max_y) && (magnetic_z*0.7 < first_mag_z) && (magnetic_z*1.3 > first_mag_z)) _hmc5883l_max_y = magnetic_y;
        if(magnetic_z>_hmc5883l_max_z) _hmc5883l_max_z = magnetic_z;
        delay(h); // pause until next reading ready 
        //if(((i++)%20) == 0) Serial.print('.'); // print '.' at every +/- 200ms
        if(((i++)%50) == 0) { blinkState = !blinkState; quad_led(GREEN_LED,blinkState);} // blink every 500 ms
    }
    // calculate offsets from center (0,0)
    _hmc5883l_x_off = -(_hmc5883l_max_x+_hmc5883l_min_x)/2;
    _hmc5883l_y_off = -(_hmc5883l_max_y+_hmc5883l_min_y)/2;
    _hmc5883l_z_off = -(_hmc5883l_max_z+_hmc5883l_min_z)/2;
    // calculate scale factor
    _hmc5883l_x_scf = (_hmc5883l_max_y-_hmc5883l_min_y)/(_hmc5883l_max_x-_hmc5883l_min_x);
    _hmc5883l_y_scf = (_hmc5883l_max_x-_hmc5883l_min_x)/(_hmc5883l_max_y-_hmc5883l_min_y);
    // choose the biggest scale factor (avoid elipt)
    if(_hmc5883l_x_scf > _hmc5883l_y_scf){
        _hmc5883l_y_scf = 1;
        _hmc5883l_z_scf = (_hmc5883l_max_y-_hmc5883l_min_y)/(_hmc5883l_max_z-_hmc5883l_min_z);
    } else{
        _hmc5883l_z_scf = (_hmc5883l_max_x-_hmc5883l_min_x)/(_hmc5883l_max_z-_hmc5883l_min_z);
        _hmc5883l_x_scf = 1;
    } 
    // flag calibration done
    _hmc5883l_calibrated = true;
    quad_ledOff();
    return _hmc5883l_calibrated;
}

