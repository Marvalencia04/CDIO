//Humedad.cpp//
#include "Humedad.h"
#include "Sparkfun.h"
Sparkfun FunH;
int Humedad::medirH()
{
  //Leemos del canal channelValue a través del ADS1115
  sensorValue = FunH.ads1015.readADC_SingleEnded(channelValue);
  //mapeamos el valor leido para un porcentaje entre 0 a 100
  humidityValue = map(sensorValue, 22484 , 10100, 0, 100);
  //imprimimos por pantalla si esta seco o humedo
  //  if (sensorValue >)
  //  {
  //    Serial.println("El medidor esta seco");
  //  }
  //  else
  //  {
  //    Serial.println("El medidor esta mojado");
  //  }
  //limitamos los valores entre 0 y 100 para minimizar errores
  if (humidityValue >= 100)
  {
    humidityValue = 100;
  }
  if (humidityValue <= 0)
  {
    humidityValue = 0;
  }
  return (humidityValue);
}