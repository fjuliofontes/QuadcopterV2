#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define NUMBER_OF_KNOWN_SSIDs 3
#define MAX_STRING_SIZE 20

char ssid[NUMBER_OF_KNOWN_SSIDs][MAX_STRING_SIZE] ={ 
    "ITHome\0",
    "HUAWEI-E5776-D797\0",
    "WiFi-Tixa\0"
};

char password[NUMBER_OF_KNOWN_SSIDs][MAX_STRING_SIZE] = {   
    "pass1234\0",
    "MFQ548R8\0",
    "atixacheiramal\0"
};

char* host = (char*)"000.000.000.000\0";
uint16_t port = 0;

unsigned long last_time = 0;
char _uart_rx_buffer[500] = {'\0'};
char _uart_tx_buffer[500] = {'\0'};
uint16_t _uart_rx_buffer_len = 0;
uint16_t _uart_tx_buffer_len = 0;

// Use WiFiClient class to create TCP connections
WiFiClient client;
bool isConnectedTCPServer = false;
bool isToConnectTCPServer = false;
bool ota_initialized = false;

void connect_to_wifi() {
    // setup variables
    uint8_t i=0, j=0, n=0;
    bool isKnown = false;
    // change wifi mode to wifi sta and disconnect from possible connected network
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // enter in discovery mode and list access points
    // search a known network
    //Serial.println("Scanning Networks ...");
    n = WiFi.scanNetworks();
    // go through all scanned ssids and check if we have the authentication parameters
    for (i = 0; i < n; i++) {
        //Serial.println(WiFi.SSID(i));
        for(j = 0; j < NUMBER_OF_KNOWN_SSIDs; j++){
            // compare ssid with known ssids
            if(strcmp(ssid[j],WiFi.SSID(i).c_str()) == 0){
                isKnown = true;
                break;
            }
        }
        if (isKnown) {
            break;
        }
    }

    if (isKnown) {
        // try to connect if isknown
        // Serial.printf("Trying to connect to SSID[%d]: %s",j,ssid[j]);
        WiFi.begin(ssid[j], password[j]);
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            // Serial.println("Connection failed! Rebooting...");
            WiFi.disconnect();
        }
    }
}

void configure_ota() {
    // configurations for OTA

    // change ota port
    ArduinoOTA.setPort(8266);

    // change esp hostname
    ArduinoOTA.setHostname("ESP8266-JF");

    // set password
    // ArduinoOTA.setPassword((const char *)"123");

    // set ota callbacks
    ArduinoOTA.onStart([]() {
        Serial.printf("OTA onStart()...\r");
    });

    ArduinoOTA.onEnd([]() {
        Serial.printf("OTA onEnd()...\r");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("\rOTA onProgress(): %u%%", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA onError() [%u]: \r", error);
        if (error == OTA_AUTH_ERROR) Serial.printf("Authentication Failed\r");
        else if (error == OTA_BEGIN_ERROR) Serial.printf("Begin error\r");
        else if (error == OTA_CONNECT_ERROR) Serial.printf("Connection Failed\r");
        else if (error == OTA_RECEIVE_ERROR) Serial.printf("Error while receiving\r");
        else if (error == OTA_END_ERROR) Serial.printf("End failure\r");
    });

    // start ota
    ArduinoOTA.begin();

    ota_initialized = true;
}

void setup() {
    // start by initing serial port for debug 
    Serial.begin(115200);
    Serial.printf(">OK\r");

    // Ok ! done, print IP
    //Serial.print("OK, IP: ");
    //Serial.println(WiFi.localIP());

    // go to loop();
    last_time = millis();
}

void loop() {
    if (ota_initialized && (WiFi.status() == WL_CONNECTED)) {
        // check possible updates
        ArduinoOTA.handle();
    } else if (WiFi.status() == WL_CONNECTED) {
        configure_ota();
    }

    // read commands from uart rx
    if(Serial.available()){
        _uart_rx_buffer_len += Serial.readBytesUntil('\r',&_uart_rx_buffer[_uart_rx_buffer_len],sizeof(_uart_rx_buffer)-_uart_rx_buffer_len);
        _uart_rx_buffer[_uart_rx_buffer_len] = '\0';

        // check if is a inner command
        if(String(_uart_rx_buffer).indexOf('#') != -1){
            
            //// #TCP,IP,PORT
            if(String(_uart_rx_buffer).indexOf("#TCP,") != -1){
                //// init ip and port variables
                String ip = "";
                String po = "";
                //// try set ip and port
                ip = String(_uart_rx_buffer).substring(5);
                po = ip.substring(ip.indexOf(',')+1,ip.length());
                ip = ip.substring(0,ip.indexOf(','));
                //// validate ip and port
                if((ip != "") && (po != "")){
                    //// try cpy ip to host
                    strcpy(host,ip.c_str());
                    //// try convert port o int
                    port = po.toInt();
                    if(port != 0){
                        Serial.printf(">OK\r");
                        isToConnectTCPServer = true;
                    }
                    else Serial.printf(">ERROR\r");
                } else Serial.printf(">ERROR\r");
            }

            //// #TPCCLOSE
            else if(String(_uart_rx_buffer).indexOf("#TPCCLOSE") != -1){
                isToConnectTCPServer = false;
                Serial.printf(">OK\r");
            }
            
            //// just confirm that you are alive
            else{
                Serial.printf(">OK\r");
            }

            //// clean buffer
            memset(_uart_rx_buffer,'\0',_uart_rx_buffer_len);
            //// reset length
            _uart_rx_buffer_len = 0;
        }  
    }

    if (isToConnectTCPServer && (WiFi.status() != WL_CONNECTED)) {
        connect_to_wifi();
    }

    // try connecting to a tcp server every 5 seconds if isToConnectTCPServer
    if(((millis()-last_time) >= 5000) && (WiFi.status() == WL_CONNECTED) && (!isConnectedTCPServer) && (isToConnectTCPServer) ){
        // update last time
        last_time = millis();

        // check connection status
        if (client.connect(host, port)){

            // flag isConnectedTCPServer
            isConnectedTCPServer = true;

            // send hello to the server
            client.printf("Hello from Quadcopter V2\n");

            // send connected via tx
            Serial.printf(">CONNECTED\r");
        }
    }

    // if connected to tcp server check if new messages and print older ones
    if(isConnectedTCPServer && isToConnectTCPServer && (client.status() != CLOSED)){

        //// check if have characters to send 
        if(_uart_rx_buffer_len > 0){
            //// send it
            client.print(_uart_rx_buffer);
            //// clean buffer
            memset(_uart_rx_buffer,'\0',_uart_rx_buffer_len);
            //// update _uart_rx_buffer
            _uart_rx_buffer_len = 0;
        }

        //// read from tcp server and fill buffer
        if(client.available()){
            //// get bytes
            _uart_tx_buffer_len += client.readBytesUntil('\r',&_uart_tx_buffer[_uart_tx_buffer_len],sizeof(_uart_tx_buffer)-_uart_tx_buffer_len);
            //// add string terminator
            _uart_tx_buffer[_uart_tx_buffer_len] = '\0';
        }

    }
    else if(isConnectedTCPServer && !isToConnectTCPServer) {
        //// disconnect 
        client.stop();

        //// flag isConnectedTCPServer
        isConnectedTCPServer = false;
    } 
    else if (isConnectedTCPServer && (client.status() == CLOSED) ) {
        //// disconnect
        client.stop();
        // advertise
        Serial.printf(">DISCONNECTED\r");
        //// flag isConnectedTCPServer
        isConnectedTCPServer = false;
    }

    if(_uart_tx_buffer_len > 0){
        Serial.printf("%s\r",_uart_tx_buffer);
        //// clean buffer
        memset(_uart_tx_buffer,'\0',_uart_tx_buffer_len);
        //// update len
        _uart_tx_buffer_len = 0;
    }

}