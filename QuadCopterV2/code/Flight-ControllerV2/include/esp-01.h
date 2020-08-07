#ifndef ESP_01_H
#define ESP_01_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <hw_uart.h>
#include <pin_map.h>
#include <hw_types.h>

#define ESP_01_UART_BASE UART3_BASE
#define ESP_01_BAUDRATE 115200
#define ESP_01_OK 0
#define ESP_01_NOT_OK 1
#define ESP_01_TIMEOUT 10000
#define ESP_01_STATUS_NORMAL_MODE 0
#define ESP_01_STATUS_ANSW_CMD 1
#define ESP_01_TCP_CONNECTED 1
#define ESP_01_TCP_DISCONNECTED 0
#define ESP_01_RST_PIN PA_2
//#define ESP_01_BEGIN(x) Serial1.begin(x)
#define ESP_01_BEGIN(x) ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3); \
                            ROM_GPIOPinConfigure(GPIO_PC6_U3RX); \
                                ROM_GPIOPinConfigure(GPIO_PC7_U3TX); \
                                    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7); \
                                        ROM_UARTConfigSetExpClk(ESP_01_UART_BASE, SysCtlClockGet(), x ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); \
                                            ROM_UARTEnable(ESP_01_UART_BASE); \
                                                SysCtlDelay(100)
//#define ESP_01_AVAILABLE Serial1.available()
#define ESP_01_AVAILABLE ROM_UARTCharsAvail(ESP_01_UART_BASE)
//#define ESP_01_READBYTE Serial1.read()
#define ESP_01_READBYTE ROM_UARTCharGetNonBlocking(ESP_01_UART_BASE)
//#define ESP_01_WRITEBYTE(x) Serial1.write(x)
#define ESP_01_WRITEBYTE(x) ROM_UARTCharPut(ESP_01_UART_BASE, x)
#define ESP_01_RX_INT(x)   UARTIntDisable(ESP_01_UART_BASE, UART_INT_RX); \
                            UARTIntRegister(ESP_01_UART_BASE, x); \
                                ROM_UARTIntEnable(ESP_01_UART_BASE,UART_INT_RX)

// ROM_UARTFIFOLevelSet(ESP_01_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

#define ESP_01_DISABLE_RX_INT UARTIntDisable(ESP_01_UART_BASE, UART_INT_RX)
#define ESP_01_DISABLE_TX_INT UARTIntDisable(ESP_01_UART_BASE, UART_INT_TX)

#define ESP_01_ENABLE_RX_INT ROM_UARTIntEnable(ESP_01_UART_BASE, UART_INT_RX)
#define ESP_01_ENABLE_TX_INT ROM_UARTIntEnable(ESP_01_UART_BASE, UART_INT_TX)

#define ESP_01_RX_INT_STATUS ((HWREG(ESP_01_UART_BASE+UART_O_IM)&UART_INT_RX) == UART_INT_RX)
#define ESP_01_TX_INT_STATUS ((HWREG(ESP_01_UART_BASE+UART_O_IM)&UART_INT_TX) == UART_INT_TX)

#define ESP_01_CLEAN_RX_INT UARTIntClear(ESP_01_UART_BASE, UART_INT_RX)
#define ESP_01_CLEAN_TX_INT UARTIntClear(ESP_01_UART_BASE, UART_INT_TX)

uint8_t esp_01_init();
uint8_t esp_01_available();
void esp_01_writeByte(uint8_t ch);
uint8_t esp_01_readByte();
void esp_01_writeWord(char *word);
uint8_t esp_01_disconnect_wifi();
uint8_t esp_01_tcp_connect(char *ip, char *port);
uint8_t esp_01_tcp_send(char * msg);
void esp_01_tcp_disconnect();
void esp_01_rx_isr();

#endif