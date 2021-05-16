
#include "sim800l.h"

sim800l::sim800l(void){

}

uint8_t sim800l::_available(){
    return SIM800L_AVAILABLE;
}

uint8_t sim800l::_readByte(){
    return SIM800L_READBYTE;
}

void sim800l::_writeByte(char ch){
    SIM800L_WRITEBYTE(ch);
}

void sim800l::_writeWord(char *word){
    while(*word) _writeByte(*word++);
}

void sim800l::writeWord(char *word){
    _writeWord(word);
}

void sim800l::writeByte(char ch){
    _writeByte(ch);
}

uint8_t sim800l::begin(){
    // set rst pin as output
    pinMode(SIM800L_RST_PIN, OUTPUT);

    // config baudrate
    _sim800l_baud = SIM800L_BAUDRATE;   // Default baud rate 9600
    // configure UART Baudrate
    SIM800L_BEGIN(_sim800l_baud);
    
    // reset module and wait AT response
    if(reset() == SIM800L_NOT_OK) return SIM800L_NOT_OK;

    // disable echo
    if(_echo(0) == SIM800L_NOT_OK) return SIM800L_NOT_OK;

    _sim800l_sleepMode = 0;
    _sim800l_functionalityMode = 1;

    //if (LED_FLAG) pinMode(LED_PIN, OUTPUT);

    _sim800l_buffer.reserve(SIM800L_BUFFER_RESERVE_MEMORY); // Reserve memory to prevent intern fragmention

    return SIM800L_OK;
}

uint8_t sim800l::begin(uint32_t baud){
    // set rst pin as output
    pinMode(SIM800L_RST_PIN, OUTPUT);

    // config baudrate
    _sim800l_baud = baud;   // Default baud rate 9600
    // configure UART Baudrate
    SIM800L_BEGIN(_sim800l_baud);
    
    // reset module and wait AT response
    if(reset() == SIM800L_NOT_OK) return SIM800L_NOT_OK;
    
    // disable echo
    if(_echo(0) == SIM800L_NOT_OK) return SIM800L_NOT_OK;

    _sim800l_sleepMode = 0;
    _sim800l_functionalityMode = 1;

    //if (LED_FLAG) pinMode(LED_PIN, OUTPUT);

    _sim800l_buffer.reserve(SIM800L_BUFFER_RESERVE_MEMORY); // Reserve memory to prevent intern fragmention

    return SIM800L_OK;
}


/*
 * AT+CSCLK=0	Disable slow clock, module will not enter sleep mode.
 * AT+CSCLK=1	Enable slow clock, it is controlled by DTR. When DTR is high, module can enter sleep mode. When DTR changes to low level, module can quit sleep mode
 */
bool sim800l::setSleepMode(bool state){

    _sim800l_sleepMode = state;

    if (_sim800l_sleepMode) _writeWord((char*)"AT+CSCLK=1\r\n");
    else 			        _writeWord((char*)"AT+CSCLK=0\r\n");

    if ( (_receive_answer().indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}

bool sim800l::getSleepMode(){
    return _sim800l_sleepMode;
}

/*
 * AT+CFUN=0	Minimum functionality
 * AT+CFUN=1	Full functionality (defualt)
 * AT+CFUN=4	Flight mode (disable RF function)
*/
bool sim800l::setFunctionalityMode(uint8_t fun){
    switch (fun){
    case 0:
    case 1:
    case 4:
        _sim800l_functionalityMode = fun;
        _writeWord((char*)"AT+CFUN=");
        _writeWord(myITOA(fun,10,0));
        _writeWord((char*)"\r\n");
        break;
    
    default:
        return SIM800L_NOT_OK;
    }

    if ( (_receive_answer().indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}

uint8_t sim800l::getFunctionalityMode(){
    return _sim800l_functionalityMode;
}


bool sim800l::simReady(){
    _writeWord((char*)"AT+CPIN?\r\n");
    if ( (_receive_answer().indexOf("ER")) == -1) return true;
    else return false;
}

bool sim800l::setPIN(String pin){
    String command;
    command  = "AT+CPIN=";
    command += pin;
    command += "\r\n";

    // Can take up to 5 seconds

    _writeWord((char*)&command[0]);

    if ( (_receive_answer().indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}

bool sim800l::_echo(uint8_t on){
    if(on) _writeWord((char*)"ATE1\r\n");
    else _writeWord((char*)"ATE0\r\n");
    
    return (_receive_answer().indexOf("OK") != -1) ? SIM800L_OK : SIM800L_NOT_OK;
}

String sim800l::getProductInfo(){
    _writeWord((char*)"ATI\r\n");
    return (_receive_answer());
}


String sim800l::getOperatorsList(){

    // Can take up to 45 seconds

    _writeWord((char*)"AT+COPS=?\r\n");

    return _receive_answer(45000);

}

String sim800l::getOperator(){

    _writeWord((char*)"AT+COPS ?\r\n");

    return _receive_answer();

}


bool sim800l::calculateLocation(){
    /*
    	Type: 1  To get longitude and latitude
    	Cid = 1  Bearer profile identifier refer to AT+SAPBR
    */

    uint8_t type = 1;
    uint8_t cid = 1;
	
	String tmp = "AT+CIPGSMLOC=" + String(type) + "," + String(cid) + "\r\n";
	_writeWord(&tmp[0]);
	
	/*
    this->SoftwareSerial::print("AT+CIPGSMLOC=");
    this->SoftwareSerial::print(type);
    this->SoftwareSerial::print(",");
    this->SoftwareSerial::print(cid);
    this->SoftwareSerial::print("\r");
	*/

    String data = _receive_answer(20000);

    if (data.indexOf("ER")!=(-1)) return SIM800L_NOT_OK;

    uint8_t indexOne;
    uint8_t indexTwo;

    indexOne = data.indexOf(":") + 1;
    indexTwo = data.indexOf(",");

    _sim800l_locationCode = data.substring(indexOne, indexTwo);

    indexOne = data.indexOf(",") + 1;
    indexTwo = data.indexOf(",", indexOne);

    _sim800l_longitude = data.substring(indexOne, indexTwo);

    indexOne = data.indexOf(",", indexTwo) + 1;
    indexTwo = data.indexOf(",", indexOne);

    _sim800l_latitude = data.substring(indexOne, indexTwo);

    return SIM800L_OK;

}

String sim800l::getLocationCode(){
    return _sim800l_locationCode;
    /*
     Location Code:
     0      Success
     404    Not Found
     408    Request Time-out
     601    Network Error
     602    No Memory
     603    DNS Error
     604    Stack Busy
     65535  Other Error
    */
}

String sim800l::getLongitude(){
    return _sim800l_longitude;
}

String sim800l::getLatitude(){
    return _sim800l_latitude;
}


//
//PUBLIC METHODS
//

uint8_t sim800l::reset(){
    //if (LED_FLAG) digitalWrite(LED_PIN,1);
    unsigned long curr_time = millis();

    digitalWrite(SIM800L_RST_PIN,0);
    delay(1000);
    digitalWrite(SIM800L_RST_PIN,1);
    delay(1000);

    // wait for the module response - try aprox. 4 times
    do{
        _writeWord((char*)"AT\r\n");
    }while((_receive_answer().indexOf("OK")==-1) && ((millis()-curr_time) < SIM800L_TIMEOUT*4));

    //wait for sms ready
    //while (_receive_answer().indexOf("SMS")==-1 );

    //if (LED_FLAG) digitalWrite(LED_PIN,0);

    return ((millis()-curr_time) < SIM800L_TIMEOUT*4) ? SIM800L_OK : SIM800L_NOT_OK;
}

void sim800l::shutdown(){
    digitalWrite(SIM800L_RST_PIN,0);
}

void sim800l::setPhoneFunctionality(){
    /*AT+CFUN=<fun>[,<rst>]
    Parameters
    <fun> 0 Minimum functionality
    1 Full functionality (Default)
    4 Disable phone both transmit and receive RF circuits.
    <rst> 1 Reset the MT before setting it to <fun> power level.
    */
    _writeWord((char*)"AT+CFUN=1\r\n");
}


String sim800l::signalQuality(){
    /*Response
    +CSQ: <rssi>,<ber>Parameters
    <rssi>
    0 -115 dBm or less
    1 -111 dBm
    2...30 -110... -54 dBm
    31 -52 dBm or greater
    99 not known or not detectable
    <ber> (in percent):
    0...7 As RXQUAL values in the table in GSM 05.08 [20]
    subclause 7.2.4
    99 Not known or not detectable
    */
    _writeWord((char*)"AT+CSQ\r\n");
    return(_receive_answer());
}


void sim800l::activateBearerProfile(){
    _writeWord((char*)" AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\" \r\n");
    _sim800l_buffer=_receive_answer();  // set bearer parameter
    _writeWord((char*)" AT+SAPBR=3,1,\"APN\",\"internet\" \r\n" );
    _sim800l_buffer=_receive_answer();  // set apn
    _writeWord((char*)" AT+SAPBR=1,1 \r\n");
    delay(1200);
    _sim800l_buffer=_receive_answer();			// activate bearer context
    _writeWord((char*)" AT+SAPBR=2,1\r\n ");
    delay(3000);
    _sim800l_buffer=_receive_answer(); 			// get context ip address
}


void sim800l::deactivateBearerProfile(){
    _writeWord((char*)"AT+SAPBR=0,1\r\n ");
    delay(1500);
}



bool sim800l::answerCall(){
    _writeWord((char*)"ATA\r\n");
    //Response in case of data call, if successfully connected
    if ( (_receive_answer().indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}


void  sim800l::callNumber(char* number){
    // check if sim ready
    if(!simReady()) return;

    _writeWord((char*)"ATD");
    _writeWord(number);
    _writeWord((char*)";\r\n");
}



uint8_t sim800l::getCallStatus(){
    /*
      values of return:

     0 Ready (MT allows commands from TA/TE)
     2 Unknown (MT is not guaranteed to respond to tructions)
     3 Ringing (MT is ready for commands from TA/TE, but the ringer is active)
     4 Call in progress

    */
    _writeWord((char*)"AT+CPAS\r\n");
    _sim800l_buffer=_receive_answer();
    return _sim800l_buffer.substring(_sim800l_buffer.indexOf("+CPAS: ")+7,_sim800l_buffer.indexOf("+CPAS: ")+9).toInt();

}


bool sim800l::hangoffCall(){
    _writeWord((char*)"ATH\r\n");
    _sim800l_buffer=_receive_answer();
    if ( (_sim800l_buffer.indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}


bool sim800l::sendSms(char* number,char* text){
    // first check if sim ok
    if(!simReady()) return SIM800L_NOT_OK;

    // Can take up to 60 seconds
    _writeWord((char*)"AT+CMGF=1\r\n"); 	//set sms to text mode
    if(_receive_answer().indexOf("ERROR") != -1) return SIM800L_NOT_OK;
    _writeWord((char*)"AT+CMGS=\"");  	// command to send sms
    _writeWord((char*)number);
    _writeWord((char*)"\"\r\n");
    if(_receive_answer().indexOf("ERROR") != -1) return SIM800L_NOT_OK;
    _writeWord((char*)text);
    _writeWord((char*)"\r\n");
    if(_receive_answer().indexOf("ERROR") != -1) return SIM800L_NOT_OK;
    _writeByte((char)26);
    _sim800l_buffer=_receive_answer(60000);
    //expect CMGS:xxx   , where xxx is a number,for the sending sms.
    if(_receive_answer().indexOf("ERROR") == -1) return SIM800L_OK;
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}


String sim800l::getNumberSms(uint8_t index){
    _sim800l_buffer=readSms(index);
    //Serial.println(_buffer.length());
    if (_sim800l_buffer.length() > 10) //avoid empty sms
    {
        uint8_t _idx1=_sim800l_buffer.indexOf("+CMGR:");
        _idx1=_sim800l_buffer.indexOf("\",\"",_idx1+1);
        return _sim800l_buffer.substring(_idx1+3,_sim800l_buffer.indexOf("\",\"",_idx1+4));
    }
    else
    {
        return "";
    }
}

bool sim800l::unReadSms(uint8_t * index_list, uint8_t * len){
    bool isUnReadSms = false;
    *len = 0;
    String index;

    _writeWord((char*)"AT+CMGF=1\r\n"); // set text mode

    if (( _receive_answer(5000).indexOf("ER")) ==-1){
        // send command
        _writeWord((char*)"AT+CMGL\r\n");

        // receive sms
        _sim800l_buffer = _receive_answer();

        // check for unread sms
        isUnReadSms = _sim800l_buffer.indexOf("UNREAD") != -1 ? true : false;

        while(_sim800l_buffer.indexOf("+CMGL:") != -1){
            _sim800l_buffer = _sim800l_buffer.substring(_sim800l_buffer.indexOf("+CMGL:")+6);
            index = _sim800l_buffer.substring(0,_sim800l_buffer.indexOf(",")); // first 
            index.replace(" ", "");
            index_list[*len] = index.toInt();
            *len += 1;
        }
    }

    return isUnReadSms;   
}

String sim800l::listSms(){
    _writeWord((char*)"AT+CMGF=1\r\n"); // set text mode

    if (( _receive_answer(5000).indexOf("ER")) ==-1){
        // send command
        _writeWord((char*)"AT+CMGL\r\n");
        
        return _receive_answer();
        //+CMGL: 1,"REC UNREAD","+351911599040","","20/08/08,15:52:03+04"
        //Teste!
    }
    return "";
}

String sim800l::readSms(uint8_t index){

    // Can take up to 5 seconds

    _writeWord((char*)"AT+CMGF=1\r\n"); // set text mode

    if (( _receive_answer(5000).indexOf("ER")) ==-1)
    {
        _writeWord((char*)"AT+CMGR=");
        _writeWord(myITOA(index,10,0));
        _writeWord((char*)"\r\n");
        _sim800l_buffer=_receive_answer();
        if (_sim800l_buffer.indexOf("CMGR:")!=-1)
        {
            return _sim800l_buffer;
        }
        else return "";
    }
    else
        return "";
}


bool sim800l::delAllSms(){
    // Can take up to 25 seconds

    _writeWord((char*)"AT+CMGDA=\"DEL ALL\"\r\n");
    _sim800l_buffer=_receive_answer(25000);
    if ( (_sim800l_buffer.indexOf("ER")) == -1)
    {
        return SIM800L_OK;
    }
    else return SIM800L_NOT_OK;
    // Error found, return 1
    // Error NOT found, return 0
}


void sim800l::RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second){
    _writeWord((char*)"AT+CCLK?\r\n");
    // if respond with ERROR try one more time.
    _sim800l_buffer=_receive_answer();
    if ((_sim800l_buffer.indexOf("ERR"))!=-1)
    {
        delay(50);
        _writeWord((char*)"AT+CCLK?\r\n");
    }
    if ((_sim800l_buffer.indexOf("ERR"))==-1)
    {
        _sim800l_buffer=_sim800l_buffer.substring(_sim800l_buffer.indexOf("\"")+1,_sim800l_buffer.lastIndexOf("\"")-1);
        *year=_sim800l_buffer.substring(0,2).toInt();
        *month= _sim800l_buffer.substring(3,5).toInt();
        *day=_sim800l_buffer.substring(6,8).toInt();
        *hour=_sim800l_buffer.substring(9,11).toInt();
        *minute=_sim800l_buffer.substring(12,14).toInt();
        *second=_sim800l_buffer.substring(15,17).toInt();
    }
}

//Get the time  of the base of GSM
String sim800l::dateNet(){
    _writeWord((char*)"AT+CIPGSMLOC=2,1\r\n ");
    _sim800l_buffer=_receive_answer();

    if (_sim800l_buffer.indexOf("OK")!=-1 )
    {
        return _sim800l_buffer.substring(_sim800l_buffer.indexOf(":")+2,(_sim800l_buffer.indexOf("OK")-4));
    }
    else
        return "0";
}

// Update the RTC of the module with the date of GSM.
bool sim800l::updateRtc(int utc){

    activateBearerProfile();
    _sim800l_buffer=dateNet();
    deactivateBearerProfile();

    _sim800l_buffer=_sim800l_buffer.substring(_sim800l_buffer.indexOf(",")+1,_sim800l_buffer.length());
    String dt=_sim800l_buffer.substring(0,_sim800l_buffer.indexOf(","));
    String tm=_sim800l_buffer.substring(_sim800l_buffer.indexOf(",")+1,_sim800l_buffer.length()) ;

    int hour = tm.substring(0,2).toInt();
    int day = dt.substring(8,10).toInt();

    hour=hour+utc;

    String tmp_hour;
    String tmp_day;
    //TODO : fix if the day is 0, this occur when day is 1 then decrement to 1,
    //       will need to check the last month what is the last day .
    if (hour<0)
    {
        hour+=24;
        day-=1;
    }
    if (hour<10)
    {

        tmp_hour="0"+String(hour);
    }
    else
    {
        tmp_hour=String(hour);
    }
    if (day<10)
    {
        tmp_day="0"+String(day);
    }
    else
    {
        tmp_day=String(day);
    }
    //for debugging
    //Serial.println("at+cclk=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n");
    String command = "AT+CCLK=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n";
    _writeWord(&command[0]);
    if ( (_receive_answer().indexOf("ER"))!=-1)
    {
        return SIM800L_NOT_OK;
    }
    else return SIM800L_OK;


}

String sim800l::_receive_answer(){
    // check rx interrupt status
    bool rx_int_status = SIM800L_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) SIM800L_DISABLE_RX_INT;

    String sim800l_answer = "";
    unsigned long curr_time = millis();

    // wait until receiving the first char
    while( (!_available()) && ((millis()-curr_time) < SIM800L_TIMEOUT) );
    
    // so far ok, timeout not reached
    if( (millis()-curr_time) < SIM800L_TIMEOUT ){
        curr_time = millis(); // reset timer
    
        do{
            if(_available())
                sim800l_answer += (char)_readByte();
        }while(((millis()-curr_time) < SIM800L_TIMEOUT) && 
                    (sim800l_answer.indexOf("OK\r\n") == -1) &&
                        (sim800l_answer.indexOf("ERROR\r\n") == -1) );
    
    }

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) SIM800L_ENABLE_RX_INT;

    return sim800l_answer;
}

String sim800l::_receive_answer(uint32_t timeout){
    // check rx interrupt status
    bool rx_int_status = SIM800L_RX_INT_STATUS;

    // if interrupt enabled, temporary disable it
    if(rx_int_status) SIM800L_DISABLE_RX_INT;

    String sim800l_answer = "";
    unsigned long curr_time = millis();

    // wait until receiving the first char
    while( (!_available()) && ((millis()-curr_time) < timeout) );
    
    // so far ok, timeout not reached
    if( (millis()-curr_time) < timeout ){
        curr_time = millis(); // reset timer
    
        do{
            if(_available())
                sim800l_answer += (char)_readByte();
        }while(((millis()-curr_time) < timeout) && 
                    (sim800l_answer.indexOf("OK\r\n") == -1) &&
                        (sim800l_answer.indexOf("ERROR\r\n") == -1) );
    
    }

    // if interrupt was disabled, re-enable it again
    if(rx_int_status) SIM800L_ENABLE_RX_INT;

    return sim800l_answer;
}

void sim800l_rx_isr(){
    while(SIM800L_AVAILABLE){
        Serial.write(SIM800L_READBYTE);
    }
    // clean interrup flag
    SIM800L_CLEAN_RX_INT;
}