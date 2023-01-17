// PH.cpp//
#include "PH.h"
#include "Sparkfun.h"
Sparkfun FunPh;
float Ph::averageSample(int lista[ArrayLenght])
{

    for (int i = 0; i <= (ArrayLenght - 1); i++)
    {
        lista[i] = FunPh.ads1015.readADC_SingleEnded(channelValue);
        media = (lista[i] + media);
    }
    media = media / ArrayLenght;
    return (media);
};

float Ph::medirPh()
{
    static unsigned long samplingTime = millis();
    static unsigned long printTime = millis();

    samplingTime = millis();
    printTime = millis();

    if (millis() - samplingTime > samplingInterval)
    {
        // pHArray[pHArrayIndex++] = ads1015.readADC_SingleEnded(channelValue);
        if (pHArrayIndex == ArrayLenght)
        {
            pHArrayIndex = 0;
        }
        voltage = averageSample(pHArray) * 4.096 / 32767;
        //    voltage=pHArray[pHArrayIndex++];
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
}
