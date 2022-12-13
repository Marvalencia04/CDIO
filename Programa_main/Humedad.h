#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;


class humedad
  {
    private:
    int humidityValue = 0;
    int sensorValue = 0;
    public:
      int medir (int channelValue)
        {
          //Leemos del canal channelValue a través del ADS1115
          sensorValue = ads1015.readADC_SingleEnded(channelValue);
          //mapeamos el valor leido para un porcentaje entre 0 a 100
           humidityValue = map(sensorValue,22484 , 10100, 0, 100);
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
  }
