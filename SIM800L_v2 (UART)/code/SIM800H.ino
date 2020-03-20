 /*             GSM MODULE TEST
  *when you type in 's' the program will invoke 
  *function to SEND AN SMS FROM GSM module.if the 
  *user input is 'c ', the programwill invoke the 
  *function to 
  *     
  */
  

#include <SoftwareSerial.h> //including software serial library

SoftwareSerial sim800l(2, 3); // create a constructor of SoftwareSerial

void setup()
{
  sim800l.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  sim800l.println("AT");
  delay(1000);
  sim800l.println("AT+CFUN=?");
  delay(5000);
  //sim800l.println("AT+CFUN?");
  //delay(5000);
  sim800l.println("AT+CFUN=1");
  delay(5000);
}


void loop()
{
  if (Serial.available()>0) // checks for any data  coming through serial port of arduino.
   switch(Serial.read())   //
  {
    case 's':
      SendTextMessage();
      break;
    case 'c':
      DialVoiceCall();
      break;
  }

 if (sim800l.available()>0)
   Serial.write(sim800l.read()); // prints the data collected from software serial port to serial monitor of arduino
}


void SendTextMessage()
{
  Serial.println("Sending Text...");
  sim800l.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+2507*******\"\r");  
  delay(200);
  sim800l.print("This is a Test text message from SIM800L "); //the content of the message
  sim800l.print("\r"); 
  delay(500);
  sim800l.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  sim800l.println();
  Serial.println("Text Sent.");
   delay(500);
}

void DialVoiceCall()
{
  sim800l.println("ATD+25078*******;");//dial the number, must include country code
  delay(100);
  sim800l.println();
}

 
