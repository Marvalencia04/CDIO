#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;
#include "Humedad.h"
#include "Salinidad.h"
#include "Temperatura.h"
#include "Luminosidad.h"
#include "Ph.h"
#include "GPS.h"
#include "Wifi.h"

////////////////////////////////////////////////////////////////////////////////////////////////
/////////////// Variables Sensores /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


int channelValue = 0;
int pHArray[ArrayLenght];
int pHArrayIndex = 0;
int sensorValue = 0;




float Temperatura = 0;




void setup()
{
  Serial.begin(9600);
  //inicializamos la com. serie(UART) a 9600 baudios
  Serial.println("Inicializamos las mediciones");
  ads1015.begin();
  ads1015.setGain(GAIN_ONE);
  pinMode(power_pin, OUTPUT);

  connectWiFi();
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
  Humedad = Calcular_humedad(0);
  delay(500);
  //llamamos a la funcion de calcular de salinidad
  Sal = Calcular_salinidad();
  delay(500);
  
  //llamamos a la funcion de calcular de temperatura
  Temperatura= Calcular_temperatura(2);
  delay(500);
  
  //llamamos a la funcion de calcular de el nivel de Ph Puerto 3
  NivelPh=Calcular_Ph(3);
  
  delay(500);

  //Una vez calculados todos los datos los enviamos a la nube
  EnviarDatos(Humedad,Sal,Temperatura,NivelPh);
}
