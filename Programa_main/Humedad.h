#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;


class humedad{
    private:
      int humidityValue;
      int sensorValue;
    public:
      int medir (int);
};
