#include <OneWire.h>
#include <SPI.h>
#include <DallasTemperature.h>
#include <LoRa.h>

#define ss D8
#define rst D0
#define dio0 D2

#define BAND 433E6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initLora();

  
}

void loop() {
  // put your main code here, to run repeatedly:
}

void initLora() {
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(BAND)) {
    Serial.println("Lora failed");
    delay(1000);
  }
  Serial.println("LoRa connect success");
}