// #include <OneWire.h>
#include <SPI.h>
// #include <DallasTemperature.h>
#include <LoRa.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define ss D8
#define rst D0
#define dio0 D2

#define BAND 433120000

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

Adafruit_SSD1306 displays(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// OneWire oneWire(DSpin);
// DallasTemperature Sensors(&oneWire);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(D4, D3);
  initOLED();
  initLora();
  LoRa.onReceive(receive);
  LoRa.receive();
  // initSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  // float temp = 1209;

  // char buff[8];

  // displays.clearDisplay();
  // displays.setTextColor(WHITE);
  // displays.setCursor(0, 16);
  // displays.setTextSize(2);
  // displays.print(temp);
  // displays.display();

  // LoRa.beginPacket();
  // LoRa.print(temp);
  // LoRa.endPacket();
  //   delay(3000);
}

void initLora() {
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(BAND)) {
    Serial.println("Lora failed");
    delay(1000);
  }
  Serial.println("LoRa connect success");
}

void initOLED() {
  while (!displays.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED failed");
    delay(1000);
  }
  displays.clearDisplay();
  displays.setTextColor(WHITE);
  displays.setCursor(0, 0);
  displays.setTextSize(2);
  displays.print(F("OK"));
  displays.display();
}

// void initSensor() {
//   Sensors.begin();
// }

// float readSensor() {
//   Sensors.requestTemperatures();
//   float tempC = Sensors.getTempCByIndex(0);
//   return tempC;
// }

void sendLoRa() {
}

void receive(int packetSize) {
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }
  Serial.print(" with RSSI: ");
  Serial.println(LoRa.packetRssi());
}
