#include "Sparkfun.h"
#include "wifi.h"
Sparkfun Fun;
wifi W;
void setup()
{
  Serial.begin(9600);
  //inicializamos la com. serie(UART) a 9600 baudios
  Serial.println("Inicializamos las mediciones");
  Fun.ads1015.begin();
  Fun.ads1015.setGain(GAIN_ONE);
  pinMode(W.power_pin, OUTPUT);
  digitalWrite(W.LED_PIN, HIGH);
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print("Server_Host: ");
  Serial.println(Server_Host);
  Serial.print("Port: ");
  Serial.println(String( Server_HttpPort ));
  Serial.print("Server_Rest: ");
  Serial.println(Rest_Host);
#endif
}

void loop()
{
  //llamamos a la funcion de calcular de humedad
  int NHumedad=Fun.medirH(5);
  delay(500);
  //llamamos a la funcion de calcular de salinidad
  int Sal =Fun.medirSal();
  delay(500);
  
  //llamamos a la funcion de calcular de temperatura
  float Temp=Fun.medirTemp(4);
  delay(500);
  
  //llamamos a la funcion de calcular de el nivel de Ph Puerto 3
  float NivelPh=Fun.medirPh(3);
  
  int NivelLuz=Fun.medirLuz(2);
  delay(500);

  //Una vez calculados todos los datos los enviamos a la nube
  W.enviardatos(NHumedad,Sal,Temp,NivelPh,NivelLuz);
}
