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
        float averageSample(int,int);
        float medir(int);
          
};
