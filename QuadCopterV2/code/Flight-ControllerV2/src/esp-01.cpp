
#include "esp-01.h"
#include "util.h"

String _esp_01_ip = "";
uint8_t _esp_01_tcp_status = 0; // 0 -> disconnected , 1 -> connected

uint8_t esp_01_wait_answer(){
    uint16_t esp_01_timeout;
    esp_01_timeout = ESP_01_TIMEOUT;
    while( (!esp_01_available()) && (--esp_01_timeout > 0) );
    return (esp_01_timeout == 0);
}

String esp_01_receive_answer(){
    String esp_01_answer = "";
    while(esp_01_available()){
        esp_01_answer += (char)esp_01_readByte();
        delayMicroseconds(100); // ((1/baudrate)*1e6) * 10 -> wait 10 times the baudrate - 115200bps
    }
    return esp_01_answer;
}

uint8_t esp_01_init(){
    // reset esp-01
    pinMode(ESP_01_RST_PIN,OUTPUT);
    // set RST pin high
    digitalWrite(ESP_01_RST_PIN,LOW); delay(1);
    // set RST pin down
    digitalWrite(ESP_01_RST_PIN,HIGH); delay(5000);
    // configure UART Baudrate
    ESP_01_BEGIN(ESP_01_BAUDRATE);
    
    // disable ECHO
    /// write the command
    esp_01_writeWord((char*)"ATE0\r\n");
    /// wait for answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    /// receive answer
    if(esp_01_receive_answer().indexOf("OK") != -1) return ESP_01_OK;
    else return ESP_01_NOT_OK;
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

uint8_t esp_01_disconnect_wifi(){
    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    esp_01_writeWord((char*)"AT+CWQAP\r\n");
    /// ignore answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    esp_01_receive_answer();

    // clear ip
    _esp_01_ip = "";

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    return ESP_01_OK;
}

uint8_t esp_01_connect_wifi(char *ssid, char *pwd){
    String esp_01_answer;
    int pos;

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // check wifi mode 
    /// write the command
    esp_01_writeWord((char*)"AT+CWMODE?\r\n");
    /// wait for answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    /// receive answer
    esp_01_answer = esp_01_receive_answer();
    /// search for mode
    pos = esp_01_answer.indexOf(":");
    if(pos == -1) return ESP_01_NOT_OK;
    /// change to sta mode
    if(pos != 1){ 
        esp_01_writeWord((char*)"AT+CWMODE=1\r\n");
        /// ignore answer
        if(esp_01_wait_answer()) return ESP_01_NOT_OK;
        esp_01_receive_answer();
    }

    // check wifi ap connection status
    /// write the command
    esp_01_writeWord((char*)"AT+CWJAP?\r\n");
    /// wait for answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    /// receive answer
    esp_01_answer = esp_01_receive_answer();
    /// search for ssid
    pos = esp_01_answer.indexOf(":");
    /// already connected
    if(pos != -1){
        /// check ssid
        pos = esp_01_answer.indexOf(ssid);
        /// connected to the wrong ssid so disconnect
        if(pos == -1){
            /// write command
            esp_01_writeWord((char*)"AT+CWQAP\r\n");
            /// ignore answer
            esp_01_wait_answer();
            esp_01_receive_answer();
        }
    }
    /// connect to the desired ssid
    if(pos == -1){
        // define variables
        unsigned long cmd_time;
        // connect to ssid with pwd
        esp_01_writeWord((char*)"AT+CWJAP=\"");
        esp_01_writeWord(ssid);
        esp_01_writeWord((char*)"\",\"");
        esp_01_writeWord(pwd);
        esp_01_writeWord((char*)"\"\r\n");
        /// wait for wifi connection 
        cmd_time = millis();
        while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
        if(esp_01_receive_answer().indexOf("WIFI CONNECTED") == -1) return ESP_01_NOT_OK;
        cmd_time = millis();
        while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
        if(esp_01_receive_answer().indexOf("WIFI GOT IP") == -1) return ESP_01_NOT_OK;
        cmd_time = millis();
        while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
        if(esp_01_receive_answer().indexOf("OK") == -1) return ESP_01_NOT_OK;
    }

    // get ip / connection status and print ip
    /// write command 
    esp_01_writeWord((char*)"AT+CIFSR\r\n");
    /// wait for answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    /// receive answer
    esp_01_answer = esp_01_receive_answer();
    /// search for ip
    pos = esp_01_answer.indexOf("STAIP");
    /// print ip
    _esp_01_ip = esp_01_answer.substring(pos+7,pos+22);
    _esp_01_ip.replace("\"","");
    Serial.println("Sucess, IP: "+_esp_01_ip);

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    return ESP_01_OK;
}

uint8_t esp_01_tcp_connect(char *ip, char *port){
    // verify internet connection
    if(_esp_01_ip == "") return ESP_01_NOT_OK;

    // init variables
    String esp_01_answer;

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // set esp to single connection
    /// write the command
    esp_01_writeWord((char*)"AT+CIPMUX=0\r\n");
    /// wait for answer
    if(esp_01_wait_answer()) return ESP_01_NOT_OK;
    /// receive answer
    if(esp_01_receive_answer().indexOf("OK") == -1) return ESP_01_NOT_OK;

    // try connect to the given ip and port
    /// write the command
    esp_01_writeWord((char*)"AT+CIPSTART=\"TCP\",\"");
    esp_01_writeWord(ip);
    esp_01_writeWord((char*)"\",");
    esp_01_writeWord(port);
    esp_01_writeWord((char*)"\r\n");
    /// wait for answer
    unsigned long cmd_time = millis();
    while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
    /// receive answer
    if(esp_01_receive_answer().indexOf("CONNECT") == -1) return ESP_01_NOT_OK;
    
    // tcp connected
    _esp_01_tcp_status = 1;

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    return ESP_01_OK;
}

uint8_t esp_01_tcp_send(char * msg, uint32_t len){
    // verify connection status
    if(_esp_01_tcp_status == 0) return ESP_01_NOT_OK; // not connected

    // init variables
    uint32_t msg_size = strlen(msg);
    char* slen = myITOA(len,10,0);

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // start transaction 
    /// write the command
    esp_01_writeWord((char*)"AT+CIPSEND=");
    esp_01_writeWord(slen);
    esp_01_writeWord((char*)"\r\n");
    /// wait for answer
    if(esp_01_wait_answer());
    /// receive answer
    if(esp_01_receive_answer().indexOf(">") == -1) return ESP_01_NOT_OK;

    // start transmitting
    /// send bytes
    if(len > msg_size){
        for(uint32_t i = 0; i < msg_size; i++) esp_01_writeByte(msg[i]);
        for(uint32_t i = msg_size; i < len; i++) esp_01_writeByte(' ');
    }else if(len < msg_size){
        for(uint32_t i = 0; i < len; i++) esp_01_writeByte(msg[i]);
    }else{
        esp_01_writeWord(msg);
    }

    /// wait recv confirmation
    if(esp_01_wait_answer());
    /// receive answer
    if(esp_01_receive_answer().indexOf("Recv "+String(slen)+" bytes") == -1) return ESP_01_NOT_OK;
    /// wait send confirmation
    if(esp_01_wait_answer());
    /// receive answer
    if(esp_01_receive_answer().indexOf("SEND OK") == -1) return ESP_01_NOT_OK;

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    return ESP_01_OK;
}

void esp_01_tcp_disconnect(){

    if(_esp_01_tcp_status == 0) return; // already disconnected

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // disconnect from tcp connection
    /// write the command
    esp_01_writeWord((char*)"AT+CIPCLOSE\r\n");
    /// wait for answer
    if(esp_01_wait_answer());
    /// receive answer
    if(esp_01_receive_answer().indexOf("CLOSED") != -1) _esp_01_tcp_status = 0;

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;
}

void esp_01_rx_isr(){
    while(ESP_01_AVAILABLE){
        Serial.write(ESP_01_READBYTE);
    }
    // clean interrup flag
    ESP_01_CLEAN_RX_INT;
}