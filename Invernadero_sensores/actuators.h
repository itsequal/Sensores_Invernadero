//Clase que incluye las funciones para usar los actuadores
class actuators{
  public:
    void relay( int );
    bool BombState;

    //LCD (display)
    void lcd_init( void );
    long printLCD( void );
    
    //MircoSD
    void MicroSD_init( void );
    void FileID( void );
    void JSON ( void );
    void JSON_SaveFile( DynamicJsonDocument *);

    //RTC
    uint8_t hora, minuto, segundo, dia, mes, wday;
    uint16_t ano;
    String fecha, tiempo, filename,json_string="" ;
    
    void rtc_init( void );
    void get_time( void );
    void get_format_time( void );
    void get_format_date( void );
};

//Funcion del relay en la cual entra un dato de 1 o 0 y dependiendo de cada uno, se inicia el actuador para encender el dispositivo al cual esta conectado (la bomba)
void actuators::relay(int value){
  if(value==1)
  {
    Serial.println("Encendiendo bomba");
    digitalWrite(Pins.PinRB, LOW);
    BombState = true;
  } else {
    Serial.println("Apagando bomba");
    digitalWrite(Pins.PinRB, HIGH);
    BombState = false;
  }
}

//Funcion que inicia la pantalla LCD
void actuators::lcd_init( void ){
  Wire.begin();
  lcd.init();
  lcd.backlight();
}

//Funcion que imprime los datos de los sensores en la pantalla
long actuators::printLCD( ){
  //setCursor nos pone en el pixel elegido de la pantalla de 16x4
  lcd.setCursor(0,0);
   //print escribe el dato que ingresemos dentro del parentesis
  lcd.print("H: ");
  lcd.print(Sen.HumTierra());
  lcd.setCursor(8,0);
  lcd.print("TC: ");
  lcd.print(Sen.Fotosensor());
  lcd.setCursor(0,1);
  lcd.print("C:");
  lcd.print(Sen.TempClima());
  lcd.setCursor(8,1);
  lcd.print("L:");
  lcd.print(Sen.Caudal());
}

//Funcion de inicio del reloj en tiempo real
void actuators :: rtc_init( void ){
//Se utiliza un ciclo While para validar en caso de que haya una desconexion, begin inicializa el reloj
  while (! RRTC.begin()) {
    
    Serial.println(F("Hay un error al reconocer el RTC, revise las conexiónes e intente de nuevo"));
    delay(10);
    
  }
  //Adjust establece una fecha inicial a partir de la cual se iniciará el conteo
  //RRTC.adjust(DateTime(2022, 5, 18, 9, 0, 0));
  Serial.println(F("El RTC se ha iniciado correctamente"));
}

//Funcion que toma el tiempo que lleva contando el reloj y guarda en variables independientes cada dato
void actuators :: get_time( void ){
  DateTime now = RRTC.now();
  ano = now.year();
  mes = now.month();
  dia = now.day();
  hora = now.hour();
  minuto = now.minute();
  segundo = now.second();
}

//Funcion que corrige el formato del tiempo (agrega un 0 cuando sea necesario para que la hora sea en formato xx:yy en vez de xx:y), también separa con una '/' el dia,
//mes y año 
void actuators :: get_format_date ( void ){
  get_time();
  fecha = "";
  if ( dia < 10 ) fecha += '0';
  fecha += dia;
  fecha += '/';
  if ( mes < 10 ) fecha += '0';
  fecha += mes;
  fecha += '/';
  fecha += ano;
  
}

//Funcion que corrige el formato de la hora (agrega un 0 cuando sea necesario para que la hora sea en formato xx:yy en vez de xx:y), también separa con una '/' la hora,
//minuto y segundo
void actuators :: get_format_time ( void ){
  get_time();
  tiempo = "";
  if ( hora < 10 ) tiempo += '0';
    tiempo += hora;
    tiempo += ':';
  
  if ( minuto < 10 ) tiempo += '0';
    tiempo += minuto;
    tiempo += ':';
    
  if ( segundo < 10 ) tiempo += '0';
    tiempo += segundo;
}

//Funcion que inicializa la Micro SD
void actuators :: MicroSD_init( void ){
  while (!SD.begin(MICROSD_PIN)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
  }
  Serial.println("card initialized.");
}

//Funcion que establece el nombre del archivo donde se va a guardar la información
void actuators :: FileID( void ){
  filename = '/';

  if ( dia < 10 ) filename += '0';
  filename += dia;
  filename+='-';
  
  if ( mes < 10 ) filename += '0';
  filename += mes;
  filename+='-';

  filename += ano;

  filename += EXTENSION;
}

//Funcion donde se empaqueta la información en forma de JSON (información de los sensores y del equipo)
void actuators :: JSON( void ){
  JSON_SaveFile( &doc );
}

//Funcion que guarda el JSON en la memoria
void actuators :: JSON_SaveFile( DynamicJsonDocument * doc){
  FileID ( );
  json_string = "";
  MicroSD_File = SD.open ( filename, FILE_APPEND );
  if (MicroSD_File) {
    serializeJson(*doc, json_string);
    MicroSD_File.print(json_string);
    MicroSD_File.println(",");
    MicroSD_File.close();
  }
}














