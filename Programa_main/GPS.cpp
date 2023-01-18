#include "GPS.h"

  void GPS::medir(){
     while (pins.available() > 0)
      gps.encode(pins.read());
      if (gps.location.isUpdated())
      {
        Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
        Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
      }
  }
