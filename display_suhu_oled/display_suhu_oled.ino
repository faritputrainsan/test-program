#include <Wire.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 0

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();



void setup() {
  // put your setup code here, to run once:
  mlx.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  }
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
   display.setTextSize(2);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(0,0);
   display.println("Temp:");
   display.setTextSize(2);
   display.println(mlx.readObjectTempC());
   display.display();
   delay (100);
   display.clearDisplay();
}
