#include <Arduino.h>
#include "m8-gps.h"
#include <interrupt.h>

struct m8_gps gps_coords;
uint8_t retval;

void setup() {
    Serial.begin(115200);
    delay(3000); // delay 3 seconds 

    Serial.println("Starting loop...");
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");

    // put your setup code here, to run once:
    Serial.println("M8_GPS Library");
    Serial.println("Initing M8_GPS...");
    //init M8_GPS
    //// set baudrate
    if(m8_gps_init(M8_GPS_BAUDRATE) == M8_GPS_OK) Serial.println("M8_GPS INIT OK ! BAUDRATE = " + String(M8_GPS_BAUDRATE));
    else Serial.println("failed");
    //// change measurement rate
    m8_gps_setMeasRate(M8_GPS_MEASRATE, M8_GPS_NAVRATE);
    //// disable un-necessary messages
    m8_gps_setMsgRate(M8_GPS_RMC_MESSAGE, M8_GPS_MESSAGE_DISABLED);
    m8_gps_setMsgRate(M8_GPS_VTG_MESSAGE, M8_GPS_MESSAGE_DISABLED);
    m8_gps_setMsgRate(M8_GPS_GGA_MESSAGE, M8_GPS_MESSAGE_DISABLED);
    m8_gps_setMsgRate(M8_GPS_GSA_MESSAGE, M8_GPS_MESSAGE_DISABLED);
    m8_gps_setMsgRate(M8_GPS_GSV_MESSAGE, M8_GPS_MESSAGE_DISABLED);
    //// set M8_GPS rx interrupt callback
    M8_GPS_RX_INT(m8_gps_rx_isr);
    
    // enables global interrupts
    IntMasterEnable();
}   

void loop() {

    // Read user input if available.  
    /*
    if (Serial.available()){  
        delay(10); // The DELAY!
        char ch = Serial.read();
        Serial.write(ch);
        m8_gps_writeByte(ch);  
    }    
    */
    // data received
    if(m8_gps_pending_read()){

        retval = m8_gps_getCoords(&gps_coords);

        if(retval == M8_GPS_OK){
            Serial.print(String(gps_coords.lat.degrees) + "°");
            Serial.print(String(gps_coords.lat.minutes) + "'");
            Serial.print(String(gps_coords.lat.seconds) + "''");
            Serial.println(gps_coords.lat.direction);

            Serial.print(String(gps_coords.lon.degrees) + "°");
            Serial.print(String(gps_coords.lon.minutes) + "'");
            Serial.print(String(gps_coords.lon.seconds) + "''");
            Serial.println(gps_coords.lon.direction);
        }
    }
}
