//SD module
/////////////////////////////////////////////////////////////////////////////////////
#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library
int chipSelect = 4; //chipSelect pin for the SD card Reader
File Document; //Data object you will write your sesnor data to
/////////////////////////////////////////////////////////////////////////////////////




//BMP180 (Temperatura, pressió, altitud)
/////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;
////////////////////////////////////////////////////////////////////////////////////




//ds18b20 (temperatura -55ºC fins +125ºC)
////////////////////////////////////////////////////////////////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
////////////////////////////////////////////////////////////////////////////////////




//DHT11 (humitat i temperatura)
////////////////////////////////////////////////////////////////////////////////////
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN  8         
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
////////////////////////////////////////////////////////////////////////////////////




void setup() {

  Serial.begin(9600);
  
  while (!Serial){
    ;
  }

  //SD module
  ///////////////////////////////////////////////////////////////////////////////////
  pinMode(10, OUTPUT); //Must declare 10 an output and reserve it to keep SD card happy
  SD.begin(chipSelect); //Initialize the SD card reader
  
  if (SD.exists("Dades.txt")) { //Delete old data files to start fresh
    SD.remove("Dades.txt");
  }
  
  delay(15);
  
  if (SD.exists("T_int.txt")) { //Delete old data files to start fresh
    SD.remove("T_int.txt");
  }
  
  delay(15);
  
  if (SD.exists("T_ext.txt")) { //Delete old data files to start fresh
    SD.remove("T_ext.txt");
  }

  delay(15);

  if (SD.exists("Alt.txt")) { //Delete old data files to start fresh
    SD.remove("Alt.txt");
  }
  delay(15);
  ///////////////////////////////////////////////////////////////////////////////////




  //BMP180 (Temperatura, pressió, altitud)
  //////////////////////////////////////////////////////////////////////////////////
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
  ///////////////////////////////////////////////////////////////////////////////////




  //ds18b20 (temperatura -55ºC fins +125ºC)
  ///////////////////////////////////////////////////////////////////////////////////
  sensor.begin();
  ///////////////////////////////////////////////////////////////////////////////////



  
  //DHT11 (humitat i temperatura)
  ///////////////////////////////////////////////////////////////////////////////////
  // Initialize device.
  dht.begin();
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  ///////////////////////////////////////////////////////////////////////////////////

}




void loop() {

 Serial.println("Ok");

 //ds18b20 (temperatura -55ºC fins +125ºC)
 ///////////////////////////////////////////////////////////////////////////////////////
   sensor.requestTemperatures();
   float lectura = sensor.getTempCByIndex(0);
 ///////////////////////////////////////////////////////////////////////////////////////




 //DHT11 (humitat i temperatura)
 ///////////////////////////////////////////////////////////////////////////////////////
  // Delay between measurements.
  //delaMS = 1000(1seg)
  //sensor.min_delay = 1000000(10seg)
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  dht.humidity().getEvent(&event);
 ///////////////////////////////////////////////////////////////////////////////////////
 
 
  //SD module
 ///////////////////////////////////////////////////////////////////////////////////////
 Document = SD.open("Dades.txt", FILE_WRITE); //Open file on SD card for writing
 Document.print("Temperatura externa: ");
 Document.print(lectura); //Write first NMEA to SD card
 Document.println("*C");
 Document.print("Temperatura interna: ");
 Document.print(bmp.readTemperature());
 Document.println("*C");
 Document.print("Humitat interna: ");
 Document.print(event.relative_humidity);
 Document.println("%");
 Document.print("Pressio interna: ");
 Document.print(bmp.readPressure());
 Document.println(" Pa");
 // Calculate altitude assuming 'standard' barometric
 // pressure of 1013.25 millibar = 101325 Pascal
 Document.print("Altitud: ");
 Document.print(bmp.readAltitude());
 Document.println(" metres");
 Document.print("Pressio al nivell del mar: ");
 Document.print(bmp.readSealevelPressure());
 Document.println(" Pa");
 // you can get a more precise measurement of altitude
 // if you know the current sea level pressure which will
 // vary with weather and such. If it is 1015 millibars
 // that is equal to 101500 Pascals.
 Document.print("Altitud real: ");
 Document.print(bmp.readAltitude(101500));
 Document.println(" metres"); 
 Document.println("---------------------------------------------------------------------");
 Document.close();  //Close the file

 Serial.println("SD done");
 delay(15);
 
 Document = SD.open("T_int.txt", FILE_WRITE);
 Document.println(bmp.readTemperature());
 Document.close();  //Close the file

 Serial.println("T_int done");
 delay(15);
 
 Document = SD.open("T_ext.txt", FILE_WRITE);
 Document.println(lectura);
 Document.close();  //Close the file

 Serial.println("T_ext done");
 delay(15);
 
 Document = SD.open("Alt.txt", FILE_WRITE);
 Document.println(bmp.readAltitude());
 Document.close();  //Close the file

 Serial.println("Alt done");
 ///////////////////////////////////////////////////////////////////////////////////////
 delay(1000);


}
