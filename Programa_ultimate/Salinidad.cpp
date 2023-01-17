#include "Salinidad.h"
#include "Sparkfun.h"
Sparkfun FunS;
// diseñamos el metodo de medir salinidad
int Salinidad::medirSal()
{
    int16_t adc0;
    digitalWrite(FunS.power_pin, HIGH);
    delay(100);

    adc0 = analogRead(A0);
    digitalWrite(FunS.power_pin, LOW);
    delay(100);
    // mapeamos el valor leido para un porcentaje entre 0 a 100
    Sal = map(adc0, 540, 910, 0, 100);
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
}
