//Se definen las variables para los conteos y el almacenamiento de informacion
int valorht = 0;
int valorfs = 0;
float valortc = 0.0;
float valorcd = 0;

class tasks {
  //Variables
  public:
    unsigned long currentMillis;
    unsigned long m5s = 0, m4s = 0;
    
  //Funciones
  public:
    void call_tasks();
    void _5s ();//Tareas que se ejecutaran cada 5 segundos
    void _4s ();//Tareas que se ejecutaran cada 4 segundos
};

//Funcion que realiza un conteo cada 4 segundos y a 5 segundos
void tasks :: call_tasks(){
  if(currentMillis-m4s>=4000){
    m4s = currentMillis;
    tasks::_4s();
  }
  if(currentMillis-m5s>=5000){
    m5s = currentMillis;
    tasks::_5s();
  }
}

//Funcion que realiza varias tareas cada 5 segundos
void tasks :: _5s(){
  //Se guarda el valor del sensor de humedad
  valorht = Sen.HumTierra();
  //Se llama la funcion donde se le da formato al tiempo y fecha
  Act.get_format_time();
  Act.get_format_date();
  
  //Dependiendo del valor de ht (humedad del suelo), se inicializará el riego o se detendrá
  if(valorht>700){
    Serial.println("Comenzando riego");
    Act.relay(1);
  } else {
    Serial.println("Deteniendo riego");
    Act.relay(0);
  }
  
  //Se pasa el conteo de milisegundos al sensor caudal
  Act.printLCD(m4s);

  //Se guardan los valores de los sensores dentro de un JSON
  doc["HumedadTierra"] = valorht;
  doc["FotoSensor"] = valorfs;
  doc["Litros/minutos"] = valorcd;
  doc["Sensor de agua"] = valortc;
  
  //Le da formato de JSON a la informacion que se guardó previamente y se indica la salida de los datos
  serializeJsonPretty(doc, Serial);

  //Se guarda el JSON 
  Act.JSON();
  
  //Se reconecta al servidor MQTT
  mqtt.reconnect_MQTT ( );
  
  //Se publica dentro del servidor MQTT
  mqtt.publish_MQTT ( );
}

//Funcion que guarda cada 4 segundos los valores especificados
void tasks :: _4s(){;
  valorfs = Sen.Fotosensor();
  valortc = Sen.TempClima();
  valorcd = Sen.Caudal(m4s);
}
