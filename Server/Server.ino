#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "Device.h"

#ifndef STASSID
#define STASSID "Fibertel Thea 2.4 GHz."
#define STAPSK  "c413209720" //COMPLETAR CON PASSWORD FUERA DE GIT
#endif


ESP8266WebServer server(80);
const int led = 13;

const char *ssid = STASSID;
const char *password = STAPSK;

Device dev("televisor");
Key *k;

void handleRoot() {
  digitalWrite(led, 1);
  //server.send(200, "text/plain", "hello from esp8266!\r\n");
  server.send(
    200,
    "html",
    "<!DOCTYPE html><html><meta name=\"viewport\" content=\"width=device-width, initial-scale=2.0\"><body><h1>Clonador de controles remotos IR con WeMOS</h1><form action=\"/action_page.php\"> <label for=\"dispositivo\">Elija el dispositivo a controlar</label> <select name=\"dispositivo\" id=\"dispositivo\"> <option value=\"tv\">Television</option> <option value=\"ac\">Aire Acondicionado</option> <option value=\"proy\">Proyector</option> </select> <br><br> <input type=\"submit\" value=\"Submit\"></form><br><br><!--<button type=\"button\" onclick=\"alert('alerta!')\">Click Me!</button>--><div class=\"container\"> <ul style=\"list-style-type:none\"> <li> <button type=\"button\">Volumen +</button> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp <button type=\"button\">Canal +</button> </li> <br> <li> <button type=\"button\">Volumen - </button> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp <button type=\"button\">Canal -</button> </li> </ul></div> </body></html>"
  );
  digitalWrite(led, 0);
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
  digitalWrite(led, 0);
}

void initServer() {
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

  server.on("/", handleRoot);

/*
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
*/

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  
  Serial.begin(115200);
  
  //initServer();
}

void loop(void) {
  //server.handleClient();
  //MDNS.update();

  delay(1500);
  Serial.println("Attempting to acquire key data");

  k = dev.acquireKeyData();
  if (k) {
    Serial.print(k->getPropertyById(1));
  } else {
    Serial.println("Couldn't read key data");
  }

  Serial.println();

}
