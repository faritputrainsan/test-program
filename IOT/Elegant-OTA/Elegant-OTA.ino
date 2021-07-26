/*
  Rui Santos
  Complete project details
   - Arduino IDE: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-arduino/
   - VS Code: https://RandomNerdTutorials.com/esp8266-nodemcu-ota-over-the-air-vs-code/
     
  This sketch shows a Basic example from the AsyncElegantOTA library: ESP8266_Async_Demo
  https://github.com/ayushsharma82/AsyncElegantOTA
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <ESP8266WebServer.h>
#include <AsyncElegantOTA.h>

#ifndef APSSID
#define APSSID "Jam Control"
#define APPSK  "12345678"
#endif

const char *ssid = APSSID;
const char *pass = APPSK;

const char* ssidC = "XLGO-75C3";
const char* password = "46266172";

AsyncWebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  IPAddress ip(192,168,8,99);
  IPAddress gateway(192,168,8,1);
  IPAddress subnet(255,255,255,0);

  WiFi.config(ip,gateway,subnet);
  
  WiFi.begin(ssidC, password);
//  WiFi.softAP(ssid, pass);
//  IPAddress myIP = WiFi.softAPIP();
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//  Serial.println(myIP);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  AsyncElegantOTA.loop();
}
