#include <Arduino.h>
#include "hc-05.h"
#include <interrupt.h>

String command = "";
void hc_05_status_isr();
void hc_05_rx_isr();

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("HC-05 Library");
    Serial.println("Initing HC-05...");

    // try to init hc-05
    if(hc_05_init() == HC_05_OK)
        Serial.println("HC-05 INIT OK ! BAUDRATE = " + String(HC_05_BAUDRATE) + 
        " HC-05 NAME = " + String(HC_05_DEVICE_NAME) + " HC-05 PASS " + String(HC_05_DEVICE_PASS));
    else
        Serial.println("failed");

    // set state interrupt callback
    HC_05_STATE_INT(hc_05_status_isr);
    // set hc-05 rx interrupt callback
    HC_05_RX_INT(hc_05_rx_isr);
    // enables interrupts
    IntMasterEnable();
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        hc_05_writeByte(ch);  
    }    

}

void hc_05_status_isr(){
    Serial.println("Disconected!");
}

void hc_05_rx_isr(){
    while(HC_05_AVAILABLE){
        Serial.write(HC_05_READBYTE);
    }
    // clean interrup flag
    HC_05_CLEAN_RX_INT;
}