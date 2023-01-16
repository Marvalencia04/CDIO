#ifndef SPARKFUN_YA_INCLUIDO
#define SPARKFUN_YA_INCLUIDO

#include "Humedad.h"
#include "Salinidad.h"
#include "Temperatura.h"
#include "Luminosidad.h"
#include "Ph.h"
//#include "GPS.h"
#include "wifi.h"
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;

#include <ESP8266WiFi.h>
#include "TinyGPSPlus.h"
TinyGPSPlus gps;
#define power_pin 5
const int LED_PIN = 5;

//Variables sensores//
int Sal =0;
int NHumedad = 0;
int NivelPh = 0;
int NivelLuz = 0;
float Temp = 0;
Salinidad S;
Humedad H;
Luminosidad L;
Ph PH;
Temperatura T;
wifi W;
#endif