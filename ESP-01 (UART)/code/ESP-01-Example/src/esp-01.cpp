
#include "esp-01.h"

uint8_t esp_01_init(){
    // config status and enable pin
    pinMode(ESP_01_RST_PIN,OUTPUT);
    // set RST pin low
    digitalWrite(ESP_01_RST_PIN,LOW);
    // configure UART Baudrate
    ESP_01_BEGIN(ESP_01_BAUDRATE);
    return ESP_01_OK;
}

uint8_t esp_01_available(){
    return ESP_01_AVAILABLE;
}

uint8_t esp_01_readByte(){
    return ESP_01_READBYTE;
}

void esp_01_writeByte(uint8_t ch){
    ESP_01_WRITEBYTE((char)ch);
}

void esp_01_writeWord(char *word){
    while(*word) esp_01_writeByte(*word++);
}
