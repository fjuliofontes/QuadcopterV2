
#include "esp-01.h"
#include "util.h"

uint8_t _esp_01_tcp_status = ESP_01_TCP_DISCONNECTED; // 0 -> disconnected , 1 -> connected
char _esp_01_tcp_answer[20];
uint8_t _esp_01_tcp_answer_len = 0;
char _esp_01_ch;
char _esp_01_status = ESP_01_STATUS_NORMAL_MODE; 

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
    digitalWrite(ESP_01_RST_PIN,HIGH); delay(100);
    // configure UART Baudrate
    ESP_01_BEGIN(ESP_01_BAUDRATE);
    
    /// wait OK from reset
    unsigned long cmd_time = millis();
    while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
    /// receive answer
    if(esp_01_receive_answer().indexOf(">OK") != -1) return ESP_01_OK;
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


uint8_t esp_01_tcp_connect(char *ip, char *port){
    // init variables
    String esp_01_answer;
    unsigned long cmd_time;
    bool isConnected = false;

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // try connect to the given ip and port
    //// send tcp command - #TCP,192.168.100.1,3000
    esp_01_writeWord((char*)"#TCP,");
    esp_01_writeWord(ip);
    esp_01_writeWord((char*)",");
    esp_01_writeWord(port);
    esp_01_writeWord((char*)"\r");
    /// wait for answer for 1 seconds 
    /// if you want to force and wait for the answer, increase this value to 10s or greater
    cmd_time = millis();
    while((millis()-cmd_time) < 1000){
        if(esp_01_wait_answer() == ESP_01_OK){
            /// receive answer
            if(esp_01_receive_answer().indexOf(">CONNECTED") != -1){
                isConnected = true;
                break;
            }
        }
    }

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    // check connection result so far
    if(isConnected){
        _esp_01_tcp_status = ESP_01_TCP_CONNECTED;
        return ESP_01_OK;
    }else return ESP_01_NOT_OK; // no problem, the answer will be handled by the isr

}

uint8_t esp_01_tcp_send(char * msg){
    // verify connection status
    if(_esp_01_tcp_status == ESP_01_TCP_DISCONNECTED) return ESP_01_NOT_OK; // not connected

    // send msg
    esp_01_writeWord(msg);

    // send msg terminator
    esp_01_writeByte('\r');

    return ESP_01_OK;
}

void esp_01_tcp_disconnect(){

    if(_esp_01_tcp_status == ESP_01_TCP_DISCONNECTED) return; // already disconnected

    // check rx interrupt status
    bool rx_int_status = ESP_01_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) ESP_01_DISABLE_RX_INT;

    // disconnect from tcp connection
    /// write the command
    esp_01_writeWord((char*)"#TPCCLOSE\r");
    /// wait for answer
    if(esp_01_wait_answer());
    /// receive answer
    if(esp_01_receive_answer().indexOf(">OK") != -1) _esp_01_tcp_status = ESP_01_TCP_DISCONNECTED;

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;
}

void esp_01_rx_isr(){
    while(ESP_01_AVAILABLE){
        _esp_01_ch = ESP_01_READBYTE;

        switch (_esp_01_ch){
        // answer to commands
        case '>':
            _esp_01_status = ESP_01_STATUS_ANSW_CMD;
            break;

        case '\r':
            if(_esp_01_status == ESP_01_STATUS_ANSW_CMD){
                _esp_01_status = ESP_01_STATUS_NORMAL_MODE;
                // process cmd
                //// add string terminator
                _esp_01_tcp_answer[_esp_01_tcp_answer_len++] = '\0';
                //// check if is CONNECTED answer
                if(strcmp("CONNECTED\0",_esp_01_tcp_answer) == 0){
                    //// set tcp status to connected
                    _esp_01_tcp_status = ESP_01_TCP_CONNECTED;
                }
                //// future answers here 
                // reset answer cmd variables
                memset(_esp_01_tcp_answer,'\0',_esp_01_tcp_answer_len);
                _esp_01_tcp_answer_len = 0;
            }
            // normal operation
            else if(_esp_01_status == ESP_01_STATUS_NORMAL_MODE){
                //Serial.write(_esp_01_ch);
                Serial.print(" "); Serial.print((uint8_t)_esp_01_ch); Serial.print(" ");
            }
            break;
        
        default:
            // normal operation
            if(_esp_01_status == ESP_01_STATUS_NORMAL_MODE){
                Serial.print(" "); Serial.print((uint8_t)_esp_01_ch); Serial.print(" ");
            }
            // answer to commands
            else if(_esp_01_status == ESP_01_STATUS_ANSW_CMD){
                // add to buffer
                _esp_01_tcp_answer[_esp_01_tcp_answer_len++] = _esp_01_ch;
            }
            break;
        }
    }
    // clean interrup flag
    ESP_01_CLEAN_RX_INT;
}