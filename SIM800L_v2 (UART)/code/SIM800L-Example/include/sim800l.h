#ifndef SIM800L_H
#define SIM800L_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>

#define SIM800L_UART_BASE UART4_BASE
#define SIM800L_BAUDRATE 115200
#define SIM800L_OK 0
#define SIM800L_NOT_OK 1
#define SIM800L_TIMEOUT 500
#define SIM800L_RST_PIN PB_2
//#define SIM800L_BEGIN(x) Serial1.begin(x)
#define SIM800L_BEGIN(x) ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4); \
                            ROM_GPIOPinConfigure(GPIO_PC4_U4RX); \
                                ROM_GPIOPinConfigure(GPIO_PC5_U4TX); \
                                    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5); \
                                        ROM_UARTConfigSetExpClk(SIM800L_UART_BASE, SysCtlClockGet(), x ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); \
                                            ROM_UARTEnable(SIM800L_UART_BASE); \
                                                SysCtlDelay(100)
//#define SIM800L_AVAILABLE Serial1.available()
#define SIM800L_AVAILABLE ROM_UARTCharsAvail(SIM800L_UART_BASE)
//#define SIM800L_READBYTE Serial1.read()
#define SIM800L_READBYTE ROM_UARTCharGetNonBlocking(SIM800L_UART_BASE)
//#define SIM800L_WRITEBYTE(x) Serial1.write(x)
#define SIM800L_WRITEBYTE(x) ROM_UARTCharPut(SIM800L_UART_BASE, x)
#define SIM800L_RX_INT(x)   UARTIntDisable(SIM800L_UART_BASE, UART_INT_TX | UART_INT_RX); \
                            UARTIntRegister(SIM800L_UART_BASE, x); \
                                ROM_UARTFIFOLevelSet(SIM800L_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8); \
                                    ROM_UARTIntEnable(SIM800L_UART_BASE,UART_INT_RX)

#define SIM800L_CLEAN_RX_INT UARTIntClear(SIM800L_UART_BASE, UART_INT_RX)

uint8_t sim800l_init();
uint8_t sim800l_available();
void sim800l_writeByte(uint8_t ch);
uint8_t sim800l_readByte();
void sim800l_writeWord(char *word);

#endif