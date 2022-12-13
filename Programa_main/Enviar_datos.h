#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads1015;

class Enviar_datos{

    public:
    
        void Enviar(int Humedad,int Sal,float Temperatura,int Ph) {
        
          String data[ NUM_FIELDS_TO_SEND + 1];  // Podemos enviar hasta 8 datos
          data[ 1 ] = String(Humedad); //Escribimos el dato 1. Recuerda actualizar numFields
        #ifdef PRINT_DEBUG_MESSAGES
          Serial.print( "Porcentaje de humedad = " );
          Serial.print( data[ 1 ] );
          Serial.println("%");
        #endif
        
          data[ 2 ] = String(Sal); //Escribimos el dato 2. Recuerda actualizar numFields
        #ifdef PRINT_DEBUG_MESSAGES
          Serial.print( "Porcentaje de sal = " );
          Serial.print( data[ 2 ] );
          Serial.println("%");
        #endif
          data[ 3 ] = String(Temperatura); //Escribimos el dato 3. Recuerda actualizar numFields
        #ifdef PRINT_DEBUG_MESSAGES
          Serial.print( "Nivel de temperatura(en grados centigrados): " );
          Serial.print( data[ 3 ] );
          Serial.println("º");
        #endif
        
          data[ 4 ] = String(Ph); //Escribimos el dato 4. Recuerda actualizar numFields
        #ifdef PRINT_DEBUG_MESSAGES
          Serial.print( "Nivel de Ph = " );
          Serial.println( data[ 4 ] );
        #endif
        
        
          //Selecciona si quieres enviar con GET(ThingSpeak o Dweet) o con POST(ThingSpeak)
          //HTTPPost( data, NUM_FIELDS_TO_SEND );
          HTTPGet( data, NUM_FIELDS_TO_SEND );
        
          //Selecciona si quieres un retardo de 15seg para hacer pruebas o dormir el SparkFun
          delay( 1500 );
          //Serial.print( "Goodnight" );
          //ESP.deepSleep( sleepTimeSeconds * 1000000 );
        }
}
