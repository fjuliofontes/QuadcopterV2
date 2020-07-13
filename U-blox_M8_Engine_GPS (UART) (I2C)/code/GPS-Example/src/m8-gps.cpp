
#include "m8-gps.h"
#include "util.h"
#include <math.h>
//#include <string.h>

/*GPS VARIABLES*/
static char gps_ch;
static uint8_t gps_status = 0;
static uint8_t gps_type = 0;
static char gps_data[100];
static uint8_t gps_len = 0;

uint8_t m8_gps_init(uint32_t baudrate){
    // start by finding actual baudrate
    uint32_t curr_baud = m8_gps_findBaudrate();
    
    // assert baudrate found
    if(curr_baud == M8_GPS_NOT_OK) return M8_GPS_NOT_OK;

    // check if already configured 
    if(curr_baud == baudrate) return M8_GPS_OK;

    // configure new baudrate
    m8_gps_setBaudrate(baudrate);

    // change to the new conf UART Baudrate
    M8_GPS_BEGIN(baudrate);

    // clear FIFO
    while(m8_gps_available()) m8_gps_readByte();

    return M8_GPS_OK;
}

uint8_t m8_gps_available(){
    return M8_GPS_AVAILABLE;
}

uint8_t m8_gps_readByte(){
    return M8_GPS_READBYTE;
}

void m8_gps_writeByte(uint8_t ch){
    M8_GPS_WRITEBYTE((char)ch);
}

void m8_gps_writeWord(char *word){
    while(*word) m8_gps_writeByte(*word++);
}

uint8_t m8_gps_getCoords(struct m8_gps *coords){
    /*
     * m8_gps_getCoords(uint8_t *str)
     * str expected format:
     *  ,4037.82658,N,00843.48667,W,141650.00,A,A*67
     * Output format:
     *  lat = 000º00'00'N/S
     *  lon = 000º00'00'E/W
     */

    uint8_t i,j,k;
    char *p = gps_data;
    uint8_t field = 0, start = 0; 
    uint8_t msg[7][20];
    uint8_t len[7];
    uint8_t seconds[10], minutes[10], degrees[10];
    struct coord *ptr_coord; 

    // set variables
    for(i = 0; i < 7; i++) len[i] = 0;
    // split message
    while( *(++p) != '\0'){
        switch (*p){
        case ',':
            field++;
            break;
        
        default:
            msg[field][len[field]++] = *p;
            break;
        }
    }
    // convert to degrees
    for(k = 0; k <= 2; k+=2){
        /// check if length ok 
        if(len[k] == 0) return M8_GPS_NOT_OK;
        /// init vars
        start = 0; j = 0;
        /// get seconds
        for(i = 0; i < len[k]; i++){
            if(start){
                seconds[j++] = msg[k][i];
            }else if(msg[k][i] == '.'){
                start = 1;
            }
        }
        /// get degrees and minutes
        for(i = 0; i < len[k]-j-1; i++){
            if(i < (len[k]-j-3)){
                degrees[i] = msg[k][i];
            }else{
                minutes[i-(len[k]-j-3)] = msg[k][i];
            }
        }
        /// add string terminator
        seconds[j] = '\0';
        degrees[len[k]-j-3] = '\0';
        minutes[2] = '\0';
        /// select either lat or lon
        if(k == 0)
            ptr_coord = &coords->lat;
        else
            ptr_coord = &coords->lon;
        /// save coordinate
        ptr_coord->degrees=myAtoi((char*)degrees);
        ptr_coord->minutes=myAtoi((char*)minutes);
        ptr_coord->seconds=(uint16_t)(60.0*((float)myAtoi((char*)seconds)/pow10(j)));
        ptr_coord->direction=msg[k+1][0];
    }

    // re-activate READING process 
    gps_status = M8_GPS_MODULE_WAITING;

    return M8_GPS_OK;
}

void m8_gps_checksum(uint8_t *CK_A, uint8_t *CK_B, uint8_t *data, uint8_t len){
    // reset vars
    *CK_A = 0;
    *CK_B = 0;
    // create vars
    uint32_t i;
    // calculate checksum
    for(i=0; i<len; i++){
        *CK_A += data[i];
        *CK_B += *CK_A;
    }
    // saturate checksum
    *CK_A &= 0xFF;
    *CK_B &= 0xFF;
}

uint32_t m8_gps_findBaudrate(){
    static uint32_t allowedRates[] = {9600,115200};
    static uint8_t numRates = 2;
    unsigned long curr_time;
    uint8_t i;

    for(i = 0; i < numRates; i++){
        // init serial port
        M8_GPS_BEGIN(allowedRates[i]);
        delay(100);

        // wait for '$' char 
        curr_time = millis();
        do{
            if(m8_gps_available())
                if((char)m8_gps_readByte() == '$')
                    return allowedRates[i];  
        }while((millis()-curr_time) < M8_GPS_TIMEOUT);
    }

    return M8_GPS_NOT_OK;
}

void m8_gps_setBaudrate(uint32_t baudrate){
    // get/set uart cmd
    static uint8_t conf[28] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xC0,0x08,0x00,0x00,
                               0x00,0xC2,0x01,0x00,0x07,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xB0,0x7E};

    // convert to little endian format
    uint32_t little_endian_baudrate = bswap_32(baudrate);

    // update baudrate bytes
    conf[14] = (little_endian_baudrate >> 24) & 0xFF;
    conf[15] = (little_endian_baudrate >> 16) & 0xFF;
    conf[16] = (little_endian_baudrate >> 8)  & 0xFF;
    conf[17] = little_endian_baudrate & 0xFF;

    // calculate and fill checksum
    uint8_t CK_A, CK_B;
    uint8_t *packet = conf;
    //// remove header
    packet += 2;
    //// call checksum function
    m8_gps_checksum(&CK_A, &CK_B, packet, 24);
    //// fill checksum
    conf[26] = CK_A;
    conf[27] = CK_B;

    // finally write configuration to the module
    for(int i=0; i<28; i++) m8_gps_writeByte(conf[i]);

    // delay 200 ms
    delay(200);
}

void m8_gps_setMeasRate(uint16_t measRate, uint8_t navRate){
    // get/set uart cmd
    static uint8_t conf[14] = {0xB5,0x62,0x06,0x08,0x06,0x00,0x32,0x00,0x3C,0x00,0x00,0x00,0x00,0x00};

    // convert to little endian format
    if(measRate < 50) measRate = 50; // saturate for protocol versions less then 24
    if(navRate > 127) navRate = 127; // saturate for protocol versions greater or equal then 18
    uint16_t little_endian_measRate = bswap_16(measRate);
    uint16_t little_endian_navRate = bswap_16(navRate);

    // update bytes
    conf[6] = (little_endian_measRate >> 8) & 0xFF;
    conf[7] = little_endian_measRate & 0xFF;
    conf[8] = (little_endian_navRate >> 8) & 0xFF;
    conf[9] = little_endian_navRate & 0xFF;

    // calculate and fill checksum
    uint8_t CK_A, CK_B;
    uint8_t *packet = conf;
    //// remove header
    packet += 2;
    //// call checksum function
    m8_gps_checksum(&CK_A, &CK_B, packet, 10);
    //// fill checksum
    conf[12] = CK_A;
    conf[13] = CK_B;

    // finally write configuration to the module
    for(int i=0; i<14; i++) m8_gps_writeByte(conf[i]);

    // delay 200 ms
    delay(200);
}

void m8_gps_setMsgRate(uint16_t MSG_ID, uint8_t rate){
    // get/set uart cmd
    static uint8_t conf[11] = {0xB5,0x62,0x06,0x01,0x03,0x00,0xF0,0x03,0x00,0x00,0x00};

    // update bytes
    conf[6] = (MSG_ID >> 8) & 0xFF;
    conf[7] = MSG_ID & 0xFF;
    conf[8] = rate;

    // calculate and fill checksum
    uint8_t CK_A, CK_B;
    uint8_t *packet = conf;
    //// remove header
    packet += 2;
    //// call checksum function
    m8_gps_checksum(&CK_A, &CK_B, packet, 7);
    //// fill checksum
    conf[9] = CK_A;
    conf[10] = CK_B;

    // finally write configuration to the module
    for(int i=0; i<11; i++) m8_gps_writeByte(conf[i]);

    // delay 200 ms
    delay(200);
}

uint32_t bswap_32 (uint32_t num){
    uint32_t swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
                       ((num<<8)&0xff0000) | // move byte 1 to byte 2
                       ((num>>8)&0xff00) | // move byte 2 to byte 1
                       ((num<<24)&0xff000000); // byte 0 to byte 3
    return swapped;
}

uint16_t bswap_16 (uint16_t num){
    uint16_t swapped = (num>>8) | (num<<8);
    return swapped;
}

uint8_t m8_gps_pending_read(){
    return (gps_status&M8_GPS_MODULE_LF) == M8_GPS_MODULE_LF;
}

void m8_gps_rx_isr(){
    /* 
     * m8_gps_rx_isr() - Interrupt triggered after every single char received
     * Goal: Obtain the latitude and longitude from the GPS module
     * Device Specs: 
     *  Protocol: UART
     *  Baudrate: 9600 bps
     *  Read Periodicity: 1 second
     *  Message Structure: $xxxxx, , , , , <CR><LF>
     *  Target Message: $xxGLL,lat,NS,lon,EW,time,status,posMode*cs<CR><LF>
     *  ASCII CODES:
     *       $  - 0x24
     *       G  - 0x47
     *       L  - 0x4C
     *     <CR> - 0xD
     *     <LF> - 0xA 
     */ 

    // read all available char's
    while(M8_GPS_AVAILABLE){
        // get one byte
        gps_ch = M8_GPS_READBYTE;
        
        // ch == $
        switch (gps_ch){

        case 0x24:
            /* $ */
            if(gps_status == M8_GPS_MODULE_WAITING){
                gps_status |= M8_GPS_MODULE_START | M8_GPS_MODULE_IGNORING; // default state
                gps_type = 0x00;
            }
            break;
        case 0x47:
            /* G */
            if((gps_status&M8_GPS_MODULE_IGNORING) == M8_GPS_MODULE_IGNORING){
                if(gps_type == 0x00){
                    gps_type = 0x47; // G
                }
            }else if((gps_status&M8_GPS_MODULE_READING) == M8_GPS_MODULE_READING){
                // save
                gps_data[gps_len++] = gps_ch;
            }
            break;
        case 0x4C:
            /* L */
            if((gps_status&M8_GPS_MODULE_IGNORING) == M8_GPS_MODULE_IGNORING){
                if(gps_type == 0x47){ // G
                    gps_type = 0x4C; // L
                }else if(gps_type == 0x4C){ // L
                    gps_type = 0x00; // ok :)
                    gps_len  = 0; // start reading
                    gps_status &= ~M8_GPS_MODULE_IGNORING; // remove ignoring flag
                    gps_status |= M8_GPS_MODULE_READING;   // add reading flag
                }
            }else if((gps_status&M8_GPS_MODULE_READING) == M8_GPS_MODULE_READING){
                // save
                gps_data[gps_len++] = gps_ch;
            }
            break;
        case 0xD:
            /* <CR> */
            if(((gps_status&M8_GPS_MODULE_READING) == M8_GPS_MODULE_READING)
                    || ((gps_status&M8_GPS_MODULE_IGNORING) == M8_GPS_MODULE_IGNORING))
                gps_status |= M8_GPS_MODULE_CR;
            break;
        case 0xA:
            /* <LF> */
            if((gps_status&M8_GPS_MODULE_CR) == M8_GPS_MODULE_CR){
                if((gps_status&M8_GPS_MODULE_READING) == M8_GPS_MODULE_READING){
                    gps_data[gps_len++] = '\0';
                    gps_status |= M8_GPS_MODULE_LF;
                }
                else{
                    gps_status &= M8_GPS_MODULE_WAITING;
                }
            }
            break;
        
        default:
            if((gps_status&M8_GPS_MODULE_READING) == M8_GPS_MODULE_READING){
                // save
                gps_data[gps_len++] = gps_ch;
            }else{   
                // discard
                gps_type = 0x00;
            }
            break;
        }

        //Serial.write(M8_GPS_READBYTE);
    
    }
    // clean interrup flag
    M8_GPS_CLEAN_RX_INT;
}