#ifndef SIM800L_h
#define SIM800L_h

#include <stdint.h>
#include <Arduino.h>
#include <sysctl.h>
#include <uart.h>
#include <rom.h>
#include <pin_map.h>
#include "util.h"
#include <hw_uart.h>
#include <hw_types.h>

#define SIM800L_UART_BASE UART4_BASE
#define SIM800L_BAUDRATE 9600
#define SIM800L_OK 0
#define SIM800L_NOT_OK 1
#define SIM800L_TIMEOUT 5000
#define SIM800L_BUFFER_RESERVE_MEMORY 255
#define SIM800L_RST_PIN PB_2
#define DEFAULT_LED_FLAG false 	// true: use led.	 false: don't user led.
#define DEFAULT_LED_PIN 13 		// pin to indicate states.
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
#define SIM800L_CLEAN_TX_INT UARTIntClear(SIM800L_UART_BASE, UART_INT_TX)

#define SIM800L_DISABLE_RX_INT UARTIntDisable(SIM800L_UART_BASE, UART_INT_RX)
#define SIM800L_DISABLE_TX_INT UARTIntDisable(SIM800L_UART_BASE, UART_INT_TX)

#define SIM800L_ENABLE_RX_INT ROM_UARTIntEnable(SIM800L_UART_BASE, UART_INT_RX)
#define SIM800L_ENABLE_TX_INT ROM_UARTIntEnable(SIM800L_UART_BASE, UART_INT_TX)

#define SIM800L_RX_INT_STATUS ((HWREG(SIM800L_UART_BASE+UART_O_IM)&UART_INT_RX) == UART_INT_RX)
#define SIM800L_TX_INT_STATUS ((HWREG(SIM800L_UART_BASE+UART_O_IM)&UART_INT_TX) == UART_INT_TX)

void sim800l_rx_isr();

class sim800l {

private:
    uint32_t _sim800l_baud;
    int _sim800l_timeout;
    String _sim800l_buffer;
    bool _sim800l_sleepMode;
    uint8_t _sim800l_functionalityMode;
    String _sim800l_locationCode;
    String _sim800l_longitude;
    String _sim800l_latitude;

    void _writeWord(char *word);
    void _writeByte(char ch);
    uint8_t _available();
    uint8_t _readByte();
    String _receive_answer();
    String _receive_answer(uint32_t timeout);
    bool _echo(uint8_t on);

public:
    sim800l(void);

    void begin();					//Default baud 9600
    void begin(uint32_t baud);
    void reset();

    bool setSleepMode(bool state);
    bool getSleepMode();
    bool setFunctionalityMode(uint8_t fun);
    uint8_t getFunctionalityMode();

    bool setPIN(String pin);
    String getProductInfo();

    String getOperatorsList();
    String getOperator();

    bool calculateLocation();
    String getLocationCode();
    String getLongitude();
    String getLatitude();

    bool answerCall();
    void callNumber(char* number);
    bool hangoffCall();
    uint8_t getCallStatus();

    bool sendSms(char* number,char* text);
    String readSms(uint8_t index);
    String getNumberSms(uint8_t index);
    bool delAllSms();


    String signalQuality();
    void setPhoneFunctionality();
    void activateBearerProfile();
    void deactivateBearerProfile();

    void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);
    String dateNet();
    bool updateRtc(int utc);

    void writeWord(char *word);
    void writeByte(char ch);
    bool simReady();
    String listSms();
    bool unReadSms(uint8_t * index_list, uint8_t * len);
};


#endif
