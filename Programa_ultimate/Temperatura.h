#ifndef TEMPERATURA_YA_INCLUIDO
#define TEMPERATURA_YA_INCLUIDO

class Temperatura
  {
    private:
      double Temperatura = 0;      
      float m;
      float b;
      double Vo;
      int channelValue;
    public:
      float medirTemp();
  };
#endif