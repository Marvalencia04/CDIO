
#include "Sparkfun.h"
//#include "GPS.h"
#include "Luminosidad.h"
#include "Humedad.h"
#include "PH.h"
#include "Salinidad.h"
#include "Temperatura.h"
#include "wifi.h"
Salinidad S;
Humedad H;
Luminosidad L;
Ph PH;
Temperatura T;
wifi W;
Sparkfun Fun;
void setup()
{
  Serial.begin(9600);
  //inicializamos la com. serie(UART) a 9600 baudios
  Serial.println("Inicializamos las mediciones");
  Fun.ads1015.begin();
  Fun.ads1015.setGain(GAIN_ONE);
  pinMode(Fun.power_pin, OUTPUT);
  digitalWrite(Fun.LED_PIN, HIGH);
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
  int NHumedad=H.medirH();
  delay(500);
  //llamamos a la funcion de calcular de salinidad
  int Sal =S.medirSal();
  delay(500);
  
  //llamamos a la funcion de calcular de temperatura
  float Temp=T.medirTemp();
  delay(500);
  
  //llamamos a la funcion de calcular de el nivel de Ph Puerto 3
  int NivelPh=PH.medirPh();
  
  int NivelLuz=L.medirLuz();
  delay(500);

  //Una vez calculados todos los datos los enviamos a la nube
  W.enviardatos(NHumedad,Sal,Temp,NivelPh,NivelLuz);
}
