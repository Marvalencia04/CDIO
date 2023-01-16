#ifndef HUMEDAD_YA_INCLUIDO
#define HUMEDAD_YA_INCLUIDO

class Humedad
  {
    private:
    int humidityValue = 0;
    int sensorValue = 0;
    int channelValue=2;
    public:
    int medirH();
  };
#endif