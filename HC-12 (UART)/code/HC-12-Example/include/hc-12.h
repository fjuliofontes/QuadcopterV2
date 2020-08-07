#ifndef HC_12_H
#define HC_12_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>

#define HC_12_UART_BASE UART1_BASE
#define HC_12_BAUDRATE 115200
#define HC_12_OK 0
#define HC_12_NOT_OK 1
#define HC_12_TIMEOUT 500
#define HC_12_SET_PIN PB_5
//#define HC_12_BEGIN(x) Serial1.begin(x)
#define HC_12_BEGIN(x) ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); \
                            ROM_GPIOPinConfigure(GPIO_PB0_U1RX); \
                                ROM_GPIOPinConfigure(GPIO_PB1_U1TX); \
                                    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); \
                                        ROM_UARTConfigSetExpClk(HC_12_UART_BASE, SysCtlClockGet(), x ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); \
                                            ROM_UARTEnable(HC_12_UART_BASE); \
                                                SysCtlDelay(100)
//#define HC_12_AVAILABLE Serial1.available()
#define HC_12_AVAILABLE ROM_UARTCharsAvail(HC_12_UART_BASE)
//#define HC_12_READBYTE Serial1.read()
#define HC_12_READBYTE ROM_UARTCharGetNonBlocking(HC_12_UART_BASE)
//#define HC_12_WRITEBYTE(x) Serial1.write(x)
#define HC_12_WRITEBYTE(x) ROM_UARTCharPut(HC_12_UART_BASE, x)
#define HC_12_RX_INT(x)   UARTIntDisable(HC_12_UART_BASE, UART_INT_TX | UART_INT_RX); \
                            UARTIntRegister(HC_12_UART_BASE, x); \
                                    ROM_UARTIntEnable(HC_12_UART_BASE,UART_INT_RX)

// ROM_UARTFIFOLevelSet(HC_12_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

#define HC_12_CLEAN_RX_INT UARTIntClear(HC_12_UART_BASE, UART_INT_RX)

#define HC_12_AT_MODE 1
#define HC_12_NORMAL_MODE 0

#define HC_12_RESET "AT+DEFAULT"
#define HC_12_VERSION "AT+V"
#define HC_12_UART "AT+B"
#define HC_12_CHANNEL "AT+C"
#define HC_12_MODE "AT+FU"
#define HC_12_TX_PWR "AT+P"
#define HC_12_RX_PARAMS "AT+RX"

#define HC_12_MODERATE_POWER_SAVING_MODE 1
#define HC_12_EXTREME_POWER_SAVING_MODE 2
#define HC_12_GENERAL_PURPOSE_MODE 3
#define HC_12_LONG_RANGE_MODE 4

#define HC_12_0_8_mW 1
#define HC_12_1_6_mW 2
#define HC_12_3_2_mW 3
#define HC_12_6_3_mW 4
#define HC_12_12_mW 5
#define HC_12_25_mW 6
#define HC_12_50_mW 7
#define HC_12_100_mW 8

uint8_t hc_12_init();
uint8_t hc_12_available();
void hc_12_writeByte(uint8_t ch);
uint8_t hc_12_readByte();
void hc_12_writeWord(char *word);
void hc_12_normal_mode();
void hc_12_at_mode();

uint32_t hc_12_findBaudrate();
uint8_t hc_12_changeBaudrate(uint32_t baudrate);
uint8_t hc_12_setRadioChannel(uint8_t ch);
uint8_t hc_12_setDeviceMode(uint8_t mode);
uint8_t hc_12_setTXpower(uint8_t pwr);
void hc_12_version();
void hc_12_reset();
void hc_12_rx_params();

#endif