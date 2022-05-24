#include <WiFi.h>
  WiFiClient ESP32_WIFI;
  
#define MICROSD_PIN 5
//Extension que va a tener el archivo a guardar en la memoria SD
#define EXTENSION ".json"

#include <PubSubClient.h>
  PubSubClient client ( ESP32_WIFI );
  
//ARDUINO JSON
#include <ArduinoJson.h>
DynamicJsonDocument doc(1024);
  
// Micro SD adapter
#include <SD.h>
#include <SPI.h>
File MicroSD_File;

//DISPLAY LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);//0x27

//RELOJ
#include "RTClib.h"
RTC_DS1307 RRTC;


//PINES
#include "pines.h"
pines Pins;


//SENSORES
#include <OneWire.h>
OneWire tempClima(13);

//LIBRERIA PARA EL SENSOR DE TEMPERATURA
#include <DallasTemperature.h>
DallasTemperature sensorDS18B20(&tempClima);

//HEADER DE SENSORES
#include "sensors.h"
sensors Sen;

//ACTUADORES
#include "actuators.h"
actuators Act;
//MQTT
#include "MQTT.h"
 MQTT mqtt;
 
//TASKS
#include "tasks.h"
tasks Tasks;

class invernadero_sensores {
  public:
    void startConfg();
};


void invernadero_sensores::startConfg(){
  //Pins de entrada de valores de sensores
  pinMode(Pins.PinST, INPUT);//Sensor temperatura tierra
  pinMode(Pins.PinFS, INPUT); //Fotosensor
  pinMode(Pins.PinC, INPUT); //Caudal
  
  //Pins de actuadores
  pinMode(Pins.PinRB, OUTPUT);//Relay bomba
}