#include "SIM900.h"
#include <SoftwareSerial.h>
//We don't need the http functions. So we can disable the next line.
//#include "inetGSM.h"
#include "sms.h"
#include "call.h"

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to check if an incoming call is from an authorized
//number and in this case, send to this number an SMS with the value
//of a digital input.

//We have to create the classes for SMSs and calls.
CallGSM call;
SMSGSM sms;

char numero[20];
byte estat=0; 
int valor_int;
int pin=1;
char missatge_str[5];

void setup()
{
     pinMode(pin,INPUT);
     //Serial connection.
     Serial.begin(9600);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(2400))
          Serial.println("\nstatus=READY");
     else Serial.println("\nstatus=IDLE");
};

void loop()
{
     //Chekcs status of call
     estat=call.CallStatusWithAuth(numero,1,3);
     //If the incoming call is from an authorized number
     //saved on SIM in the positions range from 1 to 3.
     if(estat==CALL_INCOM_VOICE_AUTH) {
          //Hang up the call.
          call.HangUp();
          delay(2000);
          //Check the value of the input.
          valor_int=32769;
          //Convert the int to a string.
          itoa(valor_int,missatge_str,10);
          //Send an SMS to the previous number with
          //the value read previously.
          sms.SendSMS(numero,missatge_str);
     }
     delay(1000);
};
