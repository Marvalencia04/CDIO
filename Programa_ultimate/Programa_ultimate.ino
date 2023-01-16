
#include "Sparkfun.h"
void setup()
{
  Serial.begin(9600);
  //inicializamos la com. serie(UART) a 9600 baudios
  Serial.println("Inicializamos las mediciones");
  ads1015.begin();
  ads1015.setGain(GAIN_ONE);
  pinMode(power_pin, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
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
  NHumedad =H.medirH();
  delay(500);
  //llamamos a la funcion de calcular de salinidad
  Sal =S.medirSal();
  delay(500);
  
  //llamamos a la funcion de calcular de temperatura
  Temp=T.medirTemp();
  delay(500);
  
  //llamamos a la funcion de calcular de el nivel de Ph Puerto 3
  NivelPh=PH.medirPh();
  
  NivelLuz=L.medirLuz();
  delay(500);

  //Una vez calculados todos los datos los enviamos a la nube
  W.enviardatos(NHumedad,Sal,Temp,NivelPh,NivelLuz);
}
