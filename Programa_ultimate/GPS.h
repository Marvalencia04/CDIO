#ifndef GPS_YA_INCLUIDO
#define GPS_YA_INCLUIDO
#endif
#include "TinyGPSPlus.h"
TinyGPSPlus gps;

class GPS{
  
  public:
  void medir(){
      while (pins.available() > 0)
      gps.encode(pins.read());
      if (gps.location.isUpdated())
      {
        Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
        Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
      }
  }
}
