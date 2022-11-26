/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp8266-nodemcu/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0x05, 0x68, 0x4E};

// Digital pin connected to the DHT sensor
#define BTNPIN D1

byte readPin;

bool button;
bool sts;

// Define variables to store DHT readings to be sent
float temperature;

//float humidity;

// Define variables to store incoming readings
float incomingTemp;

// Variable to store if sending data was successful
String success;

//Must match the receiver structure
typedef struct struct_recv_message {
  float temp;
  //  float hum;
} struct_recv_message;

//Structure example to send data
typedef struct struct_send_message {
  bool btn;
} struct_send_message;

// Create a struct_message called DHTReadings to hold sensor readings
struct_send_message btnReadings;

// Create a struct_message to hold incoming sensor readings
struct_recv_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
//  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
  //  Serial.println("Delivery success");
  }
  else {
  //  Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//  Serial.print("Bytes received: ");
//  Serial.println(len);
  incomingTemp = incomingReadings.temp;
  //  incomingHum = incomingReadings.hum;
}

void getReadings() {

  // read button

  readPin = digitalRead(BTNPIN);
  
  if (readPin == HIGH) {
    antiBounce();
    button = true;
    sts = true;
    Serial.println(button);
  }
  else {
    button = false;
  }
  btnReadings.btn = button;

  /////////////////!!!!!!!!!!!    this    !!!!!!!!!!!//////////////////
    esp_now_send(broadcastAddress, (uint8_t *) &btnReadings, sizeof(btnReadings));


  //Read Temperature
  //  temperature = dht.readTemperature();
  //Read temperature as Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  //  if (isnan(temperature)){
  //    Serial.println("Failed to read from DHT");
  //    temperature = 0.0;
  //  }
  //  humidity = dht.readHumidity();
  //  if (isnan(humidity)){
  //    Serial.println("Failed to read from DHT");
  //    humidity = 0.0;
  //  }
}

void printIncomingReadings() {
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Temperature: ");
  Serial.print(incomingTemp);
  Serial.println(" ºC");
  //  Serial.print("Humidity: ");
  //  Serial.print(incomingHum);
  //  Serial.println(" %");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  //  unsigned long currentMillis = millis();
  getReadings();
  if (incomingTemp && sts) {
  // save the last time you updated the DHT values
  // previousMillis = currentMillis;
  // Get DHT readings
  //Set values to send
  //  DHTReadings.hum = humidity;
  // Send message via ESP-NOW
    sts = false;
  // Print incoming readings
    printIncomingReadings();
  }
}

void antiBounce() {
  while (readPin) {
    readPin = digitalRead(BTNPIN);
    delay(100);
  }
}