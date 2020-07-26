/*!
 * 
 */
#ifndef __HMC5883L_H__
#define __HMC5883L_H__

#include "I2Cdev.h"

/*!
 * @brief I2C address/bits
 */
#define HMC5883_ADDRESS_MAG (0x3C >> 1) // 0011110x

#define SENSORS_GAUSS_TO_MICROTESLA 100 /**< Gauss to micro-Tesla multiplier */

#define HMC5883_CALIBRATION_ADDR      0x00
#define HMC5883_CALIBRATION_VALIDATOR 0x12345

/*!
 @brief Registers
 */
typedef enum {
  HMC5883_REGISTER_MAG_CRA_REG_M = 0x00,
  HMC5883_REGISTER_MAG_CRB_REG_M = 0x01,
  HMC5883_REGISTER_MAG_MR_REG_M  = 0x02,
  HMC5883_REGISTER_MAG_OUT_X_H_M = 0x03,
  HMC5883_REGISTER_MAG_OUT_X_L_M = 0x04,
  HMC5883_REGISTER_MAG_OUT_Z_H_M = 0x05,
  HMC5883_REGISTER_MAG_OUT_Z_L_M = 0x06,
  HMC5883_REGISTER_MAG_OUT_Y_H_M = 0x07,
  HMC5883_REGISTER_MAG_OUT_Y_L_M = 0x08,
  HMC5883_REGISTER_MAG_SR_REG_Mg = 0x09,
  HMC5883_REGISTER_MAG_IRA_REG_M = 0x0A,
  HMC5883_REGISTER_MAG_IRB_REG_M = 0x0B,
  HMC5883_REGISTER_MAG_IRC_REG_M = 0x0C,
  HMC5883_REGISTER_MAG_TEMP_OUT_H_M = 0x31,
  HMC5883_REGISTER_MAG_TEMP_OUT_L_M = 0x32
} hmc5883MagRegisters_t;

/*!
 * @brief Magnetometer gain settings
 */
typedef enum {
  HMC5883_MAGGAIN_1_3 = 0x20, // +/- 1.3
  HMC5883_MAGGAIN_1_9 = 0x40, // +/- 1.9
  HMC5883_MAGGAIN_2_5 = 0x60, // +/- 2.5
  HMC5883_MAGGAIN_4_0 = 0x80, // +/- 4.0
  HMC5883_MAGGAIN_4_7 = 0xA0, // +/- 4.7
  HMC5883_MAGGAIN_5_6 = 0xC0, // +/- 5.6
  HMC5883_MAGGAIN_8_1 = 0xE0  // +/- 8.1
} hmc5883MagGain;

typedef enum{
  HMC5883_MAGRATE_0_75 = 0x00 << 2,
  HMC5883_MAGRATE_1_5  = 0x01 << 2,
  HMC5883_MAGRATE_3    = 0x02 << 2,
  HMC5883_MAGRATE_7_5  = 0x03 << 2,
  HMC5883_MAGRATE_15   = 0x04 << 2,
  HMC5883_MAGRATE_30   = 0x05 << 2,
  HMC5883_MAGRATE_75   = 0x06 << 2
} hmc5883MagRate;

typedef enum{
  HMC5883_MAGSAMPLES_1 = 0x00 << 5,
  HMC5883_MAGSAMPLES_2 = 0x01 << 5,
  HMC5883_MAGSAMPLES_4 = 0x02 << 5,
  HMC5883_MAGSAMPLES_8 = 0x03 << 5
} hmc5883MagSamples;

/*!
 * @brief Internal magnetometer data type
 */
typedef struct hmc5883MagData_s {
  float x;           //!< Magnetometer x value
  float y;           //!< Magnetometer y value
  float z;           //!< Magnetometer z value
  float orientation; //!< Magnetometer orientation
} hmc5883MagData;

//typedef uint8_t (*callback_function)(uint32_t addr, uint32_t * data, uint32_t len); // type for conciseness

/*!
 * @brief Chip ID
 */
#define HMC5883_ID (0b11010100)

//! Unified sensor driver for the magnetometer ///
class HMC5883L {
public:
  /*!
   * @param sensorID sensor ID, -1 by default
   */
  HMC5883L(int32_t sensorID = -1);

  bool begin(void); //!< @return Returns whether connection was successful
  void setMagGain(hmc5883MagGain gain); //!< @param gain Desired magnetic gain
  void getMotion(float *x, float *y, float *z, float *orientation=NULL);
  bool calibrate(uint8_t seconds);
  bool isCalibrated();

  void setEEPROMWriteFunction(uint8_t(*func)(uint32_t addr, uint32_t * data, uint32_t len));
  void setEEPROMReadFunction(uint8_t(*func)(uint32_t addr, uint32_t * data, uint32_t len));

private:
  hmc5883MagGain _magGain;
  hmc5883MagData _magData; // Last read magnetometer data will be available here
  int32_t _sensorID;

  void write8(byte address, byte reg, byte value);
  byte read8(byte address, byte reg);
  void read(void);

  float _hmc5883l_max_x, _hmc5883l_max_y, _hmc5883l_max_z; // for calibration purposes 
  float _hmc5883l_min_x, _hmc5883l_min_y, _hmc5883l_min_z;

  float _hmc5883l_x_off, _hmc5883l_y_off, _hmc5883l_z_off;
  float _hmc5883l_x_scf, _hmc5883l_y_scf, _hmc5883l_z_scf;
  
  bool _hmc5883l_calibrated = false;

  uint8_t (*_hmc5883l_eeprom_write_function)(uint32_t addr, uint32_t * data, uint32_t len) = NULL;
  uint8_t (*_hmc5883l_eeprom_read_function)(uint32_t addr, uint32_t * data, uint32_t len) = NULL;
  //callback_function _hmc5883l_eeprom_write_function = NULL; // variable to store function pointer type
  //callback_function _hmc5883l_eeprom_read_function = NULL; // variable to store function pointer type
};

#endif
