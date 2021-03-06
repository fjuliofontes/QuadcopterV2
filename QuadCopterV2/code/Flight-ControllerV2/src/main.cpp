#include <Arduino.h>

#include <interrupt.h>
#include <math.h>
//#include <gpio.h>

#include "hc-05.h"
#include "hc-sr04.h"
#include "HMC5883L.h"
#include "m8-gps.h"
#include "MPU6050.h"
#include "esp-01.h"
#include "hc-12.h"
#include "sim800l.h"
#include "MS5611.h"
#include "quad_pins.h"
#include "util.h"

///////////////// SAFETY DEFINES //////////////
#define QUADCOPTER_MIN_BATTERY_VOLTAGE 9
//////////////////////////////////////////////

///////////////// PID AND OTHERS DEFINES ///////////////
//>>> PID
/* PID General Equation 
 *
 * u(n) = kp  *e(n) + ki  ∑ e(n)T + kd *( e(n)-e(n-1)/T)
 * kp   - proportional gain
 * ki   - integral gain
 * kd   - derivative gain
 * e(n) - setpoint - current value
 * T    - sampling time = 0.004 seconds
 */
//<<< PID EOF

//>>> ALTITUDE
#define QUADCOPTER_MAX_ALTITUDE_ALLOWED 1000 // cm
#define QUADCOPTER_ALTITUDE_SCALE_FACTOR (1250.f/QUADCOPTER_MAX_ALTITUDE_ALLOWED)
#define PID_ALTITUDE_MAX_INTEGRAL 25
#define PID_ALTITUDE_KP 1
#define PID_ALTITUDE_KI 0.01f
#define PID_ALTITUDE_KD 0.001f
//<<< ALTITUDE EOF

//>>> ROLL
#define QUADCOPTER_MAX_ROLL_ALLOWED 25  // degrees
#define QUADCOPTER_ROLL_SCALE_FACTOR (625.f/QUADCOPTER_MAX_ROLL_ALLOWED)
#define PID_ROLL_MAX_INTEGRAL 25
#define PID_ROLL_KP 3
#define PID_ROLL_KI 0.01f
#define PID_ROLL_KD 0.001f
//<< ROLL EOF

//>>> PITCH
#define QUADCOPTER_MAX_PITCH_ALLOWED 25  // degrees
#define QUADCOPTER_PITCH_SCALE_FACTOR (625.f/QUADCOPTER_MAX_PITCH_ALLOWED)
#define PID_PITCH_MAX_INTEGRAL 25
#define PID_PITCH_KP 3
#define PID_PITCH_KI 0.01f
#define PID_PITCH_KD 0.001f
//<< PITCH EOF

//>>> YAW
#define QUADCOPTER_MAX_YAW_ALLOWED 60  // degrees
#define QUADCOPTER_YAW_SCALE_FACTOR (625.f/QUADCOPTER_MAX_YAW_ALLOWED)
#define PID_YAW_MAX_INTEGRAL 25
#define PID_YAW_KP 0.5f
#define PID_YAW_KI 0.0001f
#define PID_YAW_KD 0.000001f
//<< YAW EOF
////////////////////////////////////////////////////////

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
float quad_pitch, quad_roll, quad_yaw;
bool yawFirstTime = true;
//////////////////////////////////////

////////////////HMC5883L///////////////
HMC5883L mag = HMC5883L(0);
// for magnetic measurements 
float magnetic_x, magnetic_y, magnetic_z, heading;
// for tilt correction
float Xh, Yh;
//////////////////////////////////////

////////////////MS5611///////////////
MS5611 baro = MS5611();
// for altitude measurements 
float altitude, temperature, baro_correction_coeff;
//////////////////////////////////////

////////////////GPS///////////////
struct m8_gps gps_coords;
//////////////////////////////////

////////////////SIM800L///////////////
sim800l sim;
//////////////////////////////////

////////////////LOOP///////////////
unsigned long last_loop = 0;
uint32_t count = 0;
uint8_t retval = 0;
char uart0_tx_buffer[100];
char* float_conv_ptr;
char* int_conv_ptr;
uint8_t isNewInc = 0;
unsigned long tic;
unsigned long toc;
bool flag = false;
//////////////////////////////////////

//////////CALIBRATION//////////////
void sw2_isr();
void sw1_isr();
// for magnetometer
bool isMagCal = false;
// for MPU-6050
bool isMpuCal = false;
//////////////////////////////////////

//////////REMOTE////////////
int32_t motor1_thrust = 0;
int32_t motor2_thrust = 0;
int32_t motor3_thrust = 0;
int32_t motor4_thrust = 0;
float thrust_cmd, yaw_cmd, pitch_cmd, roll_cmd, initial_yaw;
float thrust_u, yaw_u, pitch_u, roll_u;
uint16_t ch[4];
////////////////////////////

////////////PID////////////
float thrust_last_error = 0, thrust_error = 0;
float yaw_last_error = 0, yaw_error = 0;
float pitch_last_error = 0, pitch_error = 0;
float roll_last_error = 0, roll_error = 0;
float yaw_integral, roll_integral;
float thrust_integral, pitch_integral;
///////////////////////////

void setup() {
    // start initing serial port
    Serial.begin(115200);
    pinMode(PA_4,OUTPUT); // for debugging 
    
    /* --- Init LED's and Analogs --- */
    quad_init();

    /* --- Init ESC Motors --- */
    quad_esc_motors_init();

    /* --- Init rotines to trigger a newer calibration --- */
    pinMode(PF_4,INPUT_PULLUP);
    pinMode(PF_0,INPUT_PULLUP);
    attachInterrupt(PF_4,sw1_isr, FALLING);
    attachInterrupt(PF_0,sw2_isr, FALLING);

    // let voltage stable
    delay(3000);

    // print system information
    quad_redOn();
    Serial.println("System Clock Frequency : " + String(SysCtlClockGet()/1000000) + " Mhz");
    Serial.println("System Battery : " + String(quad_readBatteryVoltage()) + " Volt");
    if(quad_readBatteryVoltage() < QUADCOPTER_MIN_BATTERY_VOLTAGE){
        Serial.println("Not enough power to start ...");
        while(1); // TODO: BLINK
    }

    /* --- Init i2c pins --- */
    Wire = TwoWire(1);
    Wire.begin(); 
    delay(200);

    /* --- Init EEPROM --- */
    Serial.println("Initing EEPROM...");
    if(quad_init_eeprom() == QUAD_OK){
        Serial.println("EEPROM OK!");
        // set magnetometer eeprom callbacks
        mag.setEEPROMWriteFunction(quad_write_eeprom);
        mag.setEEPROMReadFunction(quad_read_eeprom);
        // set mpu6050 eeprom callbacks
        accelgyro.setEEPROMWriteFunction(quad_write_eeprom);
        accelgyro.setEEPROMReadFunction(quad_read_eeprom);
    } else {
        Serial.println("EEPROM NOT OK!");
        while(1); // TODO: BLINK
    }
    // EEPROM Size (bytes) : 2048 EEPROM Bytes Pear Block : 64
    Serial.println("EEPROM Size (bytes) : " + String(quad_eeprom_get_size()) + " EEPROM Bytes Pear Block : " 
                                + String(quad_eeprom_get_bytes_pear_block()));

    /* --- Init HC-05 --- */
    Serial.println("Initing HC-05...");
    if(hc_05_init() == HC_05_OK){
        Serial.println("HC-05 INIT OK ! BAUDRATE = " + String(HC_05_BAUDRATE) + 
        " HC-05 NAME = " + String(HC_05_DEVICE_NAME) + " HC-05 PASS " + String(HC_05_DEVICE_PASS));
        // set state interrupt callback
        HC_05_STATE_INT(hc_05_status_isr);
        // set hc-05 rx interrupt callback
        HC_05_RX_INT(hc_05_rx_isr);
    } else {
        Serial.println("HC-05 INIT FAILED !");
        while(1); // TODO: BLINK
    }
    delay(200);

    /* --- Init HC-12 --- */
    Serial.println("Initing HC-12...");
    if(hc_12_init() == HC_12_OK){
        Serial.println("HC-12 INIT OK ! BAUDRATE = " + String(HC_12_BAUDRATE));
        Serial.println("Channel: " + String(433.4F + hc_12_getRadioChannel()*0.5F ) + "Mhz");
        Serial.print("Device Mode: ");
        switch (hc_12_getDeviceMode()){
        case HC_12_MODERATE_POWER_SAVING_MODE: Serial.println("\"MODERATE POWER SAVING MODE\""); break;
        case HC_12_EXTREME_POWER_SAVING_MODE: Serial.println("\"EXTREME POWER SAVING MODE\""); break;
        case HC_12_GENERAL_PURPOSE_MODE: Serial.println("\"GENERAL PURPOSE MODE\""); break;
        case HC_12_LONG_RANGE_MODE: Serial.println("\"LONG RANGE MODE\""); break;                                
        default: Serial.println("Invalid Mode!"); break; }
        Serial.println("TX Power: " + String(0.8F*pow(2,hc_12_getTXpower()-1)) + "mW");
    } else {
        Serial.println("HC-12 INIT FAILED !");
        while(1); // TODO: BLINK
    }
    delay(200);

    /* --- Init HC-SR04 --- */
    Serial.println("Initing HC-SR04...");
    if(hc_sr04_init(HC_SR04_EXPECTED_HEIGHT) == HC_SR04_0K){
        Serial.println("HC-SR04 INIT OK");
    } else Serial.println("HC-SR04 INIT FAILED");
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
    } else {
        Serial.println("M8_GPS FAILED!");
        while(1); // TODO: BLINK
    }
    delay(200);

    /* --- Init SIM800L --- */
    Serial.println("Initing SIM800L...");
    if(sim.begin(SIM800L_BAUDRATE) == SIM800L_OK){
        Serial.println("SIM800L INIT OK ! BAUDRATE = " + String(SIM800L_BAUDRATE));
        SIM800L_RX_INT(sim800l_rx_isr);
    }else {
        Serial.println("SIM800L INIT FAILED!");
        while(1); // TODO: BLINK
    }
    delay(200);

    /* --- Init ESP-01 --- */
    Serial.println("Initing ESP_01...");
    if(esp_01_init() == ESP_01_OK){
        Serial.println("ESP_01 INIT OK ! BAUDRATE = " + String(ESP_01_BAUDRATE));
        /// open tcp connection
        esp_01_tcp_connect((char*)"192.168.100.1",(char*)"9090");
        /// set interrupt callback
        ESP_01_RX_INT(esp_01_rx_isr);
    } else {
        Serial.println("ESP_01 INIT FAILED!");
    }
    delay(200);

    /* --- Init HMC5883 --- */
    Serial.println("Initing HMC5883...");
    //init sensor
    if(!mag.begin()) {
        Serial.println("HMC5883 INIT FAILED!");
        while(1); // TODO: BLINK
    } else {
        if(!mag.isCalibrated()) mag.calibrate(30); // calibrate for 30 seconds
        Serial.println("HMC5883 INIT OK!");
    }
    delay(200);

    /* --- MS5611 --- */
    Serial.println("Initing MS5611...");
    if(baro.init(MS5611_ADDR_CSB_LOW) == MS5611_OK) {
        Serial.println("HMC5883 INIT OK!");
    } else {
        Serial.println("MS5611 INIT FAILED!");
        while(1); // TODO: BLINK
    }
    delay(200);

    /* --- Init MPU6050 --- */
    Serial.println("Initing MPU6050...");
    accelgyro.initialize();
    if(accelgyro.testConnection()){
        // config MPU6050 resolution
        accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
        accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
        delay(200);
        if(!accelgyro.isCalibrated()) accelgyro.calibrate(); 
        Serial.println("MPU6050 INIT OK!");
    } else {
        Serial.println("MPU6050 INIT FAILED!");
        while(1); // TODO: BLINK
    }
    delay(200);

    // enables interrupts
    IntMasterEnable();

    // apply correction to altimeter
    float sr04_height, sr04_average_height = 0;
    float baro_average_altitude = 0;
    int readings_counter = 0;
    for (;;) {
        // start sr04 reading
        hc_sr04_trigger();
        // get altitude using the altimeter
        baro.getTemperature();
        baro_average_altitude = baro_average_altitude*0.1 + baro.getAltitude()*0.9;
        // wait sr04 result
        while(hc_sr04_read(&sr04_height) == HC_SR04_WAITING_MEASUREMENT);
        // valid reading ? 
        if ( sr04_height != -1 ) {
            sr04_average_height = sr04_average_height*0.45 + sr04_height*0.55;
        }
        // more than 10 seconds ? 
        if( (readings_counter++ >= 1000) && 
            (sr04_average_height >= HC_SR04_EXPECTED_HEIGHT*0.8) &&  
            (sr04_average_height <= HC_SR04_EXPECTED_HEIGHT*1.2 )
        ){
            break;
        }
        delay(10);
    }
    // get the correction coeff
    baro_correction_coeff = baro_average_altitude - (sr04_average_height/100);
    Serial.print("SR04 Average Height: ");   Serial.println(sr04_average_height);
    Serial.print("Baro Average Altitude: "); Serial.println(baro_average_altitude);
    Serial.print("Baro correction coeff: "); Serial.println(baro_correction_coeff);

    // ok :) good to go!
    quad_blueOn();
}

void loop() {
    // elapsed time = 966us - should repeat at every 4 ms
    if((micros() - last_loop) >= MPU6050_READ_PERI){
        // update last_loop time value
        last_loop = micros();

        if(flag) GPIOPinWrite(0x40004000, 0x10, 0x10);
        else GPIOPinWrite(0x40004000, 0x10, 0x00);
        flag = !flag;

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
        yaw += -gyro_z;
        // for tranfering pitch to roll
        pitch += roll * sinf(gyro_z * DEG_TO_RAD);  // pi/180 = 0.01745
        roll -= pitch * sinf(gyro_z * DEG_TO_RAD);     
        // removing drift
        pitch = pitch * 0.9996 + psi * 0.0004;     
        roll = roll * 0.9996 + theta * -0.0004;
        // saturate yaw if needed
        if(yaw > 360) yaw -= 360;
        if(yaw < 0)   yaw += 360; 
        ////////////////////////////////////////////////////////////////

        //////////// TRANSFER MPU6050 COORDS TO QUAD COORDS //////////////
        // mpu6050 can be mounted at different locations on the quadcopter
        // the goal here, is create a calibration program that will assign
        // the mpu6050 coords to the quad coords. Quad coords are based
        // on the GPS Module arrow
        quad_pitch = -roll;
        quad_roll  = pitch;
        //////////////////////////////////////////////////////////////////

        ///////////HMC5883L-READING//////////////////////
        mag.getMotion(&magnetic_x,&magnetic_y,&magnetic_z);
        ////////////////////////////////////////////////

        ///////////CALCULATIONS/////////////////
        /* tilt corrections */
        Xh = magnetic_x*cosf(-quad_pitch*DEG_TO_RAD) + magnetic_y*sinf(quad_roll*DEG_TO_RAD)*sinf(-quad_pitch*DEG_TO_RAD) 
                    - magnetic_z*cosf(quad_roll*DEG_TO_RAD)*sinf(-quad_pitch*DEG_TO_RAD);
        Yh = magnetic_y*cosf(quad_roll*DEG_TO_RAD) + magnetic_z*sinf(quad_roll*DEG_TO_RAD);
        //Now that the horizontal values are known the heading can be calculated. With the following lines of code the heading is calculated in degrees.
        //Please note that the atan2 uses radians in stead of degrees. That is why the 180/3.14 is used.
        if (Yh < 0) heading = 360 + atan2f(Yh, Xh)*RAD_TO_DEG;
        else heading = atan2f(Yh, Xh)*RAD_TO_DEG;  
        ////////////////////////////////////////

        ///////////CORRECTIONS////////////////////
        heading += -1.7667F; // declination correction
        // Correct for when signs are reversed.
        if(heading < 0)   heading += 360;
        // Check for wrap due to addition of declination.
        if(heading > 360) heading -= 360;
        /////////////////////////////////////////

        ////////////////YAW CORRECTIONS//////////////////
        if(yawFirstTime){
            yawFirstTime = false; // not first time anymore
            yaw = heading; // assign heading to yaw
            initial_yaw = yaw - 180;
        }
        // removing yaw drift
        yaw = yaw * 0.9996 + heading * 0.0004; 
        // transfering mpu6050 coords to quad coords
        quad_yaw = yaw;
        /////////////////////////////////////////////

        ///////////  READ ALTITUDE (126us) //////////////////
        temperature = baro.getTemperature();
        altitude    = (baro.getAltitude() - baro_correction_coeff) * 100; // in cm
        if(altitude < 0) altitude = 0;
        /////////////////////////////////////////////

        //////////// READ REMOTE //////////////////
        if(hc_05_readChannels(ch) == HC_05_NOT_OK){
            // TODO: READ HC-12
            ch[0] = 625;
            ch[1] = 0;
            ch[2] = 625;
            ch[3] = 625;
        }
        ///////////////////////////////////////////

        /// CONVERT REMOTE TO DEG's AND ALTITUDE //
        yaw_cmd    = yaw_cmd    * 0.6 + ((ch[0]-625)/QUADCOPTER_YAW_SCALE_FACTOR)   * 0.4; // -25 ... 0 ... 25 degrees
        thrust_cmd = thrust_cmd * 0.6 + (ch[1]/QUADCOPTER_ALTITUDE_SCALE_FACTOR)    * 0.4; //   0 ... 5 ... 10 meters
        pitch_cmd  = pitch_cmd  * 0.6 + ((625-ch[3])/QUADCOPTER_PITCH_SCALE_FACTOR) * 0.4; // -25 ... 0 ... 25 degrees
        roll_cmd   = roll_cmd   * 0.6 + ((ch[2]-625)/QUADCOPTER_ROLL_SCALE_FACTOR)  * 0.4; // -25 ... 0 ... 25 degrees
        ///////////////////////////////////////////

        /////////// PID CALCULATIONS ///////////////
        // calculate errors
        thrust_error = (thrust_cmd - altitude);
        pitch_error  = (pitch_cmd  - quad_pitch);
        roll_error   = (roll_cmd   - quad_roll);
        yaw_error    = ((initial_yaw - yaw_cmd) - (quad_yaw-180));

        // calculate and saturate integral
        thrust_integral += thrust_error;
        if(thrust_integral > PID_ALTITUDE_MAX_INTEGRAL) thrust_integral = PID_ALTITUDE_MAX_INTEGRAL;
        if(thrust_integral < - PID_ALTITUDE_MAX_INTEGRAL) thrust_integral = -PID_ALTITUDE_MAX_INTEGRAL;

        pitch_integral += pitch_error;
        if(pitch_integral > PID_PITCH_MAX_INTEGRAL) pitch_integral = PID_PITCH_MAX_INTEGRAL;
        if(pitch_integral < - PID_PITCH_MAX_INTEGRAL) pitch_integral = -PID_PITCH_MAX_INTEGRAL;

        roll_integral += roll_error;
        if(roll_integral > PID_ROLL_MAX_INTEGRAL) roll_integral = PID_ROLL_MAX_INTEGRAL;
        if(roll_integral < - PID_ROLL_MAX_INTEGRAL) roll_integral = -PID_ROLL_MAX_INTEGRAL;

        yaw_integral += yaw_error;
        if(yaw_integral > PID_YAW_MAX_INTEGRAL) yaw_integral = PID_YAW_MAX_INTEGRAL;
        if(yaw_integral < - PID_YAW_MAX_INTEGRAL) yaw_integral = -PID_YAW_MAX_INTEGRAL;

        // calculate control signal
        thrust_u = PID_ALTITUDE_KP * thrust_error + PID_ALTITUDE_KI * thrust_integral + PID_ALTITUDE_KD * (thrust_error - thrust_last_error);
        pitch_u  = PID_PITCH_KP    * pitch_error  + PID_PITCH_KI    * pitch_integral  + PID_PITCH_KD    * (pitch_error  - pitch_last_error);
        roll_u   = PID_ROLL_KP     * roll_error   + PID_ROLL_KI     * roll_integral   + PID_ROLL_KD     * (roll_error   - roll_last_error);
        yaw_u    = PID_YAW_KP      * yaw_error    + PID_YAW_KI      * yaw_integral    + PID_YAW_KD      * (yaw_error    - yaw_last_error);
        
        // update last errors
        thrust_last_error = thrust_error;
        pitch_last_error  = pitch_error;
        roll_last_error   = roll_error;
        yaw_last_error    = yaw_error;
        ///////////////////////////////////////////

        /////////// CALCULATE MOTOR THRUST ////////
        motor1_thrust = thrust_u - yaw_u - pitch_u - roll_u;
        motor2_thrust = thrust_u + yaw_u - pitch_u + roll_u;
        motor3_thrust = thrust_u + yaw_u + pitch_u - roll_u;
        motor4_thrust = thrust_u - yaw_u + pitch_u + roll_u;
        ///////////////////////////////////////////

        //////////// SET THRUST //////////////////
        motor1_thrust > 0 ? quad_esc_set_thrust(MOTOR1, motor1_thrust) : quad_esc_set_thrust(MOTOR1, 0);
        motor2_thrust > 0 ? quad_esc_set_thrust(MOTOR2, motor2_thrust) : quad_esc_set_thrust(MOTOR2, 0);
        motor3_thrust > 0 ? quad_esc_set_thrust(MOTOR3, motor3_thrust) : quad_esc_set_thrust(MOTOR3, 0);
        motor4_thrust > 0 ? quad_esc_set_thrust(MOTOR4, motor4_thrust) : quad_esc_set_thrust(MOTOR4, 0);
        ///////////////////////////////////////////

        // if isNewInc equals to zero, change back to one and increment 
        if(isNewInc == 0){
            isNewInc = 1;
            count ++;
        }
    }
    
    // have spare time ? play a little bit with it  - max reported - 1627us but play safe
    else if((micros() - last_loop <= MPU6050_READ_PERI-2000) && isNewInc){
        // toggle isNewInc - is new increment ? 
        isNewInc = 0;

        // at 1 and 1 second - elapsed time = 1200 us aprox 1.2ms 
        switch (count){
        case 250:
            // takes 36 us
            float_conv_ptr = (quad_pitch > 0) ? myFTOA(quad_pitch, 2 , 10) : myFTOA(quad_pitch*-1, 2 , 10);
            (quad_pitch > 0) ? strncat(uart0_tx_buffer,"Pitch : ",8) : strncat(uart0_tx_buffer,"Pitch : -",9);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);

            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            break;
        case 265:
            // takes 36 us
            float_conv_ptr = (quad_roll > 0) ? myFTOA(quad_roll, 2 , 10) : myFTOA(quad_roll*-1, 2 , 10);
            (quad_roll > 0) ? strncat(uart0_tx_buffer," Roll : ",8) : strncat(uart0_tx_buffer," Roll : -",9);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);

            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            break;
        case 280:
            // takes 36 us
            float_conv_ptr = (quad_yaw > 0) ? myFTOA(quad_yaw, 2 , 10) : myFTOA(quad_yaw*-1, 2 , 10);
            (quad_yaw > 0) ? strncat(uart0_tx_buffer," Yaw : ",7) : strncat(uart0_tx_buffer," Yaw : -",8);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            esp_01_tcp_send((char*)"\n");

            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.println(uart0_tx_buffer);
            break;
        case 295:          
            // takes 36 us
            float_conv_ptr = (heading > 0) ? myFTOA(heading, 2 , 10) : myFTOA(heading*-1, 2 , 10);
            (heading > 0) ? strncat(uart0_tx_buffer,"Heading : ",10) : strncat(uart0_tx_buffer,"Heading : -",11);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            esp_01_tcp_send((char*)"\n");

            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.println(uart0_tx_buffer);
            break;
        
        case 310:
            // takes 36 us
            float_conv_ptr = (temperature > 0) ? myFTOA(temperature, 2 , 10) : myFTOA(temperature*-1, 2 , 10);
            (temperature > 0) ? strncat(uart0_tx_buffer,"Temp : ",7) : strncat(uart0_tx_buffer,"Temp : -",8);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            break;
        
        case 325:
            // takes 36 us
            float_conv_ptr = (altitude > 0) ? myFTOA(altitude, 2 , 10) : myFTOA(altitude*-1, 2 , 10);
            (altitude > 0) ? strncat(uart0_tx_buffer," Alt : ",7) : strncat(uart0_tx_buffer," Alt : -",8);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            esp_01_tcp_send((char*)"\n");
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.println(uart0_tx_buffer);

            break;

        case 340:
            // takes 880us
            if(m8_gps_pending_read()){
                retval = m8_gps_getCoords(&gps_coords);
                if(retval == M8_GPS_OK){
                    // latitude
                    int_conv_ptr = myITOA(gps_coords.lat.degrees,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"?",1);
                    int_conv_ptr = myITOA(gps_coords.lat.minutes,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"'",1);
                    int_conv_ptr = myITOA(gps_coords.lat.seconds,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"''",2);
                    strncat(uart0_tx_buffer,&gps_coords.lat.direction,1);
                    strncat(uart0_tx_buffer,"\n",1);

                    // longitude
                    int_conv_ptr = myITOA(gps_coords.lon.degrees,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"?",1);
                    int_conv_ptr = myITOA(gps_coords.lon.minutes,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"'",1);
                    int_conv_ptr = myITOA(gps_coords.lon.seconds,10,0);
                    strncat(uart0_tx_buffer,int_conv_ptr,strlen(int_conv_ptr));
                    strncat(uart0_tx_buffer,"''",2);
                    strncat(uart0_tx_buffer,&gps_coords.lon.direction,1);
                    strncat(uart0_tx_buffer,"\n",1);

                    // try to send
                    retval = esp_01_tcp_send(uart0_tx_buffer);
                    if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
                }
            }
            break;

        case 355:
            // takes 36 us
            float_conv_ptr = (thrust_cmd > 0) ? myFTOA(thrust_cmd, 2 , 10) : myFTOA(thrust_cmd*-1, 2 , 10);
            (thrust_cmd > 0) ? strncat(uart0_tx_buffer,"Thrust_cmd : ",13) : strncat(uart0_tx_buffer,"Thrust_cmd : -",14);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            break;
        
        case 370:
            // takes 36 us
            float_conv_ptr = (pitch_cmd > 0) ? myFTOA(pitch_cmd, 2 , 10) : myFTOA(pitch_cmd*-1, 2 , 10);
            (pitch_cmd > 0) ? strncat(uart0_tx_buffer," Pitch_cmd : ",13) : strncat(uart0_tx_buffer," Pitch_cmd : -",14);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            break;
        
        case 385:
            // takes 36 us
            float_conv_ptr = (roll_cmd > 0) ? myFTOA(roll_cmd, 2 , 10) : myFTOA(roll_cmd*-1, 2 , 10);
            (roll_cmd > 0) ? strncat(uart0_tx_buffer," Roll_cmd : ",12) : strncat(uart0_tx_buffer," Roll_cmd : -",13);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);

            break;
        
        case 400:
            // takes 36 us
            float_conv_ptr = (yaw_cmd > 0) ? myFTOA(yaw_cmd, 2 , 10) : myFTOA(yaw_cmd*-1, 2 , 10);
            (yaw_cmd > 0) ? strncat(uart0_tx_buffer," Yaw_cmd : ",11) : strncat(uart0_tx_buffer," yaw_cmd : -",12);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            esp_01_tcp_send((char*)"\n");
            
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.println(uart0_tx_buffer);
            break;
        
        case 415:
            // takes 36 us
            float_conv_ptr = (thrust_u > 0) ? myFTOA(thrust_u, 2 , 10) : myFTOA(thrust_u*-1, 2 , 10);
            (thrust_u > 0) ? strncat(uart0_tx_buffer,"thrust_u : ",11) : strncat(uart0_tx_buffer,"thrust_u : -",12);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            uart0_tx_buffer[0] = '\0';
            // takes 36 us
            float_conv_ptr = (pitch_u > 0) ? myFTOA(pitch_u, 2 , 10) : myFTOA(pitch_u*-1, 2 , 10);
            (pitch_u > 0) ? strncat(uart0_tx_buffer," pitch_u : ",11) : strncat(uart0_tx_buffer," pitch_u : -",12);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            uart0_tx_buffer[0] = '\0';
            // takes 36 us
            float_conv_ptr = (roll_u > 0) ? myFTOA(roll_u, 2 , 10) : myFTOA(roll_u*-1, 2 , 10);
            (roll_u > 0) ? strncat(uart0_tx_buffer," roll_u : ",10) : strncat(uart0_tx_buffer," roll_u : -",11);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.print(uart0_tx_buffer);
            uart0_tx_buffer[0] = '\0';
            // takes 36 us
            float_conv_ptr = (yaw_u > 0) ? myFTOA(yaw_u, 2 , 10) : myFTOA(yaw_u*-1, 2 , 10);
            (yaw_u > 0) ? strncat(uart0_tx_buffer," yaw_u : ",9) : strncat(uart0_tx_buffer," yaw_u : -",10);
            strncat(uart0_tx_buffer,float_conv_ptr,strlen(float_conv_ptr));
            retval = esp_01_tcp_send(uart0_tx_buffer);
            esp_01_tcp_send((char*)"\n");
            // takes 55 us
            if(retval == ESP_01_NOT_OK) Serial.println(uart0_tx_buffer);
            
            count = 0; // reset count
            break;
        
        default:
            break;
        }
        // clean uart0_tx_buffer
        memset(uart0_tx_buffer,'\0',strlen(uart0_tx_buffer));
    }
    
    // no time to print, but still needs to check if it is to start a newer calibration procedure
    else if( isMagCal ){
        mag.calibrate(30);
        isMagCal = false; // set to false
    }

    // no time to print, but still needs to check if it is to start a newer calibration procedure
    else if( isMpuCal ){
        accelgyro.calibrate();
        isMpuCal = false; // set to false
    }
}

void sw1_isr(){
    if(!isMagCal) isMagCal = true;
}

void sw2_isr(){
    if(!isMpuCal) isMpuCal = true;
}