#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DSPIN D1

OneWire oneWire(DSPIN);

#define lamp_pin 2

DallasTemperature Sensors(&oneWire);

float temperature;


const char* ssid = "XLGO-75C3";
const char* password = "46266172";

const char* mqtt_server = "192.168.8.6";

WiFiClient espClient;
PubSubClient client(espClient);

long Now = millis();
long Time = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(lamp_pin,OUTPUT);

  Sensors.begin();

  wifi_init();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  read_temp();
  delay(1000);

  if(!client.connected()){
    reconnect();
  }

  if (!client.loop()){
    client.connect("ESP8266Client");
  }
  static char temperatures[7];
  dtostrf(temperature,6,2,temperatures);
  client.publish("room/temperature",temperatures);

}

void wifi_init(){
  delay(10);
  WiFi.begin(ssid,password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while(WiFi.status()!= WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Wifi connected - ESP IP address: ");
  Serial.print(WiFi.localIP());
}

void read_temp(){
  Sensors.requestTemperatures();

  temperature = Sensors.getTempCByIndex(0);
  Serial.print ("temperature: ");
  Serial.print (temperature);
  Serial.println ("ºC");
}

void callback(String topic, byte* message, unsigned int length){
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  String messageTemp;

  for(int i = 0;i<length;i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  Serial.println();

  if(topic =="room/lamp"){
    Serial.print("Changing room lamp to ");
    if(messageTemp == "on"){
      digitalWrite(lamp_pin,HIGH);
      Serial.print("ON");
    }else if(messageTemp == "off"){
      digitalWrite(lamp_pin,LOW);
      Serial.print("OFF");
    }
  }
  Serial.println();
}

void reconnect(){
  while(!client.connected()){
    Serial.print("Attempting mqtt connection...");

    if(client.connect("ESP8266Client")){
      Serial.print("connected");
      client.subscribe("room/lamp");
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println( "try again in 5 seconds");
      delay(5000);
    }
    
  }
}
