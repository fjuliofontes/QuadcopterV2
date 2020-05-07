#include <Arduino.h>
#include "sim800l.h"
#include <interrupt.h>

void sim800l_rx_isr();

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("SIM800L Library");
    Serial.println("Initing SIM800L...");

    // try to init SIM800L
    if(sim800l_init() == SIM800L_OK)
        Serial.println("SIM800L INIT OK ! BAUDRATE = " + String(SIM800L_BAUDRATE));
    else
        Serial.println("failed");

    // set SIM800L rx interrupt callback
    SIM800L_RX_INT(sim800l_rx_isr);
    // enables interrupts
    IntMasterEnable();
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        sim800l_writeByte(ch);  
    }    

}

void sim800l_rx_isr(){
    while(SIM800L_AVAILABLE){
        Serial.write(SIM800L_READBYTE);
    }
    // clean interrup flag
    SIM800L_CLEAN_RX_INT;
}