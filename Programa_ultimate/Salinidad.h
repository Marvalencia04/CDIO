#ifndef SALINIDAD_YA_INCLUIDO
#define SALINIDAD_YA_INCLUIDO

class Salinidad
{
public:
// El circuito de salinidad se conecta al puerto 5
#define power_pin 5
  int Sal = 0;
  // diseñamos el metodo de medir salinidad
  int medirSal();
};
#endif