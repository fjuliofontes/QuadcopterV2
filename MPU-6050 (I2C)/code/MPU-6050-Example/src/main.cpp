#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#define MPU6050_CAL_SAMPLES 2000
#define MPU6050_GYRO_SCALE_FACTOR 65.5
#define MPU6050_ACCEL_SCALE_FACTOR 4096.F
#define MPU6050_READ_FREQ 250 // 250hz
#define MPU6050_GYRO_ANGLE_FACTOR 16375.F // MPU6050_READ_FREQ*MPU6050_GYRO_SCALE_FACTOR
#define MPU6050_READ_PERI 4000 // 1 / MPU6050_READ_FREQ
#define MPU6050_RAD_TO_DEG 57.296

MPU6050 accelgyro;

// for mpu6050 readings
int16_t ax, ay, az;
int16_t gx, gy, gz;

// for mpu6050 calibration
float gyro_x_cal = 0, gyro_y_cal = 0, gyro_z_cal = 0;
float accel_x_cal = 0, accel_y_cal = 0, accel_z_cal = 0;

// for angle measurement based on gyro
float angle_x = 0, angle_y = 0, angle_z = 0;
float gyro_x = 0, gyro_y = 0, gyro_z = 0;

// for angle measurement based on accel
float accel_x = 0, accel_y = 0, accel_z = 0;
float XY_distance, YZ_distance, ZX_distance;
float phi, theta, psi;

// flight variables
float pitch = 0, roll = 0, yaw = 0;

// for status 
unsigned long last_loop = 0;
bool blinkState = false;
uint32_t count = 0;
uint8_t state = 0;

void setup() {
    // Init i2c pins
    Wire = TwoWire(1);
    Wire.begin();

    // Config baudrate
    Serial.begin(115200);

    // configure Arduino LED pin for output
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    delay(500); // wait 500 ms

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // config MPU6050 resolution
    accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
    accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    delay(500); // wait 500 ms

    Serial.print("Starting mpu6050 gyro calibration ");
    for(uint16_t i = 0; i < MPU6050_CAL_SAMPLES; i ++){
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        gyro_x_cal += gx;
        gyro_y_cal += gy;
        gyro_z_cal += gz;
        delay(5);
        if((i%40) == 0) Serial.print('.'); // print '.' at every +/- 200ms
        if((i%100) == 0) { blinkState = !blinkState; digitalWrite(BLUE_LED,blinkState);} // blink every 500 ms
    }
    Serial.println(" done!");

    // Get gyro offsets
    gyro_x_cal = (gyro_x_cal / MPU6050_CAL_SAMPLES) * -1;
    gyro_y_cal = (gyro_y_cal / MPU6050_CAL_SAMPLES) * -1;
    gyro_z_cal = (gyro_z_cal / MPU6050_CAL_SAMPLES) * -1;
    Serial.println("Gyro X offset: "  + String(gyro_x_cal) );
    Serial.println("Gyro Y offset: "  + String(gyro_y_cal) );
    Serial.println("Gyro Z offset: "  + String(gyro_z_cal) );

    Serial.print("Starting mpu6050 accel calibration ");
    for(uint16_t i = 0; i < MPU6050_CAL_SAMPLES; i ++){
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        accel_x_cal += ax;
        accel_y_cal += ay;
        accel_z_cal += az;
        delay(5);
        if((i%40) == 0) Serial.print('.'); // print '.' at every +/- 200ms
        if((i%100) == 0) { blinkState = !blinkState; digitalWrite(RED_LED,blinkState);} // blink every 500 ms
    }
    Serial.println(" done!");

    // Get accel offsets
    accel_x_cal = (accel_x_cal / MPU6050_CAL_SAMPLES) * -1;
    accel_y_cal = (accel_y_cal / MPU6050_CAL_SAMPLES) * -1;
    accel_z_cal = MPU6050_ACCEL_SCALE_FACTOR - (accel_z_cal / MPU6050_CAL_SAMPLES); // for 1 g cal
    Serial.println("Accel X offset: "  + String(accel_x_cal) );
    Serial.println("Accel Y offset: "  + String(accel_y_cal) );
    Serial.println("Accel Z offset: "  + String(accel_z_cal) );

    last_loop = micros();
}

void loop() {
    
    // takes aprox 2 ms
    if((micros() - last_loop) >= MPU6050_READ_PERI){
        // update last_loop time value
        last_loop = micros();

        ///////////MPU6050-READING//////////////////////
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        ////////////////////////////////////////////////

        ///////////OFFSETS//////////////
        // Add accel calibration offset
        accel_x = ax + accel_x_cal;
        accel_y = ay + accel_y_cal;
        accel_z = az + accel_z_cal;
        // Add gyro calibration offset
        gyro_x = gx + gyro_x_cal;
        gyro_y = gy + gyro_y_cal;
        gyro_z = gz + gyro_z_cal;
        ////////////////////////////////

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
        // Integrate the angle
        angle_x += gyro_x;
        angle_y += gyro_y;
        angle_z += gyro_z;
        // calculates sqrt values
        XY_distance = sqrtf(accel_x*accel_x + accel_y*accel_y);
        YZ_distance = sqrtf(accel_y*accel_y + accel_z*accel_z);
        ZX_distance = sqrtf(accel_z*accel_z + accel_x*accel_x);
        // calculates angles
        theta = atanf(accel_x/YZ_distance) * MPU6050_RAD_TO_DEG;
        psi   = atanf(accel_y/ZX_distance) * MPU6050_RAD_TO_DEG;
        phi   = atanf(XY_distance/accel_z) * MPU6050_RAD_TO_DEG;
        ////////////////////////////////////////////////////////////////

        /////////////////////////REMOVE GYRO DRIFT//////////////////////
        pitch += gyro_x;
        roll += gyro_y;
        yaw += gyro_z;
        // for tranfering pitch to roll
        pitch += roll * sin(gyro_z * 0.01745); 
        roll -= pitch * sin(gyro_z * 0.01745);     
        // removing drift
        pitch = pitch * 0.9996 + psi * 0.0004;     
        roll = roll * 0.9996 + theta * -0.0004;        
        //angle_x = angle_x * 0.95 + psi*0.05;
        //angle_y = angle_y * 0.95 + theta*-0.05;
        ////////////////////////////////////////////////////////////////

        // increment counter
        count ++;
    }

    // print every 900ms 
    // we need to print the remaning parts in 2 ms
    // takes aprox 1.5ms
    if (count >= 75){
        count = 0;
        switch (state){
        case 0:
            Serial.print(String(theta,2) + ' ');
            Serial.print(String(psi,2) + ' ');
            state ++;
            break;
        case 1:
            Serial.print(String(phi,2)+ ' ');
            Serial.print(String(pitch,2)+ ' ');
            state ++;
            break;
        case 2:
            Serial.print(String(roll,2)+ ' ');
            Serial.print(String(yaw,2)+ ' ');
            Serial.println();
            blinkState = !blinkState; 
            digitalWrite(GREEN_LED,blinkState);
            state = 0;
            break;
        
        default:
            break;
        }
    }

    // end program whenever user types 'e' key
    if(Serial.available()){
        if(Serial.read() == 'e'){
            // turn led off
            blinkState = false; 
            digitalWrite(GREEN_LED,blinkState);
            // stop program
            while (1);
        }
    }
}