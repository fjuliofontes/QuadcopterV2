#include <Arduino.h>
#include "HMC5883L.h"

#define M_PI 3.141592F

/* Assign a unique ID to this sensor at the same time */
HMC5883L mag = HMC5883L(0);

float magnetic_x, magnetic_y, magnetic_z;

float hmc5883l_max_x = magnetic_x,hmc5883l_max_y = magnetic_y,hmc5883l_max_z = magnetic_z;
float hmc5883l_min_x = magnetic_x,hmc5883l_min_y = magnetic_y,hmc5883l_min_z = magnetic_z;

float hmc5883l_x_off, hmc5883l_y_off, hmc5883l_z_off;
float hmc5883l_x_scf, hmc5883l_y_scf, hmc5883l_z_scf;

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

    delay(1000); // wait 500 ms

    // initialize device
    Serial.println("Initializing I2C devices...");
    
    if(!mag.begin()){
        // There was a problem detecting the HMC5883 ... check your connections 
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while(1);
    }
    
    delay(1000); // wait 500 ms

    digitalWrite(RED_LED,1);

    Serial.println("HMC5883 Magnetometer Test"); Serial.println("");

    //mag.calibrate(30); // calibrate for 30 seconds

    digitalWrite(RED_LED,0); 

}

void loop() {

    /* Get a new sensor event */ 
    mag.getMotion(&magnetic_x,&magnetic_y,&magnetic_z);
 
    /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
    Serial.print("X: "); Serial.print(magnetic_x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(magnetic_y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(magnetic_z); Serial.print("  ");Serial.println("uT");

    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    //float heading = atan2(magnetic_y, magnetic_x);
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -1* 46' W, which is ~1.766 Degrees, or (which we need) 0.0309 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    //float declinationAngle = 0.0309;
    //heading += declinationAngle;
    
    // Correct for when signs are reversed.
    //if(heading < 0)
    //    heading += 2*PI;
        
    // Check for wrap due to addition of declination.
    //if(heading > 2*PI)
    //    heading -= 2*PI;
    
    
    // Convert radians to degrees for readability.
    //float headingDegrees = heading * 180/M_PI; 
    
    //Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
    
    delay(10);
    
}