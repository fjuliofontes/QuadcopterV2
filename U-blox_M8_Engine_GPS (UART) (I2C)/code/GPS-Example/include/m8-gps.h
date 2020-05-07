#ifndef M8_GPS_H
#define M8_GPS_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>

#define M8_GPS_UART_BASE UART2_BASE
#define M8_GPS_BAUDRATE 115200      
#define M8_GPS_OK 0
#define M8_GPS_NOT_OK 1
#define M8_GPS_TIMEOUT 500
//#define M8_GPS_BEGIN(x) Serial1.begin(x)
#define M8_GPS_BEGIN(x) ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2); \
                            ROM_GPIOPinConfigure(GPIO_PD6_U2RX); \
                                ROM_GPIOPinConfigure(GPIO_PD7_U2TX); \
                                    ROM_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7); \
                                        ROM_UARTConfigSetExpClk(M8_GPS_UART_BASE, SysCtlClockGet(), x ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); \
                                            ROM_UARTEnable(M8_GPS_UART_BASE); \
                                                SysCtlDelay(100)
//#define M8_GPS_AVAILABLE Serial1.available()
#define M8_GPS_AVAILABLE ROM_UARTCharsAvail(M8_GPS_UART_BASE)
//#define M8_GPS_READBYTE Serial1.read()
#define M8_GPS_READBYTE ROM_UARTCharGetNonBlocking(M8_GPS_UART_BASE)
//#define M8_GPS_WRITEBYTE(x) Serial1.write(x)
#define M8_GPS_WRITEBYTE(x) ROM_UARTCharPut(M8_GPS_UART_BASE, x)
#define M8_GPS_RX_INT(x)   UARTIntDisable(M8_GPS_UART_BASE, UART_INT_TX | UART_INT_RX); \
                            UARTIntRegister(M8_GPS_UART_BASE, x); \
                                ROM_UARTFIFOLevelSet(M8_GPS_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8); \
                                    ROM_UARTIntEnable(M8_GPS_UART_BASE,UART_INT_RX)

#define M8_GPS_CLEAN_RX_INT UARTIntClear(M8_GPS_UART_BASE, UART_INT_RX)

uint8_t m8_gps_init();
uint8_t m8_gps_available();
void m8_gps_writeByte(uint8_t ch);
uint8_t m8_gps_readByte();
void m8_gps_writeWord(char *word);

#endif