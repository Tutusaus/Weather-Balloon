//Keyes GSM GPRS SIM900
////////////////////////////////////////////////////////////////////////
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

char number[20];
byte stat=0;
int pin=1;
char value_str[5];
//////////////////////////////////////////////////////////////////////



//Adafruit GPS variables
//////////////////////////////////////////////////////////////////////
//Make sure to install the adafruit GPS library from https://github.com/adafruit/Adafruit-GPS-Library
#include <Adafruit_GPS.h> //Load the GPS Library. Make sure you have installed the library form the adafruit site above
// TX to 9 and RX to 10
SoftwareSerial mySerial(9, 10); //Initialize SoftwareSerial, and tell it you will be connecting through pins 9 and 10
Adafruit_GPS GPS(&mySerial); //Create GPS object

String NMEA1;  //We will use this variable to hold our first NMEA sentence
String NMEA2;  //We will use this variable to hold our second NMEA sentence
char c;       //Used to read the characters spewing from the GPS module
//////////////////////////////////////////////////////////////////////



//SD
///////////////////////////////////////////////////////////////////////
/*
#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
int chipSelect = 8; //chipSelect pin for the SD card Reader
File mySensorData; //Data object you will write your sesnor data to
*/
///////////////////////////////////////////////////////////////////////


void setup()
{

   Serial.begin(9600);  //Conflicte entre 9600(GSM) i 115200(GPS i SD)
  
  
  //Adafruit GPS
  //////////////////////////////////////////////////////////////////
      GPS.begin(9600);       //Turn GPS on at baud rate of 9600
      GPS.sendCommand("$PGCMD,33,0*6D"); // Turn Off GPS Antenna Update
      GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); //Tell GPS we want only $GPRMC and $GPGGA NMEA sentences
      GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate     
      delay(1000);
  ///////////////////////////////////////////////////////////////////////////////////////////


 //Keyes GSM GPRS SIM900
  ///////////////////////////////////////////////////////////////////
     pinMode(pin,INPUT);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
      if (gsm.begin(2400))
          Serial.println("\nstatus=READY");
      else Serial.println("\nstatus=IDLE");
  //////////////////////////////////////////////////////////////////


  //SD
  ///////////////////////////////////////////////////////////////////
  /*
  pinMode(10, OUTPUT); //Must declare 10 an output and reserve it to keep SD card happy
  SD.begin(chipSelect); //Initialize the SD card reader
  
  if (SD.exists("NMEA.txt")) { //Delete old data files to start fresh
    SD.remove("NMEA.txt");
  }
  if (SD.exists("GPSData.txt")) { //Delete old data files to start fresh
    SD.remove("GPSData.txt");
  }
  */
  ///////////////////////////////////////////////////////////////////
  
};

void loop()
{


  //Keyes GSM GPRS SIM900
  ///////////////////////////////////////////////////////////////////////////////////////////
     //Chekcs status of call
     stat=call.CallStatusWithAuth(number,1,3);
     //If the incoming call is from an authorized number
     //saved on SIM in the positions range from 1 to 3.
     if(stat==CALL_INCOM_VOICE_AUTH) {
          //Hang up the call.
          call.HangUp();
          delay(2000);
          //Send SMS
          sms.SendSMS(number,value_str);
     }
     Serial.println("GSM");
  ///////////////////////////////////////////////////////////////////////////////////////////

 
   //Adafruit GPS
  ///////////////////////////////////////////////////////////////////////////////////////////
     readGPS();  //This is a function we define below which reads two NMEA sentences from GPS
  ///////////////////////////////////////////////////////////////////////////////////////////
   
   
  //SD
  ////////////////////////////////////////////////////////////////////////////////////////////
  /*
  if(GPS.fix==1) { //Only save data if we have a fix
  mySensorData = SD.open("NMEA.txt", FILE_WRITE); //Open file on SD card for writing
  mySensorData.println(NMEA1); //Write first NMEA to SD card
  mySensorData.println(NMEA2); //Write Second NMEA to SD card
  mySensorData.close();  //Close the file
  mySensorData = SD.open("GPSData.txt", FILE_WRITE);
  mySensorData.print(GPS.latitude,4); //Write measured latitude to file
  mySensorData.print(GPS.lat); //Which hemisphere N or S
  mySensorData.print(",");
  mySensorData.print(GPS.longitude,4); //Write measured longitude to file
  mySensorData.print(GPS.lon); //Which Hemisphere E or W
  mySensorData.print(",");
  mySensorData.println(GPS.altitude);
  mySensorData.close();
  }
  */
  ////////////////////////////////////////////////////////////////////////////////////////////

};

  //Adafruit GPS
//////////////////////////////////////////////////////////////////////////////////////////////  
 void readGPS(){  //This function will read and remember two NMEA sentences from GPS
Serial.println("GPS");
  clearGPS();    //Serial port probably has old or corrupt data, so begin by clearing it all out
  while(!GPS.newNMEAreceived()) { //Keep reading characters in this loop until a good NMEA sentence is received
  c=GPS.read(); //read a character from the GPS
  }
GPS.parse(GPS.lastNMEA());  //Once you get a good NMEA, parse it
NMEA1=GPS.lastNMEA();      //Once parsed, save NMEA sentence into NMEA1
while(!GPS.newNMEAreceived()) {  //Go out and get the second NMEA sentence, should be different type than the first one read above.
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());
NMEA2=GPS.lastNMEA();
  Serial.println(NMEA1);
  Serial.println(NMEA2);
  Serial.println("");
}
void clearGPS() {  //Since between GPS reads, we still have data streaming in, we need to clear the old data by reading a few sentences, and discarding these
  Serial.println("Clear");
while(!GPS.newNMEAreceived()) {
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());
while(!GPS.newNMEAreceived()) {
  c=GPS.read();
  }
GPS.parse(GPS.lastNMEA());

}
/////////////////////////////////////////////////////////////////////////////////////////
