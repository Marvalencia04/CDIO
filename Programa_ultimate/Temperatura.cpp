#include "Temperatura.h"
#include "Sparkfun.h"
Sparkfun FunT;
float Temperatura::medirTemp()
{
    int16_t adc0 = FunT.ads1015.readADC_SingleEnded(channelValue);

    m = 33 * pow(10, -3);
    b = 0.95;
    Vo = (adc0 * 4.096 / 32767);
    Temperatura = ((Vo - b) / m);
    return (Temperatura);
}