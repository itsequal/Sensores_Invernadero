//Clase en la cual se especifican los pines utilizados en la placa ESP32
class pines{
  //Actuadores
  public:
    int PinRB = 14;//Relay conectado a la bomba
    
  //Sensores
  public:
    int PinST = 34;//Sensor de tierra
    int PinFS = 35;//Fotosensor
    int PinSC = 13;//Sensor del clima/agua
    int PinC = 32; //Caudal
};
