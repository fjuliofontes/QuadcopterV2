
#include "m8-gps.h"

uint8_t m8_gps_init(){
    // configure UART Baudrate
    M8_GPS_BEGIN(M8_GPS_BAUDRATE);
    return M8_GPS_OK;
}

uint8_t m8_gps_available(){
    return M8_GPS_AVAILABLE;
}

uint8_t m8_gps_readByte(){
    return M8_GPS_READBYTE;
}

void m8_gps_writeByte(uint8_t ch){
    M8_GPS_WRITEBYTE((char)ch);
}

void m8_gps_writeWord(char *word){
    while(*word) m8_gps_writeByte(*word++);
}
