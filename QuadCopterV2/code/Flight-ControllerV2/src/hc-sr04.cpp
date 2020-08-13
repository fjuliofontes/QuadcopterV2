#include "hc-sr04.h"

volatile unsigned long _hc_sr04_pulseStart, _hc_sr04_pulseStop, _hc_sr04_triggerStart;
volatile float _hc_sr04_distance = 0;
volatile bool _hc_sr04_readDone = false, _hc_sr04_trigger = false;

uint8_t hc_sr04_init(uint16_t expected_height){
    // set gpios for hc_sr04
    pinMode(HC_SR04_TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
    pinMode(HC_SR04_ECHO_PIN, INPUT); // Sets the echoPin as an Input
    attachInterrupt(HC_SR04_ECHO_PIN,hc_sr04_isr, RISING);
    delayMicroseconds(10); // give micro time to set the configs

    // check if sensor is steady 
    uint16_t i, j = 0;
    float res, total = 0;
    for(i = 0; i < 20; i++){
        hc_sr04_trigger();
        while(hc_sr04_read(&res) == HC_SR04_WAITING_MEASUREMENT);
        if(res != -1){
            total += res;
            j++;
        }
        delay(20);
    }
    total /= j;
    if((j >= 15) && (expected_height >= total*0.8) && (expected_height <= total*1.2)) return HC_SR04_0K;
    else return HC_SR04_NOT_OK;
}

void hc_sr04_trigger(){
    _hc_sr04_readDone = false;
    _hc_sr04_trigger = true;
    //TODO: remove delay
    digitalWrite(HC_SR04_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(HC_SR04_TRIG_PIN, LOW);
    _hc_sr04_triggerStart = micros();
}

uint8_t hc_sr04_read(float *res){
    // if not triggered yet
    if(!_hc_sr04_trigger) hc_sr04_trigger();
    
    // if readDone = false and time elapsed since triggerStart is within the expected time for the measurment range wait 
    if((!_hc_sr04_readDone) && 
        ((micros()-_hc_sr04_triggerStart) <= (HC_SR04_MAX_ECHO_TIME+10000))) return HC_SR04_WAITING_MEASUREMENT;
    
    // otherwise, range is greater then 4 meters , ignore measurement 
    if((micros()-_hc_sr04_pulseStart) > (HC_SR04_MAX_ECHO_TIME+10000)){
        GPIOIntTypeSet(HC_SR04_ISR_BASE, HC_SR04_ISR_PIN, GPIO_RISING_EDGE);
        *res = -1;
    }
    // or read ok and return calibrated distance
    else *res = _hc_sr04_distance;

    // set last trigger to false
    _hc_sr04_trigger = false;
    
    return HC_SR04_READ_OK;
}

void hc_sr04_isr(){
    // if triggered 
    if(_hc_sr04_trigger){
        // and if we have received a low to high transiction 
        if(GPIOPinRead(HC_SR04_ISR_BASE,HC_SR04_ISR_PIN)){
            // start measuring micros
            _hc_sr04_pulseStart = micros();
            // change the isr trigger mode to high to low transiction
            GPIOIntTypeSet(HC_SR04_ISR_BASE, HC_SR04_ISR_PIN, GPIO_FALLING_EDGE);
        }
        // and if we have received a high to low transiction
        else{
            // stop measuring micros
            _hc_sr04_pulseStop = micros();
            // change the isr trigger mode to low to high transiction
            GPIOIntTypeSet(HC_SR04_ISR_BASE, HC_SR04_ISR_PIN, GPIO_RISING_EDGE);
            // estimate distance based on echo time, and do some physics based validations
            if(((_hc_sr04_pulseStop-_hc_sr04_pulseStart) <= HC_SR04_MAX_ECHO_TIME) && 
                    ((_hc_sr04_pulseStop-_hc_sr04_pulseStart) >= HC_SR04_MIN_ECHO_TIME)){
                _hc_sr04_distance = (_hc_sr04_pulseStop-_hc_sr04_pulseStart) * 0.017F;
                
            }else _hc_sr04_distance = -1; // read not ok
            // flag measuring done
            _hc_sr04_readDone = true;
        }    
    }
}