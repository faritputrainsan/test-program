#include <Wire.h>

#include <SPI.h>  // include libraries
#include <LoRa.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ss 15   //GPIO 15
#define rst 16  //GPIO 16
#define dio0 4  //GPIO 4

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


byte Master_Node = 0xFF;
byte Node = 0xAA;
byte msgCount = 0;

String SenderNode = "";

unsigned long pm = 0;
unsigned int interval = 1500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LoRa.setPins(ss, rst, dio0);

  if (!LoRa.begin(433E6)) {
    Serial.print("Lora Failed to Connect");
    while (1)
      ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // unsigned long mil = millis();
  // if (mil - pm >= interval) {
  //   pm = mil;
  //   sendMessage("Ping", Master_Node, Node);
  // }
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outGoing, byte Mnode, byte otherNode) {
  LoRa.beginPacket();
  LoRa.write(otherNode);
  LoRa.write(Mnode);
  LoRa.write(msgCount);
  LoRa.write(outGoing.length());
  LoRa.print(outGoing);
  LoRa.endPacket();
  msgCount++;
}

void onReceive(int paketSize) {
  if (paketSize == 0) return;
  int recipient = LoRa.read();
  byte sender = LoRa.read();
  if (sender == 0xAA) SenderNode = "Node:";
  byte incomingMsgId = LoRa.read();
  byte incomingLength = LoRa.read();

  
}

