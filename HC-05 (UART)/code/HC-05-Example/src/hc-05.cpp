
#include "hc-05.h"

static uint32_t _hc_05_baud = 0;
static String _hc_05_name = "";
static String _hc_05_pass = "";

uint8_t hc_05_init(){
    // config status and enable pin
    pinMode(HC_05_STATE_PIN,INPUT);
    pinMode(HC_05_ENABLE_PIN,OUTPUT);
    // set enable pin low
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // find HC-05 baudrate
    _hc_05_baud = hc_05_findBaudrate();
    // check if baudrate was found
    if(_hc_05_baud == HC_05_NOT_OK)
        return HC_05_NOT_OK;
    // config baudrate to the user choice baud
    if(_hc_05_baud != HC_05_BAUDRATE){
        // change hc-05 baudrate
        if(hc_05_changeBaudrate(HC_05_BAUDRATE) == HC_05_NOT_OK)
            return HC_05_NOT_OK;
        // change serial baudrate
        HC_05_BEGIN(HC_05_BAUDRATE);
    }
    // config device name
    _hc_05_name = hc_05_getName();
    if(_hc_05_name != String(HC_05_DEVICE_NAME))
        if(hc_05_changeName(String(HC_05_DEVICE_NAME)) == HC_05_NOT_OK)
            return HC_05_NOT_OK;
    // config device password
    _hc_05_pass = hc_05_getPass();
    if(_hc_05_pass != String(HC_05_DEVICE_PASS))
        if(hc_05_changePASS(String(HC_05_DEVICE_PASS)) == HC_05_NOT_OK)
            return HC_05_NOT_OK;
    // if everything went ok ....
    return HC_05_OK;
}

uint8_t hc_05_available(){
    return HC_05_AVAILABLE;
}

uint8_t hc_05_readByte(){
    return HC_05_READBYTE;
}

void hc_05_writeByte(uint8_t ch){
    HC_05_WRITEBYTE((char)ch);
}

void hc_05_writeWord(char *word){
    while(*word) hc_05_writeByte(*word++);
}

uint32_t hc_05_findBaudrate(){
    static uint32_t allowedRates[] = {9600,19200,38400,57600,115200,230400,460800};
    static uint8_t numRates = 7;
    unsigned long curr_time;
    uint8_t i;
    String response = "";
    bool baud_found = false;

    // set enable pin to AT commands
    digitalWrite(HC_05_ENABLE_PIN,HIGH);

    for(i = 0; i < numRates; i++){
        // init serial port
        HC_05_BEGIN(allowedRates[i]);
        delay(100);

        // Send AT command and wait response
        curr_time = millis();
        hc_05_writeWord((char*)"AT\r\n");
        do{
            if(hc_05_available())
                response += (char)hc_05_readByte();
            
        }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));

        // check for the response
        if(response == "OK\r\n"){
            baud_found = true;
            break;
        }

        response = "";
    }

    // set enable back to normal operation
    digitalWrite(HC_05_ENABLE_PIN,LOW);

    if(baud_found)
        return allowedRates[i];
    else
        return HC_05_NOT_OK;
}

uint8_t hc_05_changeBaudrate(uint32_t baudrate){
    unsigned long curr_time;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_UART) + '=' + String(baudrate) + ",1,0\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    if(response == "OK\r\n")
        return HC_05_OK;
    else
        return HC_05_NOT_OK;    
}

uint8_t hc_05_changeOpMode(uint8_t mode){
    unsigned long curr_time;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_ROLE) + '=' + String(mode) + "\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    if(response == "OK\r\n")
        return HC_05_OK;
    else
        return HC_05_NOT_OK;   
}

uint8_t hc_05_changeName(String name){
    unsigned long curr_time;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_NAME) + '=' + name + "\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    if(response == "OK\r\n")
        return HC_05_OK;
    else
        return HC_05_NOT_OK;    
}

uint8_t hc_05_changePASS(String pass){
    unsigned long curr_time;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_PASS) + '=' + pass + "\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    if(response == "OK\r\n")
        return HC_05_OK;
    else
        return HC_05_NOT_OK;    
}

uint8_t hc_05_restore(){
    unsigned long curr_time;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_RESTORE) + "\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while(((millis()-curr_time) < HC_05_TIMEOUT) && (response != "OK\r\n"));
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    if(response == "OK\r\n")
        return HC_05_OK;
    else
        return HC_05_NOT_OK;    
}

String hc_05_getName(){
    unsigned long curr_time;
    uint8_t init_pos, end_pos;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_NAME) + "?\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while((millis()-curr_time) < HC_05_TIMEOUT);
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    init_pos = response.indexOf("+NAME:");
    end_pos = response.indexOf("\r\n");
    if(init_pos != 255)
        return response.substring(init_pos+6,end_pos);
    else
        return "FAIL!";
}

String hc_05_getPass(){
    unsigned long curr_time;
    uint8_t init_pos, end_pos;
    String response = "", command = "";
    // change to command mode
    digitalWrite(HC_05_ENABLE_PIN,HIGH);
    command = String(HC_05_PASS) + "?\r\n";
    hc_05_writeWord((char*)&command[0]);
    // wait for response
    curr_time = millis();
    do{
        if(hc_05_available())
            response += (char)hc_05_readByte();
            
    }while((millis()-curr_time) < HC_05_TIMEOUT);
    // change to normal mode
    digitalWrite(HC_05_ENABLE_PIN,LOW);
    // check for the received response
    init_pos = response.indexOf("+PIN:");
    end_pos = response.indexOf("\r\n");
    if(init_pos != 255)
        return response.substring(init_pos+6,end_pos-1);
    else
        return "FAIL!";
    return response;
}
