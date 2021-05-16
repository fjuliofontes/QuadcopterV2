#ifndef _QUAD_PINS_H_
#define _QUAD_PINS_H_

#include <pins_energia.h>
#include <stdint.h>
#include <pwm.h>

#define TARGET_SSID "ITHome"
#define TARGET_PWD "pass1234"
#define QUAD_OK 0
#define QUAD_NOT_OK 1

#define MOTOR1  PWM_OUT_6
#define MOTOR2  PWM_OUT_7
#define MOTOR3  PWM_OUT_1
#define MOTOR4  PWM_OUT_0

#define BATTERY_INDICATOR PD_3

// TODO: ADD here all the necessary functionalities
#define REMOTE_QUADCOPTER_NO_FLAGS       0
#define REMOTE_QUADCOPTER_HOLD_ALTITUDE  (1 << 0)
#define REMOTE_QUADCOPTER_AUTOMATIC_LAND (1 << 1)
#define REMOTE_QUADCOPTER_GPS_HOLD       (1 << 2)

void quad_init();
float quad_readBatteryVoltage();
void quad_redOn();
void quad_greenOn();
void quad_blueOn();
void quad_ledOff();
void quad_led(uint8_t led, uint8_t state);
void quad_blinkLed(uint32_t blink_rate, uint32_t blink_ms, uint8_t led);
void quad_setColor(uint8_t red, uint8_t green, uint8_t blue);

uint8_t quad_write_eeprom(uint32_t addr, uint32_t * data, uint32_t len);
uint8_t quad_read_eeprom(uint32_t addr, uint32_t * data, uint32_t len);
uint32_t quad_eeprom_get_size();
uint8_t quad_eeprom_get_bytes_pear_block();
uint8_t quad_init_eeprom();

void quad_esc_motors_init();
void quad_esc_set_thrust(uint32_t motor, uint16_t throttle);

#endif