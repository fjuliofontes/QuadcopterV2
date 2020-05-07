
#include "hc-12.h"

uint8_t hc_12_init(){
    // config status and enable pin
    pinMode(HC_12_SET_PIN,OUTPUT);
    // set RST pin low
    digitalWrite(HC_12_SET_PIN,LOW);
    // configure UART Baudrate
    HC_12_BEGIN(HC_12_BAUDRATE);
    return HC_12_OK;
}

uint8_t hc_12_available(){
    return HC_12_AVAILABLE;
}

uint8_t hc_12_readByte(){
    return HC_12_READBYTE;
}

void hc_12_writeByte(uint8_t ch){
    HC_12_WRITEBYTE((char)ch);
}

void hc_12_writeWord(char *word){
    while(*word) hc_12_writeByte(*word++);
}
