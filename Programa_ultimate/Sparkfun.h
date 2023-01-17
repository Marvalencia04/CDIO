#include <Adafruit_ADS1X15.h>
#include <ESP8266WiFi.h>
#include "TinyGPSPlus.h"




class Sparkfun
{
public:
    Adafruit_ADS1115 ads1015;
    const int LED_PIN = 5;
    const int power_pin = 5;
    TinyGPSPlus gps;
};
