#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"
#include "ESP8266mDNS.h"
#include "ArduinoJson.h"
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "Pagina.h"
#include "control.h"
#include "protocols.h"

#include "IRac.h"
#include "IRtext.h"
#include "IRutils.h"

#define ACCESS_POINT 0    // Define si trabajar como AP o como station
#define DEBUG_TRAMAS 1    // Con Debug=1 se imprime informacion de las tramas enviadas

#ifndef STASSID
#if ACCESS_POINT
// En caso de trabajar como AP, define el nombre de la red WiFi y su contraseña
#define STASSID "WifiPlaca"
#define STAPSK  "123456789"

#else
// En caso de trabajar como estacion WiFi, define los datos de la red a conectarse
#define STASSID "Fibertel Thea 2.4 GHz."
#define STAPSK  "c413209720" //COMPLETAR CON PASSWORD FUERA DE GIT

#endif
#endif

#define IR_SEND_LED 12    // GPIO12 = D6, transmisor IR
#define IR_RECV_PIN 14    // GPIO14 = D5, receptor IR


const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);

bool receivingIR = false;

IRsend irsend(IR_SEND_LED);

// Parametros para recepcion de tramas
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 60;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%
IRrecv irrecv(IR_RECV_PIN, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results

// Controles definidos
#define N_DEVICES 5

Control TV_JVC("tv_jvc", RC5_Protocol);
Control TV_TCL("tv_tcl", Nikai_Protocol);
Control TV_Sony("tv_sony", Sony_Protocol);
Control Proyector("proyector", Epson_Protocol);
AC_Control Aire("aire", Coolix_Protocol);

Control *devices[N_DEVICES] = {&TV_JVC, &TV_TCL, &TV_Sony, &Proyector, &Aire};
// ---------------


/* Pagina principal */
void handleRoot() {
  server.send(200, "text/html", webpage);
}

/* Recibir comandos de dispositivos */
void handleCommand(){
    if (!receivingIR) {
        String postBody = server.arg("plain");
        Serial.println(postBody);
     
        DynamicJsonDocument doc(512);
        DeserializationError error = deserializeJson(doc, postBody);
        if (error) {
            // if the file didn't open, print an error:
            Serial.print(F("Error parsing JSON "));
            Serial.println(error.c_str());
     
            String msg = error.c_str();
     
            server.send(400, F("text/html"),
                    "Error in parsin json body! <br>" + msg);
     
        } else {
            JsonObject postObj = doc.as<JsonObject>();
     
            Serial.print(F("HTTP Method: "));
            Serial.println(server.method());
     
            if (server.method() == HTTP_POST) {
                if (postObj.containsKey("dispositivo") && postObj.containsKey("id")) {
     
                    Serial.println(F("done."));
     
                    String disp = postObj["dispositivo"];   // Dispositivo que se quiere controlar
                    function_t function = postObj["id"];    // Funcion que se quiere realizar
    
                    Serial.print("Dispositivo: "); Serial.println(disp);
                    Serial.print("Funcion: "); Serial.println(function);
    
                    // Busca el dispositivo en el array y llama a la funcion send
                    bool success = false;
                    for (int i = 0; i < N_DEVICES; i++) {
                      if (devices[i]->getName() == disp) {
                        success = devices[i]->send(function, irsend);
                        break;
                      }
                    }
    
                    if (success) {
                      Serial.println("Sent successfully");
                    } else {
                      Serial.println("Could not send");
                    }
    
                    
    #if DEBUG_TRAMAS
                    checkIRrecv();
    #endif
                    // Create the response
                    // To get the status of the result you can get the http status so
                    // this part can be unusefully
                    DynamicJsonDocument doc(512);
                    doc["status"] = "OK";
     
                    Serial.print(F("Stream..."));
                    String buf;
                    serializeJson(doc, buf);
     
                    server.send(201, F("application/json"), buf);
                    Serial.print(F("done."));
     
                }else {
                    DynamicJsonDocument doc(512);
                    doc["status"] = "KO";
                    doc["message"] = F("No data found, or incorrect!");
     
                    Serial.print(F("Stream..."));
                    String buf;
                    serializeJson(doc, buf);
     
                    server.send(400, F("application/json"), buf);
                    Serial.print(F("done."));
                }
            }
        }
    } // modo
}

void handleStatus(){
  DynamicJsonDocument doc = Aire.toJSON();

  Serial.print(F("Sending Status."));
  String buf;
  serializeJson(doc, buf);

  server.send(200, F("application/json"), buf);
  Serial.print(F("done."));
}

void handleMode() {
    receivingIR = !receivingIR;

    server.send(200, "text/plain", "");
    Serial.println("Changed mode.");
}

/* Pagina no encontrada */
void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


/*  Verifica si se ha recibido una trama IR con el receptor.
 *  En caso de que sí, se muestra el contenido a traves del monitor serie.
 */
void checkIRrecv() {
    if (irrecv.decode(&results)) {
        // Display a crude timestamp.
        uint32_t now = millis();
        Serial.printf(D_STR_TIMESTAMP " : %06u.%03u\n", now / 1000, now % 1000);
        
        // Check if we got an IR message that was to big for our capture buffer.
        if (results.overflow)
          Serial.printf(D_WARN_BUFFERFULL "\n", kCaptureBufferSize);
        
        // Display the library version the message was captured with.
        Serial.println(D_STR_LIBRARY "   : v" _IRREMOTEESP8266_VERSION_STR "\n");
        
        // Display the tolerance percentage if it has been change from the default.
        if (kTolerancePercentage != kTolerance)
          Serial.printf(D_STR_TOLERANCE " : %d%%\n", kTolerancePercentage);
        
        // Display the basic output of what we found.
        Serial.print(resultToHumanReadableBasic(&results));
        
        // Display any extra A/C info if we have it.
        String description = IRAcUtils::resultAcToString(&results);
        if (description.length()) Serial.println(D_STR_MESGDESC ": " + description);
        yield();  // Feed the WDT as the text output can take a while to print.
    }
}


void setup(void) {
  Serial.begin(115200);

#if ACCESS_POINT

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  char buffer[60];
  sprintf(buffer, "Network name: %s\nPassword: %s", ssid, password);
  Serial.println(buffer);
  
#else
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

#endif

  /* Servidor Web */
  server.on("/", handleRoot);
  server.on(F("/command"), HTTP_POST, handleCommand);
  server.on(F("/status"), HTTP_GET, handleStatus);
  server.on(F("/mode"), HTTP_GET, handleMode);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  /* ------------------ */

  /* Transmision - Recepcion IR */

  // Iniciar transmisor IR
  irsend.begin();
  Serial.println("IRsend started");

  // Iniciar receptor IR
  irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
  irrecv.enableIRIn();  // Start the receiver
  Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", IR_RECV_PIN);

  /* ------------------ */
}

void loop(void) {
    server.handleClient();
    if (receivingIR) {
        checkIRrecv();
    }
    MDNS.update();
}
