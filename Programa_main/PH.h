#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;




class Ph{
    private:
        #define Offset 7-6.25
        #define ArrayLenght 40 //numero de muestras
        int NivelPh = 0;
        
        #define samplingInterval 20
        
        #define printInterval 600
        int media = 0;
        static unsigned long samplingTime = millis();
          static unsigned long printTime = millis();
          static float voltage;
          int pHValue;
    public:
        float averageSample(int lista[ArrayLenght],int channelValue)
        {
          
          for (int i = 0; i <= (ArrayLenght - 1); i++)
          {
            lista[i]=ads1015.readADC_SingleEnded(channelValue);
            media = (lista[i] + media);
          }
          media = media / ArrayLenght;
          return (media);
        }
        
        float medir(int channelValue){
          samplingTime = millis();
          printTime = millis();
          
          if (millis() - samplingTime > samplingInterval)
          {
            //pHArray[pHArrayIndex++] = ads1015.readADC_SingleEnded(channelValue);
            if (pHArrayIndex == ArrayLenght)
            {
              pHArrayIndex = 0;
            } 
            voltage = averageSample(pHArray,channelValue)* 4.096 / 32767;
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
          return(pHValue);
        }
}
