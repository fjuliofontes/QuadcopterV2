#ifndef M8_GPS_H
#define M8_GPS_H

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>

#define M8_GPS_UART_BASE UART2_BASE
#define M8_GPS_TIMEOUT 1200
#define M8_GPS_BAUDRATE 115200 
#define M8_GPS_MEASRATE 55
#define M8_GPS_NAVRATE 1
#define M8_GPS_OK 0
#define M8_GPS_NOT_OK 1
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
                                UARTFIFODisable(M8_GPS_UART_BASE); \
                                    UARTIntEnable(M8_GPS_UART_BASE,UART_INT_RX)
                                
                                
// UARTFIFOLevelSet(M8_GPS_UART_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);                             

#define M8_GPS_CLEAN_RX_INT UARTIntClear(M8_GPS_UART_BASE, UART_INT_RX)

#define M8_GPS_MESSAGE_DISABLED 0x0 
#define M8_GPS_DTM_MESSAGE 0xF00A
#define M8_GPS_RMC_MESSAGE 0xF004
#define M8_GPS_VTG_MESSAGE 0xF005
#define M8_GPS_GGA_MESSAGE 0xF000
#define M8_GPS_GSA_MESSAGE 0xF002
#define M8_GPS_GSV_MESSAGE 0xF003
#define M8_GPS_GLL_MESSAGE 0xF001

#define M8_GPS_MODULE_WAITING  0x00
#define M8_GPS_MODULE_START    0x01
#define M8_GPS_MODULE_READING  0x02
#define M8_GPS_MODULE_IGNORING 0x04
#define M8_GPS_MODULE_CR       0x08
#define M8_GPS_MODULE_LF       0x10

uint8_t m8_gps_init(uint32_t baudrate);
uint8_t m8_gps_available();
void m8_gps_writeByte(uint8_t ch);
uint8_t m8_gps_readByte();
void m8_gps_writeWord(char *word);
uint8_t m8_gps_getCoords(struct m8_gps *coords);
uint32_t bswap_32 (uint32_t num);
void m8_gps_setBaudrate(uint32_t baudrate);
uint32_t m8_gps_findBaudrate();
void m8_gps_checksum(uint8_t *CK_A, uint8_t *CK_B, uint8_t *data, uint8_t len);
void m8_gps_setMeasRate(uint16_t measRate, uint8_t navRate);
void m8_gps_setMsgRate(uint16_t MSG_ID, uint8_t rate);
uint16_t bswap_16 (uint16_t num);
void m8_gps_rx_isr();
uint8_t m8_gps_pending_read();


struct coord {
    uint16_t degrees;
    uint16_t minutes;
    uint16_t seconds;
    char direction;
};

struct m8_gps {
    // 000º00'00'N/S
    struct coord lat;
    // 000º00'00'E/W
    struct coord lon;
};

#endif