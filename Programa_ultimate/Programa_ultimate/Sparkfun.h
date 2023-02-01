#include <Adafruit_ADS1X15.h>
#include <ESP8266WiFi.h>
#include "TinyGPSPlus.h"
#define Offset 7-6.25
#define ArrayLenght 40 //numero de muestras
#define samplingInterval 20
#define printInterval 600
class Sparkfun
{
  private:
    TinyGPSPlus gps;
    int humidityValue = 0;
    int sensorValue = 0;
    int NivelLuz = 0;
    int NivelPh = 0;
    int media = 0;
    float voltage;
    int pHValue;
    int channelValue = 0;
    int pHArray[ArrayLenght];
    int pHArrayIndex = 0;
    double Temperatura = 0;
    float m;
    float b;
    double Vo;

  public:
    
    const int power_pin = 5;
    int medirSal();
    float medirPh(int);
    float medirTemp(int);
    int medirLuz(int);
    int medirH(int);
    Adafruit_ADS1115 ads1015;

};

int Sparkfun::medirH(int channelValue)
{
  //Leemos del canal channelValue a través del ADS1115
  sensorValue = ads1015.readADC_SingleEnded(channelValue);
  //mapeamos el valor leido para un porcentaje entre 0 a 100
  humidityValue = map(sensorValue, 22484 , 10100, 0, 100);
  if (humidityValue >= 100)
  {
    humidityValue = 100;
  }
  if (humidityValue <= 0)
  {
    humidityValue = 0;
  }
  return (humidityValue);
};

float averageSample(int lista[ArrayLenght],int channelValue)
{
  Sparkfun Fun;
  float media;
  for (int i = 0; i <= (ArrayLenght - 1); i++)
  {
    lista[i] = Fun.ads1015.readADC_SingleEnded(channelValue);
    media = (lista[i] + media);
  }
  media = media / ArrayLenght;
  return (media);
};

float Sparkfun::medirPh(int channelValue)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();

  samplingTime = millis();
  printTime = millis();

  if (millis() - samplingTime > samplingInterval)
  {
    if (pHArrayIndex == ArrayLenght)
    {
      pHArrayIndex = 0;
    }
    voltage = averageSample(pHArray,3) * 4.096 / 32767;
    pHValue = 3.5 * voltage + Offset;
    samplingTime = millis();
    Serial.print("Voltage:");
    Serial.print(voltage);
    Serial.print(" pH Value:");
    Serial.println(pHValue);
  }
  if (millis() - printTime > printInterval)
  {
    Serial.print("Voltage:");
    Serial.print(voltage, 2);
    Serial.print(" pH Value:");
    Serial.println(pHValue, 2);
    printTime = millis();
  }
  //  if(pHValue>=6.51)
  //  {
  //    pHValue=7;
  //  }
  return (pHValue);
};

int Sparkfun::medirLuz(int channelValue)
{
  float LecturaLuz = ads1015.readADC_SingleEnded(channelValue);
  if (LecturaLuz >= 0 && LecturaLuz <= 300)
  {
    NivelLuz = 0;
  }
  if (LecturaLuz >= 301 && LecturaLuz <= 600)
  {
    NivelLuz = 1;
  }
  if (LecturaLuz >= 601 && LecturaLuz <= 10000)
  {
    NivelLuz = 2;
  }
  if (LecturaLuz >= 10001 && LecturaLuz < 50000)
  {
    NivelLuz = 3;
  }
  return (NivelLuz);
};

int Sparkfun::medirSal()
{
  int16_t adc0;
  digitalWrite(power_pin, HIGH);
  delay(100);

  adc0 = analogRead(A0);
  digitalWrite(power_pin, LOW);
  delay(100);
  // mapeamos el valor leido para un porcentaje entre 0 a 100
  int Sal = map(adc0, 540, 910, 0, 100);
  // limitamos los valores entre 0 y 100 para minimizar errores
  if (Sal >= 100)
  {
    Sal = 100;
  }
  if (Sal <= 0)
  {
    Sal = 0;
  }
  return (Sal);
};
float Sparkfun::medirTemp(int channelValue)
{
  int16_t adc0 = ads1015.readADC_SingleEnded(channelValue);

  m = 33 * pow(10, -3);
  b = 0.95;
  Vo = (adc0 * 4.096 / 32767);
  Temperatura = ((Vo - b) / m);
  return (Temperatura);
};
