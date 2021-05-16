#ifndef HC_05_H
#define HC_05_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>

#define BT_INIT_OF_FRAME 0xAABB
#define BT_END_OF_FRAME 0xCCDD
#define HC_05_WAITING_REMOTE_TIMEOUT 1000 // in us

#define HC_05_UART_BASE UART5_BASE
#define HC_05_BAUDRATE 115200
#define HC_05_DEVICE_NAME "JulioPi"
#define HC_05_DEVICE_PASS "1234"
#define HC_05_OK 0
#define HC_05_NOT_OK 1
#define HC_05_TIMEOUT 500
#define HC_05_STATE_PIN PB_4
#define HC_05_ENABLE_PIN PA_5
//#define HC_05_BEGIN(x) Serial1.begin(x)
#define HC_05_BEGIN(x) ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5); \
                            ROM_GPIOPinConfigure(GPIO_PE4_U5RX); \
                                ROM_GPIOPinConfigure(GPIO_PE5_U5TX); \
                                    ROM_GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5); \
                                        ROM_UARTConfigSetExpClk(HC_05_UART_BASE, SysCtlClockGet(), x ,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); \
                                            ROM_UARTEnable(HC_05_UART_BASE); \
                                                SysCtlDelay(100)
//#define HC_05_AVAILABLE Serial1.available()
#define HC_05_AVAILABLE ROM_UARTCharsAvail(HC_05_UART_BASE)
//#define HC_05_READBYTE Serial1.read()
#define HC_05_READBYTE ROM_UARTCharGetNonBlocking(HC_05_UART_BASE)
//#define HC_05_WRITEBYTE(x) Serial1.write(x)
#define HC_05_WRITEBYTE(x) ROM_UARTCharPut(HC_05_UART_BASE, x)
#define HC_05_RX_INT(x)   UARTIntDisable(HC_05_UART_BASE, UART_INT_TX | UART_INT_RX); \
                            UARTIntRegister(HC_05_UART_BASE, x); \
                                UARTFIFODisable(HC_05_UART_BASE); \
                                    ROM_UARTIntEnable(HC_05_UART_BASE,UART_INT_RX)

#define HC_05_STATE_INT(x) pinMode(HC_05_STATE_PIN,INPUT); \
                                attachInterrupt(HC_05_STATE_PIN,x,CHANGE)

// ROM_UARTFIFOLevelSet(HC_05_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

#define HC_05_CLEAN_RX_INT UARTIntClear(HC_05_UART_BASE, UART_INT_RX)

#define HC_05_RESET "AT+RESET"
#define HC_05_VERSION "AT+VERSION"
#define HC_05_RESTORE "AT+ORGL"
#define HC_05_ADDR "AT+ADDR"
#define HC_05_NAME "AT+NAME"
#define HC_05_RNAME "AT+RNAME"
#define HC_05_ROLE "AT+ROLE"
#define HC_05_PASS "AT+PSWD"
#define HC_05_UART "AT+UART"
#define HC_05_STATE "AT+STATE"
#define HC_05_SLAVE 0
#define HC_05_MASTER 1

#define HC_05_MODULE_WAITING        0x00
#define HC_05_MODULE_START          0x01
#define HC_05_MODULE_READING        0x02
#define HC_05_MODULE_STOP           0x04
#define HC_05_MODULE_DISCONNECTED   0x08

uint8_t hc_05_init();
uint8_t hc_05_available();
void hc_05_writeByte(uint8_t ch);
uint8_t hc_05_readByte();
uint32_t hc_05_findBaudrate();
void hc_05_writeWord(char *word);
uint8_t hc_05_changeBaudrate(uint32_t baudrate);
uint8_t hc_05_changeName(String name);
uint8_t hc_05_changeOpMode(uint8_t mode);
uint8_t hc_05_changePASS(String pass);
uint8_t hc_05_restore();
String hc_05_getName();
String hc_05_getPass();
void hc_05_status_isr();
void hc_05_rx_isr();
uint8_t hc_05_readChannels(uint16_t * ch, uint8_t * flags);

#endif