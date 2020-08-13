
#include "hc-12.h"
#include "util.h"

static uint32_t _hc_12_baud = 0;
static uint8_t _hc_12_mode = 255;
static bool _hc_12_mode_changed = false;
static uint8_t _hc_12_radio_channel = 255;
static uint8_t _hc_12_device_mode = 255;
static uint8_t _hc_12_tx_power = 255;

uint8_t hc_12_wait_answer(){
    unsigned long curr_time = millis();
    while( (!hc_12_available()) && ((millis()-curr_time) < HC_12_TIMEOUT) );
    return ((millis()-curr_time) < HC_12_TIMEOUT) ? HC_12_OK : HC_12_NOT_OK;
}

String hc_12_receive_answer(){
    unsigned long curr_time = millis();
    String hc_12_answer = "";
    do{
        if(hc_12_available())
            hc_12_answer += (char)hc_12_readByte();
    }while(((millis()-curr_time) < HC_12_TIMEOUT) && (hc_12_answer.indexOf("\r\n") == -1));
    return hc_12_answer;
}

uint8_t hc_12_init(){
    // config set pin
    pinMode(HC_12_SET_PIN,OUTPUT);
    hc_12_at_mode();

    // find HC-05 baudrate
    _hc_12_baud = hc_12_findBaudrate();

    // check if baudrate was found
    if(_hc_12_baud == HC_12_NOT_OK) return HC_12_NOT_OK;
    // config baudrate to the user choice baud
    if(_hc_12_baud != HC_12_BAUDRATE){
        // change hc-05 baudrate
        if(hc_12_changeBaudrate(HC_12_BAUDRATE) == HC_12_NOT_OK)
            return HC_12_NOT_OK;
        // change serial baudrate
        HC_12_BEGIN(HC_12_BAUDRATE);
        _hc_12_baud = HC_12_BAUDRATE;
    }

    // change radio channel
    if(hc_12_setRadioChannel(2) == HC_12_NOT_OK) return HC_12_NOT_OK;

    // set device mode to normal 
    if(hc_12_setDeviceMode(HC_12_GENERAL_PURPOSE_MODE) == HC_12_NOT_OK) return HC_12_NOT_OK;

    // set tx power to max
    if(hc_12_setTXpower(HC_12_100_mW) == HC_12_NOT_OK) return HC_12_NOT_OK;

    // change to normal mode
    if(_hc_12_mode != HC_12_NORMAL_MODE) hc_12_normal_mode();

    // if everything went ok ....
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

void hc_12_at_mode(){
    _hc_12_mode = HC_12_AT_MODE;
    digitalWrite(HC_12_SET_PIN,LOW); // AT mode
    delay(100);
}

void hc_12_normal_mode(){
    _hc_12_mode = HC_12_NORMAL_MODE;
    digitalWrite(HC_12_SET_PIN,HIGH); // Normal mode
    delay(100);
}

uint32_t hc_12_findBaudrate(){
    static uint32_t allowedRates[] = {1200,2400,4800,9600,19200,38400,57600,115200};
    static uint8_t numRates = 8;
    unsigned long curr_time;
    uint8_t i;
    String response = "";
    bool baud_found = false;
    _hc_12_mode_changed = false;

    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }

    for(i = 0; i < numRates; i++){
        // init serial port
        HC_12_BEGIN(allowedRates[i]);
        delay(100);

        // Send AT command and wait response
        curr_time = millis();
        hc_12_writeWord((char*)"AT\r\n");
        do{
            if(hc_12_available())
                response += (char)hc_12_readByte();
            
        }while(((millis()-curr_time) < HC_12_TIMEOUT) && (response != "OK\r\n"));

        // check for the response
        if(response == "OK\r\n"){
            baud_found = true;
            break;
        }

        response = "";
    }

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }

    if(baud_found)
        return allowedRates[i];
    else
        return HC_12_NOT_OK;
}

uint8_t hc_12_changeBaudrate(uint32_t baudrate){
    String response = "", command = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }
    // set the command
    command = String(HC_12_UART) + String(baudrate) + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    // wait for response
    if(hc_12_wait_answer() == HC_12_NOT_OK) return HC_12_NOT_OK;
    response = hc_12_receive_answer();
    
    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }

    // check for the received response
    if(response.indexOf("OK") != -1)
        return HC_12_OK;
    else
        return HC_12_NOT_OK;    
}

uint8_t hc_12_getRadioChannel(){
    return _hc_12_radio_channel;
}

uint8_t hc_12_setRadioChannel(uint8_t ch){
    // check if is not already in the selected channel
    if(_hc_12_radio_channel == ch) return HC_12_OK;
    // ok, define variables
    String response = "", command = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }
    // set the command
    ch = (ch >= 1) && (ch <= 100) ? ch : 100; // only valid channels
    char *channel = myITOA(ch, 10, 3);
    command = String(HC_12_CHANNEL) + channel + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response
    if(hc_12_wait_answer() == HC_12_NOT_OK) return HC_12_NOT_OK;
    response = hc_12_receive_answer();

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }

    // check for the received response
    if(response.indexOf("OK") != -1){
        _hc_12_radio_channel = ch; // update channel 
        return HC_12_OK;
    }
    else
        return HC_12_NOT_OK; 
}

uint8_t hc_12_setDeviceMode(uint8_t mode){
    // check if is already in this mode
    if(_hc_12_device_mode == mode) return HC_12_OK; 
    // ok, define variables
    String response = "", command = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }
    // set the command
    mode = (mode >= 1) && (mode <= 4) ? mode : 3; // only valid modes
    command = String(HC_12_MODE) + mode + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response
    if(hc_12_wait_answer() == HC_12_NOT_OK) return HC_12_NOT_OK;
    response = hc_12_receive_answer();

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }

    // check for the received response
    if(response.indexOf("OK") != -1){
        _hc_12_device_mode = mode;
        return HC_12_OK;
    }
    else
        return HC_12_NOT_OK; 
}

uint8_t hc_12_getDeviceMode(){
    return _hc_12_device_mode;
}

uint8_t hc_12_setTXpower(uint8_t pwr){
    // check if already has this configuration
    if(_hc_12_tx_power == pwr) return HC_12_OK;
    // ok, init variables
    String response = "", command = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }
    // set the command
    pwr = (pwr >= 1) && (pwr <= 8) ? pwr : 8; // only valid modes
    command = String(HC_12_TX_PWR) + pwr + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response
    if(hc_12_wait_answer() == HC_12_NOT_OK) return HC_12_NOT_OK;
    response = hc_12_receive_answer();

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }

    // check for the received response
    if(response.indexOf("OK") != -1){
        _hc_12_tx_power = pwr;
        return HC_12_OK;
    }
    else
        return HC_12_NOT_OK; 
}

uint8_t hc_12_getTXpower(){
    return _hc_12_tx_power;
}

void hc_12_version(){
    String command = "", response = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }

    // set the command
    command = String(HC_12_VERSION) + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response
    if(hc_12_wait_answer() == HC_12_OK){
        response = hc_12_receive_answer();
        Serial.print(response);
    }

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }
}

void hc_12_rx_params(){
    String command = "", response = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }

    // set the command
    command = String(HC_12_RX_PARAMS) + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response
    if(hc_12_wait_answer() == HC_12_OK){
        response = hc_12_receive_answer();
        Serial.print(response);
    }

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }
}

void hc_12_reset(){
    String command = "", response = "";
    _hc_12_mode_changed = false;
    // change to command mode
    if(_hc_12_mode != HC_12_AT_MODE) {
        _hc_12_mode_changed = true;
        hc_12_at_mode();
    }

    // set the command
    command = String(HC_12_RESET) + "\r\n";
    hc_12_writeWord((char*)&command[0]);
    
    // wait for response and ignore it
    if(hc_12_wait_answer() == HC_12_OK){
        response = hc_12_receive_answer();
    }

    // change to normal mode
    if(_hc_12_mode_changed) {
        hc_12_normal_mode();
    }
}

void hc_12_rx_isr(){
    while(HC_12_AVAILABLE){
        Serial.write(HC_12_READBYTE);
    }
    // clean interrup flag
    HC_12_CLEAN_RX_INT;
}