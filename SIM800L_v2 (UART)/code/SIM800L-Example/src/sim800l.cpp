
#include "sim800l.h"

uint8_t sim800l_init(){
    // config status and enable pin
    pinMode(SIM800L_RST_PIN,OUTPUT);
    // set RST pin low
    digitalWrite(SIM800L_RST_PIN,HIGH);
    // configure UART Baudrate
    SIM800L_BEGIN(SIM800L_BAUDRATE);
    return SIM800L_OK;
}

uint8_t sim800l_available(){
    return SIM800L_AVAILABLE;
}

uint8_t sim800l_readByte(){
    return SIM800L_READBYTE;
}

void sim800l_writeByte(uint8_t ch){
    SIM800L_WRITEBYTE((char)ch);
}

void sim800l_writeWord(char *word){
    while(*word) sim800l_writeByte(*word++);
}
