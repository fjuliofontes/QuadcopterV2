
#include "esp-01.h"
#include "util.h"

#define PID_CONFIG_TEMPLATE "AA00.00,00.00,00.00BB00.00,00.00,00.00CC00.00,00.00,00.00DD\r"
uint8_t _esp_01_tcp_status = ESP_01_TCP_DISCONNECTED; // 0 -> disconnected , 1 -> connected
char _esp_01_tcp_answer[20];
char _esp_01_pid_config[sizeof(PID_CONFIG_TEMPLATE) + 10];
uint8_t _esp_01_tcp_answer_len = 0;
uint8_t _esp_01_pid_config_len = 0;
char _esp_01_ch;
char _esp_01_status = ESP_01_STATUS_NORMAL_MODE; 
static quad_pid_config _quad_pid_config;
uint8_t _esp_01_new_pid_config = ESP_01_NOT_OK;

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
    uint8_t retval = ESP_01_NOT_OK;

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
    while(((millis()-cmd_time) < 5000) && (esp_01_wait_answer() == ESP_01_NOT_OK));
    /// receive answer
    if(esp_01_receive_answer().indexOf(">OK") != -1) retval = ESP_01_OK;

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) ESP_01_ENABLE_RX_INT;

    return retval;
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

uint8_t esp_01_get_pid_params(quad_pid_config ** pid_config) {
    if (_esp_01_new_pid_config == ESP_01_OK) {
        // flag has sent!
        _esp_01_new_pid_config = ESP_01_NOT_OK;
        *pid_config = &_quad_pid_config;
        return ESP_01_OK;
    }
    return ESP_01_NOT_OK;
}

void esp_01_rx_isr(){
    while(ESP_01_AVAILABLE){
        _esp_01_ch = ESP_01_READBYTE;

        switch (_esp_01_ch){
        // answer to commands
        case '>':
            _esp_01_status = ESP_01_STATUS_ANSW_CMD;
            break;

        // ignore new line because it is a reserved key
        case '\n':
            break;

        case '\r':
            if(_esp_01_status == ESP_01_STATUS_ANSW_CMD){
                _esp_01_status = ESP_01_STATUS_NORMAL_MODE;
                // process cmd
                //// add string terminator
                _esp_01_tcp_answer[_esp_01_tcp_answer_len++] = '\0';
                //// check if is CONNECTED answer
                if(strcmp("CONNECTED",_esp_01_tcp_answer) == 0){
                    //// set tcp status to connected
                    _esp_01_tcp_status = ESP_01_TCP_CONNECTED;
                } else if (strcmp("DISCONNECTED",_esp_01_tcp_answer) == 0) {
                    //// set tcp status to disconnected
                    _esp_01_tcp_status = ESP_01_TCP_DISCONNECTED;
                }
                //// future answers here 
                // reset answer cmd variables
                memset(_esp_01_tcp_answer,'\0',_esp_01_tcp_answer_len);
                _esp_01_tcp_answer_len = 0;
            }
            // normal operation
            else if(_esp_01_status == ESP_01_STATUS_NORMAL_MODE) {
                _esp_01_pid_config[_esp_01_pid_config_len++] = '\0';
                // Serial.println("Received " + String(_esp_01_pid_config));
                if (_esp_01_pid_config_len > 58) {
                    // done! process pid
                    char aa_validator[] = {
                        _esp_01_pid_config[0],
                        _esp_01_pid_config[1],
                        '\0'};
                    char bb_validator[] = {
                        _esp_01_pid_config[19],
                        _esp_01_pid_config[20],
                        '\0'};
                    char cc_validator[] = {
                        _esp_01_pid_config[38],
                        _esp_01_pid_config[39],
                        '\0'};
                    char dd_validator[] = {
                        _esp_01_pid_config[57],
                        _esp_01_pid_config[58],
                        '\0'};

                    // Serial.println(String(aa_validator) + String(bb_validator) + String(cc_validator) + String(dd_validator));

                    // check validators positions 
                    if ( (strcmp("AA",aa_validator) == 0) &&
                         (strcmp("BB",bb_validator) == 0) &&
                         (strcmp("CC",cc_validator) == 0) &&
                         (strcmp("DD",dd_validator) == 0)
                    ) { 
                        // Serial.println("valid! going to decode!");
                        // command ok, extract PID parameters
                        char target_number[7];
                        uint8_t target_number_size = 0;
                        uint8_t pid_state = 0;
                        for ( int i = 0; i <= 58; i++) {
                            // got the target number
                            if ((target_number_size > 0) && (!isdigit(_esp_01_pid_config[i])) && (_esp_01_pid_config[i] != '.')) {
                                target_number[target_number_size++] = '\0';
                                // decode
                                switch (pid_state++)
                                {
                                case 0:
                                    _quad_pid_config.altitude.p = strtod(target_number,NULL);
                                    break;
                                case 1:
                                    _quad_pid_config.altitude.i = strtod(target_number,NULL);
                                    break;
                                case 2:
                                    _quad_pid_config.altitude.d = strtod(target_number,NULL);
                                    break;
                                case 3:
                                    _quad_pid_config.pitch_and_roll.p = strtod(target_number,NULL);
                                    break;
                                case 4:
                                    _quad_pid_config.pitch_and_roll.i = strtod(target_number,NULL);
                                    break;
                                case 5:
                                    _quad_pid_config.pitch_and_roll.d = strtod(target_number,NULL);
                                    break;
                                case 6:
                                    _quad_pid_config.yaw.p = strtod(target_number,NULL);
                                    break;
                                case 7:
                                    _quad_pid_config.yaw.i = strtod(target_number,NULL);
                                    break;
                                case 8:
                                    _quad_pid_config.yaw.d = strtod(target_number,NULL);
                                    break;
                                }
                                // reset
                                target_number_size = 0;
                            } 
                            // is part of the target number
                            else if (isdigit(_esp_01_pid_config[i]) || (_esp_01_pid_config[i] == '.') ){
                                target_number[target_number_size++] = _esp_01_pid_config[i];
                            }
                        }
                        if (pid_state == 9) _esp_01_new_pid_config = ESP_01_OK;
                    }
                }
                _esp_01_pid_config_len = 0;
                memset(_esp_01_pid_config,'\0',sizeof(_esp_01_pid_config));
            }
            break;
        
        default:
            // normal operation
            if(_esp_01_status == ESP_01_STATUS_NORMAL_MODE){
                if ( _esp_01_pid_config_len < sizeof(_esp_01_pid_config)) {
                    _esp_01_pid_config[_esp_01_pid_config_len++] = _esp_01_ch;
                }
            }
            // answer to commands
            else if(_esp_01_status == ESP_01_STATUS_ANSW_CMD){
                if (_esp_01_tcp_answer_len < sizeof(_esp_01_tcp_answer)) {
                    // add to buffer
                    _esp_01_tcp_answer[_esp_01_tcp_answer_len++] = _esp_01_ch;
                }
            }
            break;
        }
    }
    // clean interrup flag
    ESP_01_CLEAN_RX_INT;
}