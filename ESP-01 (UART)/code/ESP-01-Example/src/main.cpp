#include <Arduino.h>
#include "esp-01.h"
#include <interrupt.h>

void esp_01_rx_isr();

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
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        esp_01_writeByte(ch);  
    }    

}

void esp_01_rx_isr(){
    while(ESP_01_AVAILABLE){
        Serial.write(ESP_01_READBYTE);
    }
    // clean interrup flag
    ESP_01_CLEAN_RX_INT;
}