#include <Arduino.h>
#include "m8-gps.h"
#include <interrupt.h>

void m8_gps_rx_isr();

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("M8_GPS Library");
    Serial.println("Initing M8_GPS...");

    // try to init M8_GPS
    if(m8_gps_init() == M8_GPS_OK)
        Serial.println("M8_GPS INIT OK ! BAUDRATE = " + String(M8_GPS_BAUDRATE));
    else
        Serial.println("failed");

    // set M8_GPS rx interrupt callback
    M8_GPS_RX_INT(m8_gps_rx_isr);
    // enables interrupts
    IntMasterEnable();
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        m8_gps_writeByte(ch);  
    }    

}

void m8_gps_rx_isr(){
    while(M8_GPS_AVAILABLE){
        Serial.write(M8_GPS_READBYTE);
    }
    // clean interrup flag
    M8_GPS_CLEAN_RX_INT;
}