#ifndef PH_YA_INCLUIDO
#define PH_YA_INCLUIDO

class Ph{
    private:
        #define Offset 7-6.25
        #define ArrayLenght 40 //numero de muestras
        #define samplingInterval 20
        #define printInterval 600
        int NivelPh = 0;
        int media = 0;
        static float voltage;
        int pHValue;
        int channelValue=0;
        int pHArray[ArrayLenght];
        int pHArrayIndex=0;
    public:
        float averageSample(int[]);
        
        float medirPh();

};
#endif