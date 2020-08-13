#include <Arduino.h>
#include "sim800l.h"
#include <interrupt.h>

sim800l dev;

void sim800l_rx_isr();

void setup() {
    Serial.begin(115200);
    Serial.println("Starting loop...");
    delay(1000);
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("SIM800L Library");
    Serial.println("Initing SIM800L...");

    dev.begin(115200);
    
    Serial.println("Init OK...");

    /*Serial.print(dev.getOperatorsList());
    if(dev.calculateLocation() == SIM800L_OK){
        Serial.println(dev.getLocationCode());
        Serial.println(dev.getLatitude());
        Serial.println(dev.getLongitude());
    }else Serial.println("Error While Calculating Location");*/

    // set SIM800L rx interrupt callback
    SIM800L_RX_INT(sim800l_rx_isr);
    // enables interrupts
    IntMasterEnable();

    while(!dev.simReady()){
        delay(1000);
    };

    Serial.println("Sending sms!");

    Serial.println(dev.sendSms((char*)"+351911599040",(char*)"Teste!"));
    delay(1000);
    
    //read sms
    uint8_t index_list[10];
    uint8_t len;
    
    if(dev.unReadSms(index_list,&len)){
        for(int k = 0; k < len; k++){
            Serial.println(dev.readSms(index_list[k]));
        }
    }
    
}

void loop() {

    // Read user input if available.  
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        dev.writeByte(ch);  
    }    

}

