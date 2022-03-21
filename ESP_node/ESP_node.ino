#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";

const char* mqtt_server = "";


WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
 

}

void loop() {
  // put your main code here, to run repeatedly:

}

void init_WiFi(){
  delay (10);
  Serial.println();
  Serial.print("Conecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while(){
    delay(500);
    Serial.print(.);
  }

  Serial.println();
  Serial.print();
  Serial.println();
}

void ws_init(){
  
}
