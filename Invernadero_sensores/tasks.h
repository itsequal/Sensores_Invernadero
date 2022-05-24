class tasks {
  //variables
  public:
    unsigned long currentMillis;
    unsigned long m5s = 0, m4s = 0;
    
  //funciones
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
  //Se reconecta el MQTT
  mqtt.reconnect_MQTT ( );
  
//Dependiendo del valor del sensor (humedad del suelo), se inicializará el riego o se detendrá
if(Sen.HumTierra()>700){
    Serial.println("Comenzando riego");
    Act.relay(1);
  } else {
    Serial.println("Deteniendo riego");
    Act.relay(0);
  }
 
  //Se guardan los valores de los sensores dentro de un JSON
  doc.clear();
  doc["HumedadTierra"] = Sen.HumTierra();
  doc["FotoSensor"] = Sen.Fotosensor();
  doc["Litros/minutos"] = Sen.Caudal();
  doc["Sensor de agua"] = Sen.TempClima();
  doc["Equipo"] = "1 - Alfa Buena maravilla Onda Dinamita Escuadron Lobo";
  doc["tiempo"] = Act.fecha+" "+Act.tiempo;
  //Se almacena información en caso de que la bomba se encienda
  if (Act.BombState==true)
    doc["BombaAgua"] = "Se activo la bomba el " + Act.fecha+" a las "+Act.tiempo;
    
  //Le da formato de JSON a la informacion que se guardó previamente y se indica la salida de los datos
  serializeJsonPretty(doc, Serial);

  //Se pasa el conteo de milisegundos al sensor caudal  
  Act.printLCD();

  //Se publica en MQTT	 
  mqtt.publish_MQTT ( );
  
  //Se guarda el JSON
  Act.JSON();
}


void tasks :: _4s(){
  //Se llama la funcion donde se le da formato al tiempo y fecha
  Act.get_format_time();
  Act.get_format_date();
}