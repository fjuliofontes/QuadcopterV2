
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

#define MPU6050_CAL_SAMPLES 2000

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int32_t gyro_x_cal = 0,gyro_y_cal = 0, gyro_z_cal = 0;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
boolean set_gyro_angles = false;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;

long acc_total_vector;

unsigned long last_loop = 0;

#define LED_PIN BLUE_LED
bool blinkState = false;

unsigned long startTime = 0 , endTime;

void setup() {
    Wire = TwoWire(1);
    Wire.begin();

    Serial.begin(115200);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);

    Serial.print("Starting mpu6050 calibration ");
    for(int i = 0; i < MPU6050_CAL_SAMPLES; i ++){
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        gyro_x_cal += gx;
        gyro_y_cal += gy;
        gyro_z_cal += gz;
        delay(5);
        if((i%40) == 0) Serial.print('.'); // print '.' at every +/- 200ms
    }
    Serial.println(" done!");

    gyro_x_cal = (gyro_x_cal / MPU6050_CAL_SAMPLES) * -1;
    gyro_y_cal = (gyro_y_cal / MPU6050_CAL_SAMPLES) * -1;
    gyro_z_cal = (gyro_z_cal / MPU6050_CAL_SAMPLES) * -1;

    accelgyro.setXGyroOffset((int16_t)gyro_x_cal);
    accelgyro.setYGyroOffset((int16_t)gyro_y_cal);
    accelgyro.setZGyroOffset((int16_t)gyro_z_cal);

    // Get offsets
    Serial.println("Gyro X offset: "  + String(accelgyro.getXGyroOffset()) );
    Serial.println("Gyro Y offset: "  + String(accelgyro.getYGyroOffset()) );
    Serial.println("Gyro Z offset: "  + String(accelgyro.getZGyroOffset()) );

    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);

    last_loop = micros();
}

void loop() {
    if((micros() - last_loop) > 4000){
        last_loop = micros();
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

        gx += gyro_x_cal;
        gy += gyro_y_cal;
        gz += gyro_z_cal;

  //Gyro angle calculations
  //0.0000611 = 1 / (250Hz / 65.5)
  angle_pitch += gx * 0.0000611;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_roll += gy * 0.0000611;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gz * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gz * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((ax*ax)+(ay*ay)+(az*az));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)ay/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)ax/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  //Place the MPU-6050 spirit level and note the values in the following two lines for calibration
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value

        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);

        Serial.println(String(angle_pitch_output));
    }
}