/*
+--------------------------------------------------------------------------------------------------------+
|                                       INVERNADERO INTELIGENTE 6D                                       |
+--------------------------------------------------------------------------------------------------------+
| Integrantes del Equipo:                                                                                |
|    Javier Anastasio Barreto Martinez                                                                   |
|    Christian Eduardo Sanchez Orozco                                                                    |
|    Alan Manuel Silva Larios                                                                            |
|    Oskar Pablo Rolon Gonzalez                                                                          |
|    Juan Jose Hernandez Lucas                                                                           |
|                                                                                                        |
| Sensores Utilizados:                                                                                   |
|    Relay - 3.3v - Salida Digital                                                                       |
|    Pantalla LCD 16x4 - 5v - Salida I2C                                                                 |
|    Modulo Micro SD - 5v - Salida SPI                                                                   |
|    Modulo RTC - 5v - Salida I2C                                                                        |
|    Sensor de Humedad YL-69 - 5v - Salida Digital                                                       |
|    Sensor de Temperatura DS18B20 - 5v - Salida 1-Wire                                                  |
|    Sensor de Luz - 5v - Salida Digital                                                                 |
|    Sensor Caudal YF-S201 - 5v - Salida Digital                                                         |
|    Bomba de Agua - 12v, 6A - Salida Digital                                                            |
|                                                                                                        |
| Servidor/Broker MQTT                                                                                   |
|    Eclipse Mosquitto                                                                                   |
|                                                                                                        |
| Cliente MQTT                                                                                           |
|    MQTT Lens                                                                                           |
|                                                                                                        |
| Version de MQTT                                                                                        |
|    3.1.1                                                                                               |
+--------------------------------------------------------------------------------------------------------+ 
*/

#include "invernadero_sensores.h"
invernadero_sensores start;

void setup() {
  Serial.begin(115200); //Se inicializa el puerto serial con un Baudrate de 115,200
  start.startConfg(); // Inicializa los pines
  Act.lcd_init(); //Inicializa el rejol
  Sen.startSensorDS(); //Se incializa el sensor de temperatura
  Act.MicroSD_init(); //Se incializa la MicroSD
  attachInterrupt(digitalPinToInterrupt(Pins.PinC), ContarPulsos, RISING); //Define el pin con interrupciones para el caudal
  Act.rtc_init(); //Se inicializa el RTC
  mqtt.setup_WiFi ( ); //Se hace la conexion a la red Wi-Fi
  mqtt.set_MQTT_server ( ); //Se hace la conexion al servidor MQTT
  client.setCallback(callback); //Llamada de retorno a la informacion que llega mediante el Subscribe de MQTT
}

void loop() {
  Tasks.currentMillis = millis(); //Se inicializa el conteo de milisegundos
  Tasks.call_tasks(); //Se llaman todas las tareas
}
