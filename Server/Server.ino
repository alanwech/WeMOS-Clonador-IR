#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266WebServer.h"
#include "ESP8266mDNS.h"
#include "ArduinoJson.h"
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "Pagina.h"
#include "controls.h"

#ifndef STASSID
#define STASSID "WifiPlaca"
#define STAPSK  "123456789" //COMPLETAR CON PASSWORD FUERA DE GIT
#endif

#define IR_SEND_LED 12    // GPIO12 = D6


const char* ssid = STASSID;
const char* password = STAPSK;

//IPAddress apIP(192, 168, 0, 110); // Defining a static IP address: local & gateway
                                // Default IP in AP mode is 192.168.4.1

//IPAddress apIP(192, 168, 1, 19);
ESP8266WebServer server(80);

IRsend irsend(IR_SEND_LED);
control_t TVDormitorioAlan = {"tv_dormitorio_alan", RC5, rc5_functions};
control_t TVLucho = {"tv_lucho", NIKAI, nikai_functions };
control_t Proyector = {"proyector", EPSON, epson_functions};

const int led = 13;

void handleRoot() {
  server.send(200, "text/html", webpage);
}

// Searches for code
uint64_t getCode(control_t *control, function_t *function) {
  uint64_t code = 0;
  uint32_t size = sizeof(*(control->functions));
  for (uint32_t i = 0; i < size; i++) {
    if (*function == control->functions[i].function) {
      code = control->functions[i].code;
      break;
    }  
  }
  return code;
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
                  code = getCode(&TVDormitorioAlan, &function);
                  //uint64_t code = 0xC;
                  if (code != 0) {
                    irsend.send(RC5, code, 12);
                  }

                } else if (disp == "tv_lucho") {
                  code = getCode(&TVLucho, &function);
                  if (code != 0) {
                    irsend.send(NIKAI, code, 24);
                  }
                
                } else if (disp == "proyector") {
                  code = getCode(&Proyector, &function);
                  if (code != 0) {
                    irsend.send(EPSON, code, 32);
                  }
                }


                if (code != 0) {
                  Serial.print("Sending function id ");
                  Serial.println(function);
                } else {
                  Serial.println("Code not found for action requested");  
                }
                 
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

  /*
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
  */
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
  
  server.on("/", handleRoot);
  
  server.on(F("/command"), HTTP_POST, handleCommand);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  irsend.begin();
  Serial.println("IRsend started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
