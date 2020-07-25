#include <Arduino.h>

#include <interrupt.h>
#include <math.h>

#include "hc-05.h"
#include "hc-sr04.h"
#include "HMC5883L.h"
#include "m8-gps.h"
#include "MPU6050.h"
#include "esp-01.h"
#include "quad_pins.h"

////////////////MPU-6050///////////////
MPU6050 accelgyro;
// for angle measurement based on gyro
float gyro_x = 0, gyro_y = 0, gyro_z = 0;
// for angle measurement based on accel
float accel_x = 0, accel_y = 0, accel_z = 0;
float XY_distance, YZ_distance, ZX_distance;
float phi, theta, psi;
// flight variables
float pitch = 0, roll = 0, yaw = 0;
//////////////////////////////////////

////////////////HMC5883L///////////////
HMC5883L mag = HMC5883L(0);
// for magnetic measurements 
float magnetic_x, magnetic_y, magnetic_z, heading;
// for tilt correction
float Xh, Yh;
//////////////////////////////////////

////////////////GPS///////////////
struct m8_gps gps_coords;
//////////////////////////////////

////////////////LOOP///////////////
unsigned long last_loop = 0;
uint32_t count = 0;
uint8_t retval = 0;
//////////////////////////////////////

void setup() {
    // start initing serial port
    Serial.begin(115200);
    
    /* --- Init LED's and Analogs --- */
    quad_init();

    // let voltages stable
    delay(3000);

    // print system information
    quad_redOn();
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");
    Serial.println("System Battery : " + String(quad_readBatteryVoltage()) + " Volt");

    /* --- Init i2c pins --- */
    Wire = TwoWire(1);
    Wire.begin(); 
    delay(200);

    /* --- Init HC-05 --- */
    Serial.println("Initing HC-05...");
    if(hc_05_init() == HC_05_OK){
        Serial.println("HC-05 INIT OK ! BAUDRATE = " + String(HC_05_BAUDRATE) + 
        " HC-05 NAME = " + String(HC_05_DEVICE_NAME) + " HC-05 PASS " + String(HC_05_DEVICE_PASS));
        // set state interrupt callback
        HC_05_STATE_INT(hc_05_status_isr);
        // set hc-05 rx interrupt callback
        HC_05_RX_INT(hc_05_rx_isr);
    }else Serial.println("failed");

    delay(200);

    /* --- Init HC-SR04 --- */
    Serial.println("Initing HC-SR04...");
    hc_sr04_init();
    delay(200);

    /* --- Init M8_GPS --- */
    Serial.println("Initing M8_GPS...");
    //init M8_GPS
    //// set baudrate
    if(m8_gps_init(M8_GPS_BAUDRATE) == M8_GPS_OK){
        Serial.println("M8_GPS INIT OK ! BAUDRATE = " + String(M8_GPS_BAUDRATE));
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
    }else Serial.println("failed");
    delay(200);

    /* --- Init ESP-01 --- */
    Serial.println("Initing ESP_01...");
    if(esp_01_init() == ESP_01_OK){
        Serial.println("ESP_01 INIT OK ! BAUDRATE = " + String(ESP_01_BAUDRATE));
        /// connect to wifi
        if( esp_01_connect_wifi((char*)TARGET_SSID,(char*)TARGET_PWD) == ESP_01_OK){
            /// open tcp connection
            if(esp_01_tcp_connect((char*)"192.168.100.1",(char*)"9090") == ESP_01_OK){
                /// send saudations
                esp_01_tcp_send((char*)"Hello from Quadcopter V2\r\n",26); // takes to long - 3462us
            }
        }
        /// set interrupt callback
        ESP_01_RX_INT(esp_01_rx_isr);
    } else Serial.println("failed");

    /* --- Init HMC5883 --- */
    Serial.println("Initing HMC5883...");
    if(!mag.begin()){
        // There was a problem detecting the HMC5883 ... check your connections 
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    }else{
        mag.calibrate(30); // calibrate for 30 seconds
    }
    delay(2000);

    /* --- Init MPU6050 --- */
    Serial.println("Initing MPU6050...");
    accelgyro.initialize();
    if(accelgyro.testConnection()){
        Serial.println("MPU6050 connection successful");
        // config MPU6050 resolution
        accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
        accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
        delay(200);
        accelgyro.calibrate();
    }else Serial.println("MPU6050 connection failed");
    delay(2000);

    // enables interrupts
    IntMasterEnable();

    quad_blueOn();
}

void loop() {
    // elapsed time = 0.824ms - should repeat at every 4 ms
    if((micros() - last_loop) >= MPU6050_READ_PERI){
        // update last_loop time value
        last_loop = micros();

        ///////////MPU6050-READING//////////////////////
        accelgyro.getMotion6(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
        ////////////////////////////////////////////////

        ///////////CONVERSIONS//////////////
        // convert accelaration to g-force
        accel_x = accel_x / MPU6050_ACCEL_SCALE_FACTOR;
        accel_y = accel_y / MPU6050_ACCEL_SCALE_FACTOR;
        accel_z = accel_z / MPU6050_ACCEL_SCALE_FACTOR;
        // Convert gyro output to deg
        gyro_x /= MPU6050_GYRO_ANGLE_FACTOR;
        gyro_y /= MPU6050_GYRO_ANGLE_FACTOR;
        gyro_z /= MPU6050_GYRO_ANGLE_FACTOR;
        ////////////////////////////////

        ///////////ANGLES//////////////////////////////////////////////
        // calculates sqrt values
        XY_distance = sqrtf(accel_x*accel_x + accel_y*accel_y);
        YZ_distance = sqrtf(accel_y*accel_y + accel_z*accel_z);
        ZX_distance = sqrtf(accel_z*accel_z + accel_x*accel_x);
        // calculates angles
        theta = atanf(accel_x/YZ_distance) * RAD_TO_DEG;
        psi   = atanf(accel_y/ZX_distance) * RAD_TO_DEG;
        phi   = atanf(XY_distance/accel_z) * RAD_TO_DEG;
        ////////////////////////////////////////////////////////////////

        /////////////////////////REMOVE GYRO DRIFT//////////////////////
        pitch += gyro_x;
        roll += gyro_y;
        yaw += gyro_z;
        // for tranfering pitch to roll
        pitch += roll * sin(gyro_z * DEG_TO_RAD);  // pi/180 = 0.01745
        roll -= pitch * sin(gyro_z * DEG_TO_RAD);     
        // removing drift
        pitch = pitch * 0.9996 + psi * 0.0004;     
        roll = roll * 0.9996 + theta * -0.0004;        
        ////////////////////////////////////////////////////////////////

        ///////////HMC5883L-READING//////////////////////
        mag.getMotion(&magnetic_x,&magnetic_y,&magnetic_z);
        ////////////////////////////////////////////////

        ///////////CALCULATIONS/////////////////
        // tilt corrections
        Xh = magnetic_x*cos(pitch*DEG_TO_RAD) + magnetic_y*sin(roll*DEG_TO_RAD)*sin(pitch*DEG_TO_RAD) 
                                    - magnetic_z*cos(roll*DEG_TO_RAD)*sin(pitch*DEG_TO_RAD);
        Yh = magnetic_y*cos(roll*DEG_TO_RAD) + magnetic_z*sin(roll*DEG_TO_RAD);
        // heading calculation
        if(Xh < 0)                    heading = 180 - atan2(Yh,Xh)*RAD_TO_DEG;
        else if((Xh > 0) && (Yh < 0)) heading = -atan2(Yh,Xh)*RAD_TO_DEG;
        else if((Xh > 0) && (Yh > 0)) heading = 360-atan2(Yh,Xh)*RAD_TO_DEG;
        else if((Xh = 0) && (Yh < 0)) heading = 90;
        else if((Xh = 0) && (Yh > 0)) heading = 270;
        //heading = -atan2(magnetic_y, magnetic_x);
        ////////////////////////////////////////

        ///////////CORRECTIONS////////////////////
        //heading += 4.869; // north correction
        // Correct for when signs are reversed.
        if(heading < 0)
            heading += 360;
        // Check for wrap due to addition of declination.
        if(heading > 360)
            heading -= 360;
        /////////////////////////////////////////

        count ++;
    }

    // at 1 and 1 second - elapsed time = 1600 us aprox 1.6ms
    else if((count >= 250) && (count <= 253)){
        //unsigned long meas = micros();
        switch ((uint8_t)(count-250)){
        case 0:
            Serial.print("Pitch : " + String(pitch,2));
            break;
        case 1:
            Serial.print(" Roll : " + String(roll,2));
            break;
        case 2:
            Serial.println(" Yaw : " + String(yaw,2));
            break;
        case 3:
            Serial.println("Heading : " + String(heading,2));
            break;
        
        default:
            break;
        }
        count++;
        //unsigned long stop = micros();
        //Serial.println("elapsed time: " + String(stop-meas));
    }

    // data received - elapsed time 1115 aprox 1.1ms
    else if((count == 300) && m8_gps_pending_read()){
        count = 50; 
        //unsigned long meas = micros();
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
        //unsigned long stop = micros();
    }    //Serial.println("elapsed time: " + String(stop-meas));
    else if(count >= 300){
        count = 50;
    }


}