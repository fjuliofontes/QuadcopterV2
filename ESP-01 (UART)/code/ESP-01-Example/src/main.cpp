#include <Arduino.h>
#include "esp-01.h"
#include <interrupt.h>

void esp_01_rx_isr();

#define TARGET_SSID "ITHome"
#define TARGET_PWD "pass1234"

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("ESP_01 Library");
    Serial.println("Initing ESP_01...");

    // try to init ESP_01
    if(esp_01_init() == ESP_01_OK)
        Serial.println("ESP_01 INIT OK ! BAUDRATE = " + String(ESP_01_BAUDRATE));
    else
        Serial.println("failed");

    // set ESP_01 rx interrupt callback
    ESP_01_RX_INT(esp_01_rx_isr);
    // enables interrupts
    IntMasterEnable();

    //esp_01_disconnect_wifi();

    //esp_01_connect_wifi((char*)"HUAWEI-E5776-D797",(char*)"MFQ548R8");

    esp_01_connect_wifi((char*)TARGET_SSID,(char*)TARGET_PWD);
    
    if(esp_01_tcp_connect((char*)"192.168.100.1",(char*)"9090") == ESP_01_OK){
        esp_01_tcp_send((char*)"ola mundo",9); // aprox 8 ms
        //esp_01_tcp_disconnect();
    }
}

void loop() {

    // Read user input if available.  
    while (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        //Serial.print(String((int)ch,16));
          
        if(ch == 0xd){
            esp_01_writeByte('\r');
            esp_01_writeByte('\n');    
        }else{
            esp_01_writeByte(ch);
        }
    }    

}