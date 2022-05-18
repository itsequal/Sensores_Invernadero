//Variable para la cantidad de pulsos recibidos por el caudalimetro
volatile byte NumPulsos;
//Variable usada para calibrar la formula de obtencion de L/Minuto
float calibracion = 4.5; //4.5 o 7.5
byte pulsos = 0;
float flujoAgua;
unsigned int flujoMiliLitros;
//Clase donde se inicializan las funciones de los sensores
class sensors {
  //Otras funciones necesarias
  public:
    void startSensorDS();

  //Funciones para los sensores
  public:
    int HumTierra ( void );
    int Fotosensor( void );
    float TempClima( void );
    float Caudal(unsigned long);
};


//Función que detecta los pulsos dado por el caudal
 
void ContarPulsos(){ 
  NumPulsos++;  //incrementamos la variable de pulsos
}

//Funcion que inicializa el sensor de temperatura
void sensors :: startSensorDS(){
  sensorDS18B20.begin();
}

//Funcion que lee la información del pin especificado y la retorna
int sensors :: HumTierra(){
  int SensorValue = analogRead(Pins.PinST);
  Serial.println(SensorValue);
  return SensorValue;
}

//Funcion que inicializa el foto sensor
int sensors :: Fotosensor(){
  int FSValue = analogRead(Pins.PinFS);
  return FSValue;
}

//Funcion que guarda la información proveniente del sensor de temperatura
float sensors :: TempClima(){
  //Se llama la funcion para guardar la temperatura
  sensorDS18B20.requestTemperatures();
  //Se obtiene la temperatura en grados C°, el indice indica el número de sensor en caso de que se tenga mas de uno
  float tempC = sensorDS18B20.getTempCByIndex(0);
  return tempC;
}

//Funcion que incializa el caudal
float sensors :: Caudal(unsigned long previousMillis){
  pulsos = NumPulsos;
  NumPulsos=0;

  //Se calcula los litros por minuto
  flujoAgua =((4000.0 / (millis() - previousMillis)) * pulsos) / calibracion;
  flujoMiliLitros = (flujoAgua / 60)* 4000;
  return flujoAgua;
}
