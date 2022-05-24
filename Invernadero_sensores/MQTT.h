//Se definen el SSID de la red Wi-Fi, la contraseña y el enlace del servidor MQTT
const char* HOTSPOT_WIFI = "HOTSPOT";
const char* HOTSPOT_PWD = "123456789";  
const char* MQTT_SERVER = "test.mosquitto.org";
//Se define el puerto MQTT y el Topic
#define MQTT_PORT 1883
#define TOPIC "6D/E1"

//Clase donde se inicializan las funciones de MQTT
class MQTT {
  public:
    void publish_MQTT ( void );
    void reconnect_MQTT ( void );
    void setup_WiFi ( void ); 
    void set_MQTT_server ( void );
};

//Funcion que incializa el servidor
void MQTT :: set_MQTT_server ( void ) {
  client.setServer ( MQTT_SERVER, MQTT_PORT );
}

//Funcion que publica informacion dentro del Topic seleccionado
void MQTT :: publish_MQTT ( void ) {
  Serial.println ( "Publicando información" );
  client.publish( TOPIC, Act.json_string.c_str());
}

//Funcion que valida la conexion al cliente; tambien se usa para comenzar la conexion por primera vez para ahorrarnos una funcion extra de conexion
void MQTT :: reconnect_MQTT ( void ) {
//connected verifica si es verdadera o falsa la conexion
if ( ! client.connected ( ) ) {

    while ( ! client.connected ( ) ) {
      
    Serial.print ( "Conectado nuevamente al servidor" );

//client.connect realiza la conexion al Topic elegido
if ( client.connect ( "6D/E1/INFO" ) ) {
      
      Serial.println ( "Cliente conectado" );
      
      //Se hace la suscripcion al Topic seleccionado      
	  client.subscribe("6D/E1/INFO");
      
    } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }
  client.loop();
}



//Funcion que realiza la conexion a la red Wi-Fi
void MQTT :: setup_WiFi ( void ) {
  Serial.println ( "Configurando WiFi: " );
  WiFi.begin ( HOTSPOT_WIFI, HOTSPOT_PWD );
  
  while ( WiFi.status ( ) != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  
  Serial.println("Se configuró el wifi correctamente");//Salto de linea
}


/*
Funcion que retorna la informacion que viene del Topic elegido en el Subscribe; tiene que tomarse encuenta el hecho
de que la informacion entra de letra en letra, por lo que tienes que usar un ciclo for para rearmar el mensaje
dentro de una variable nueva de formato String, tomando en cuenta el valor de longitud que entra
*/
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}