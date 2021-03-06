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
char _uart_rx_buffer[100];
char _tcp_send_buffer[500];
char _tcp_recv_buffer[100];
char _uart_tx_buffer[500];
uint16_t _tcp_send_buffer_len = 0;
uint16_t _uart_rx_buffer_len = 0;
uint16_t _tcp_recv_buffer_len = 0;
uint16_t _uart_tx_buffer_len = 0;

// Use WiFiClient class to create TCP connections
WiFiClient client;
bool isConnectedTCPServer = false;
bool isToConnectTCPServer = false;

void setup() {
    // setup variables
    uint8_t i=0, j=0, n=0;
    bool isKnown = false;
    // start by initing serial port for debug 
    Serial.begin(115200);
    Serial.println(">OK");
    // change wifi mode to wifi sta and disconnect from possible connected network
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // enter in discovery mode and list access points
    isKnown = false;
    // loop until reaching a known network
    while(isKnown == false){
        //Serial.println("Scanning Networks ...");
        n = WiFi.scanNetworks();
        // go through all scanned ssids and check if we have the authentication parameters
        for (i = 0; i < n; i++){
            //Serial.println(WiFi.SSID(i));
            for(j = 0; j < NUMBER_OF_KNOWN_SSIDs; j++){
                // compare ssid with known ssids
                if(strcmp(ssid[j],WiFi.SSID(i).c_str()) == 0){
                    isKnown = true;
                    break;
                }
            }
            // already founded
            if(isKnown) break;
        }
        if(isKnown == false){
            //Serial.println("No known networks founded ...");
            delay(10000); // wait 10 seconds and try again
        }
    }
    // try to connect if isknown
    //Serial.println("Trying to connect to SSID: " + String(ssid[j]));
    WiFi.begin(ssid[j], password[j]);
    
    while (WiFi.waitForConnectResult() != WL_CONNECTED){
        //Serial.println("Connection failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    // configurations for OTA

    // change ota port
    ArduinoOTA.setPort(8266);

    // change esp hostname
    ArduinoOTA.setHostname("ESP8266-JF");

    // set password
    // ArduinoOTA.setPassword((const char *)"123");

    // set ota callbacks
    ArduinoOTA.onStart([]() {
        Serial.println("OTA onStart()...");
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("OTA onEnd()...");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("\rOTA onProgress(): %u%%", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("OTA onError() [%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Authentication Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin error");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connection Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Error while receiving");
        else if (error == OTA_END_ERROR) Serial.println("End failure");
    });

    // start ota
    ArduinoOTA.begin();

    // Ok ! done, print IP
    //Serial.print("OK, IP: ");
    //Serial.println(WiFi.localIP());

    // go to loop();
    last_time = millis();
}

void loop() {
    // check possible updates
    ArduinoOTA.handle();

    // read commands from uart rx
    if(Serial.available()){
        Serial.readBytesUntil('\r',_uart_rx_buffer,sizeof(_uart_rx_buffer));
        //// get readen bytes
        _uart_rx_buffer_len = strlen(_uart_rx_buffer);
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
                        Serial.println(">OK");
                        isToConnectTCPServer = true;
                    }
                    else Serial.println(">ERROR");
                } else Serial.println(">ERROR");
            }

            //// #TPCCLOSE
            else if(String(_uart_rx_buffer).indexOf("#TPCCLOSE") != -1){
                isToConnectTCPServer = false;
                Serial.println(">OK");
            }
            
            //// just confirm that you are alive
            else{
                Serial.println(">OK");
            }
            
        }else{
            // concatenate to tcp send buffer
            strncat(_tcp_send_buffer, _uart_rx_buffer ,_uart_rx_buffer_len);

            // update _tcp_send_buffer_len
            _tcp_send_buffer_len = strlen(_tcp_send_buffer);
        }

        // clean buffer
        memset(_uart_rx_buffer,'\0',_uart_rx_buffer_len);
    }

    // try connecting to a tcp server every 5 seconds if isToConnectTCPServer
    if(((millis()-last_time) >= 5000) && (!isConnectedTCPServer) && (isToConnectTCPServer)){
        // update last time
        last_time = millis();

        // check connection status
        if (client.connect(host, port)){

            // flag isConnectedTCPServer
            isConnectedTCPServer = true;

            // send hello to the server
            client.println("Hello from Quadcopter V2");

            // send connected via tx
            Serial.println(">CONNECTED");
        }
    }

    // if connected to tcp server check if new messages and print older ones
    if(isConnectedTCPServer && isToConnectTCPServer){

        //// check if have characters to send 
        if(_tcp_send_buffer_len > 0){
            //// send it
            client.print(_tcp_send_buffer);
            //// clean buffer
            memset(_tcp_send_buffer,'\0',_tcp_send_buffer_len);
            //// update _tcp_send_buffer_len
            _tcp_send_buffer_len = 0;
        }

        //// read from tcp server and fill buffer
        if(client.available()){
            //// get bytes
            client.readBytesUntil('\n',_tcp_recv_buffer,sizeof(_tcp_recv_buffer));
            
            //// count bytes readen
            _tcp_recv_buffer_len = strlen(_tcp_recv_buffer);

            //// concatenate to tx send buffer
            strncat(_uart_tx_buffer, _tcp_recv_buffer ,_tcp_recv_buffer_len);

            //// clean buffer
            memset(_tcp_recv_buffer,'\0',_tcp_recv_buffer_len);

            //// update pending bytes to send
            _uart_tx_buffer_len = strlen(_uart_tx_buffer);
        }

    }else if(isConnectedTCPServer && !isToConnectTCPServer){
        //// disconnect 
        client.stop();

        //// flag isConnectedTCPServer
        isConnectedTCPServer = false;
    }

    if(_uart_tx_buffer_len > 0){
        Serial.print(String(_uart_tx_buffer));
        Serial.println();

        //// clean buffer
        memset(_uart_tx_buffer,'\0',_uart_tx_buffer_len);

        //// update len
        _uart_tx_buffer_len = 0;
    }

}