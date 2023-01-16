#ifndef GPS_YA_INCLUIDO
#define GPS_YA_INCLUIDO

#include <ESP8266WiFi.h>

class wifi{
  private:
  int numFields;
  public:
  void enviardatos(int,int,float,float,int);
};
#endif