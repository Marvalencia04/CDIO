#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;
#include <ESP8266WiFi.h>


class Temperatura
  {
    private:
      double Temperatura = 0;      
      float m;
      float b;
      double Vo;
    public:
      float medir(int channelValue)
      {
          int16_t adc0 = ads1015.readADC_SingleEnded(channelValue);
  
          m = 33 * pow(10, -3);
          b = 0.95;
          Vo = (adc0 * 4.096 / 32767);
          Temperatura = ((Vo - b) / m);
          return (Temperatura);
      }
  }
