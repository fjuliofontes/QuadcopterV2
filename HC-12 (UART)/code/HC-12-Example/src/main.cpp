#include <Arduino.h>
#include "hc-12.h"
#include <interrupt.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("HC_12 Library");
    Serial.println("Initing HC_12...");

    // try to init HC_12
    if(hc_12_init() == HC_12_OK)
        Serial.println("HC_12 INIT OK ! BAUDRATE = " + String(HC_12_BAUDRATE));
    else
        Serial.println("failed");

    hc_12_version();
    hc_12_rx_params();

    // set HC_12 rx interrupt callback
    HC_12_RX_INT(hc_12_rx_isr);
    // enables interrupts
    IntMasterEnable();
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        hc_12_writeByte(ch);  
    }    

}
