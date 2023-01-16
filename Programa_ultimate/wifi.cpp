#include "Sparkfun.h"
#define NUM_FIELDS_TO_SEND 5
// Comentar/Descomentar para ver mensajes de depuracion en monitor serie y/o respuesta del HTTP server
#define PRINT_DEBUG_MESSAGES
// #define PRINT_HTTP_RESPONSE

// Comentar/Descomentar para conexion Fuera/Dentro de UPV
#define WiFi_CONNECTION_UPV

// Selecciona que servidor REST quieres utilizar entre ThingSpeak y Dweet
#define REST_SERVER_THINGSPEAK // Selecciona tu canal para ver los datos en la web (https://thingspeak.com/channels/1948866)
// #define REST_SERVER_DWEET //Selecciona tu canal para ver los datos en la web (http://dweet.io/follow/cdiocurso2022g06)

///////////////////////////////////////////////////////
/////////////// WiFi Definitions /////////////////////
//////////////////////////////////////////////////////

#ifdef WiFi_CONNECTION_UPV // Conexion UPV
const char WiFiSSID[] = "GTI1";
const char WiFiPSK[] = "1PV.arduino.Toledo";
#else // Conexion fuera de la UPV
const char WiFiSSID[] = "";
const char WiFiPSK[] = "MyPassWord";
#endif

///////////////////////////////////////////////////////
/////////////// SERVER Definitions /////////////////////
//////////////////////////////////////////////////////

#if defined(WiFi_CONNECTION_UPV) // Conexion UPV
const char Server_Host[] = "proxy.upv.es";
const int Server_HttpPort = 8080;
#elif defined(REST_SERVER_THINGSPEAK) // Conexion fuera de la UPV
const char Server_Host[] = "api.thingspeak.com";
const int Server_HttpPort = 80;
#else
const char Server_Host[] = "dweet.io";
const int Server_HttpPort = 80;
#endif

WiFiClient client;

///////////////////////////////////////////////////////
/////////////// HTTP REST Connection ////////////////
//////////////////////////////////////////////////////

#ifdef REST_SERVER_THINGSPEAK
const char Rest_Host[] = "api.thingspeak.com";
String MyWriteAPIKey = "OHLX8R0KJH6MAZJ8"; // Escribe la clave de tu canal ThingSpeak
#else
const char Rest_Host[] = "dweet.io";
String MyWriteAPIKey = "cdiocurso2022g06"; // Escribe la clave de tu canal Dweet
#endif
/////////////////////////////////////////////////////
/////////////// WiFi Connection ////////////////
//////////////////////////////////////////////////////

void connectWiFi()
{
  byte ledStatus = LOW;

#ifdef PRINT_DEBUG_MESSAGES
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
#endif

  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_PIN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println(".");
#endif
    delay(500);
  }
#ifdef PRINT_DEBUG_MESSAGES
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP()); // Print the IP address
#endif
}

/////////////////////////////////////////////////////
/////////////// HTTP POST  ThingSpeak////////////////
//////////////////////////////////////////////////////

void HTTPPost(String fieldData[], int numFields)
{

  // Esta funcion construye el string de datos a enviar a ThingSpeak mediante el metodo HTTP POST
  // La funcion envia "numFields" datos, del array fieldData.
  // Asegurate de ajustar numFields al número adecuado de datos que necesitas enviar y activa los campos en tu canal web

  if (client.connect(Server_Host, Server_HttpPort))
  {

    // Construimos el string de datos. Si tienes multiples campos asegurate de no pasarte de 1440 caracteres

    String PostData = "api_key=" + MyWriteAPIKey;
    for (int field = 1; field < (numFields + 1); field++)
    {
      PostData += "&field" + String(field) + "=" + fieldData[field];
    }

    // POST data via HTTP
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println("Connecting to ThingSpeak for update...");
    client.println("POST http://" + String(Rest_Host) + "/update HTTP/1.1");
    client.println("Host: " + String(Rest_Host));
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(PostData.length()));
    client.println();
    client.println(PostData);
    Serial.println();
    // Para ver la respuesta del servidor
#endif
#ifdef PRINT_HTTP_RESPONSE
    delay(500);
    Serial.println();
    while (client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println();
#endif
  }
}
////////////////////////////////////////////////////
/////////////// HTTP GET  ////////////////
//////////////////////////////////////////////////////
void HTTPGet(String fieldData[], int numFields) {

  // Esta funcion construye el string de datos a enviar a ThingSpeak o Dweet mediante el metodo HTTP GET
  // La funcion envia "numFields" datos, del array fieldData.
  // Asegurate de ajustar "numFields" al número adecuado de datos que necesitas enviar y activa los campos en tu canal web

  if (client.connect( Server_Host , Server_HttpPort )) {
#ifdef REST_SERVER_THINGSPEAK
    String PostData = "GET https://api.thingspeak.com/update?api_key=";
    PostData = PostData + MyWriteAPIKey ;
#else
    String PostData = "GET http://dweet.io/dweet/for/";
    PostData = PostData + MyWriteAPIKey + "?" ;
#endif

    for ( int field = 1; field < (numFields + 1); field++ ) {
      PostData += "&field" + String( field ) + "=" + fieldData[ field ];
    }


#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( "Connecting to Server for update..." );
#endif
    client.print(PostData);
    client.println(" HTTP/1.1");
    client.println("Host: " + String(Rest_Host));
    client.println("Connection: close");
    client.println();
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( PostData );
    Serial.println();
    //Para ver la respuesta del servidor
#ifdef PRINT_HTTP_RESPONSE
    delay(500);
    Serial.println();
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println();
#endif
#endif
  }
}
  void enviardatos(int NHumedad, int NSal, float NTemperatura, int NPh, int NLuz) {
    String data[ NUM_FIELDS_TO_SEND + 1];  // Podemos enviar hasta 8 datos
    data[ 1 ] = String(NHumedad); //Escribimos el dato 1. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print( "Porcentaje de humedad = " );
    Serial.print( data[ 1 ] );
    Serial.println("%");
#endif

    data[ 2 ] = String(NSal); //Escribimos el dato 2. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print( "Porcentaje de sal = " );
    Serial.print( data[ 2 ] );
    Serial.println("%");
#endif
    data[ 3 ] = String(NTemperatura); //Escribimos el dato 3. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print( "Nivel de temperatura(en grados centigrados): " );
    Serial.print( data[ 3 ] );
    Serial.println("º");
#endif

    data[ 4 ] = String(NPh); //Escribimos el dato 4. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print( "Nivel de Ph = " );
    Serial.println( data[ 4 ] );
#endif
    data[ 5 ] = String(NLuz); //Escribimos el dato 5. Recuerda actualizar numFields
#ifdef PRINT_DEBUG_MESSAGES
    Serial.print( "Nivel de luz = " );
    Serial.println( data[ 5 ] );
#endif


    //Selecciona si quieres enviar con GET(ThingSpeak o Dweet) o con POST(ThingSpeak)
    //HTTPPost( data, NUM_FIELDS_TO_SEND );
    HTTPGet( data, NUM_FIELDS_TO_SEND );

    //Selecciona si quieres un retardo de seg 2.5 para hacer pruebas o dormir el SparkFun
    delay( 2500 );
    //Serial.print( "Goodnight" );
    //ESP.deepSleep( sleepTimeSeconds * 1000000 );
  }
