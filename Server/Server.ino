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

#define ACCESS_POINT 0
#define DEBUG_TRAMAS 1

#ifndef STASSID
#if ACCESS_POINT

#define STASSID "WifiPlaca"
#define STAPSK  "123456789"

#else

#define STASSID "Entrerios.net 8457"
#define STAPSK  "66977989" //COMPLETAR CON PASSWORD FUERA DE GIT

#endif
#endif

#define IR_SEND_LED 12    // GPIO12 = D6
#define IR_RECV_PIN 14    // GPIO14 = D5

#if DEBUG_TRAMAS
const uint32_t kBaudRate = 115200;
const uint16_t kCaptureBufferSize = 1024;
const uint8_t kTimeout = 60;
const uint16_t kMinUnknownSize = 12;
const uint8_t kTolerancePercentage = kTolerance;  // kTolerance is normally 25%
IRrecv irrecv(IR_RECV_PIN, kCaptureBufferSize, kTimeout, true);
decode_results results;  // Somewhere to store the results
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

//IPAddress apIP(192, 168, 0, 110); // Defining a static IP address: local & gateway
                                // Default IP in AP mode is 192.168.4.1

//IPAddress apIP(192, 168, 1, 19);
ESP8266WebServer server(80);

IRsend irsend(IR_SEND_LED);

Control TVDormitorioAlan("tv_dormitorio_alan", RC5, rc5_functions);
Control TVLucho("tv_lucho", NIKAI, nikai_functions);
Control Proyector("proyector", EPSON, epson_functions);

const int led = 13;

void handleRoot() {
  server.send(200, "text/html", webpage);
}


void handleCommand(){
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
 
                // Here store data or doing operation
 
                String disp = postObj["dispositivo"];
                function_t function = postObj["id"];

                Serial.println(disp);
                Serial.println(function);
                uint64_t code;
                
                if (disp == "tv_dormitorio_alan") {
                  if (TVDormitorioAlan.send(function, irsend)) {
                    Serial.println("Sent successfully."); 
                  } else {
                    Serial.println("Couldn't send");
                  }

                } else if (disp == "tv_lucho") {
                  if (TVLucho.send(function, irsend)) {
                    Serial.println("Sent successfully."); 
                  } else {
                    Serial.println("Couldn't send");
                  }
                
                } else if (disp == "proyector") {
                  if (Proyector.send(function, irsend)) {
                    Serial.println("Sent successfully."); 
                  } else {
                    Serial.println("Couldn't send");
                  }
                }
                
#if DEBUG_TRAMAS
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
}

void handleNotFound() {
  digitalWrite(led, 1);
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


  server.on("/", handleRoot);
  
  server.on(F("/command"), HTTP_POST, handleCommand);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  irsend.begin();
  Serial.println("IRsend started");

  Serial.printf("\n" D_STR_IRRECVDUMP_STARTUP "\n", IR_RECV_PIN);

#if DECODE_HASH
  // Ignore messages with less than minimum on or off pulses.
  irrecv.setUnknownThreshold(kMinUnknownSize);
#endif  // DECODE_HASH
  irrecv.setTolerance(kTolerancePercentage);  // Override the default tolerance.
  irrecv.enableIRIn();  // Start the receiver
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
