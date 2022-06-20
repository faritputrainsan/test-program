/****************************
  HUB08 (matrix led) to ARDUINO pin connection
   LA / A    -> Digital Pin 4
   LB / B    -> Digital Pin 5
   LC / C    -> Digital Pin 6
   LD / D    -> Digital Pin 7
   S / CLK   -> Digital Pin 13
   R1 / R    -> Digital Pin 11
   OE / EN   -> Digital Pin 3
   L / LAT / STB -> Digital Pin 2
******************************/

#include <SPI.h>
#include <Wire.h>
#include <I2C_eeprom.h>
#include <avr/pgmspace.h>
#include "HUB08SPI.h"
#include "TimerOne.h"
#include "Buffer.h"

//#define WIDTH  256// panjang led matrix
#define WIDTH  256// panjang led matrix
#define HEIGHT 16 // tinggi led matrix

#define ADD_I2C 0x57

I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

int len_mosName = 60;
int lenText = 300;

int mosName_add = 0;
int Text_add = 61;

String mosName;
String Texts;

String imsak ;
String subuh ;
String dhuhur ;
String asar ;
String maghrib ;
String isya ;

HUB08SPI display;

uint8_t displaybuf[WIDTH * HEIGHT / 8];
Buffer buff(displaybuf, WIDTH, 16);

#include "ronnAnimation.h"

void refresh() {
  display.scan();
}

void setup() {
  Serial.begin(9600);
  eeprom.begin();
  display.begin(displaybuf, WIDTH, HEIGHT);
  Timer1.initialize(250);

  Timer1.attachInterrupt(refresh);
  display.setBrightness(2000);
  buff.clear();

  while (1) {
    //    ping();
    if (Serial.available()) {
      //      serial();
    }
    delay(100);
    //    mosName = text_read(len_mosName, mosName_add);
    delay (100);
    Texts = text_read(lenText, Text_add);
    Serial.println(Texts);
    delay(100);
    break;
  }
}

void loop() {

  runningText(Texts);
  //  jadwal();
  //  runningText(mosName);
}

String jdwlkonversi(String data) {

  int kon_jam;
  int kon_mnt;

  String str;
  String str_jam;
  String str_mnt;

  kon_jam = data.toInt() / 60;
  kon_mnt = data.toInt() % 60;

  if (kon_jam < 10) {
    str_jam = "0" + String(kon_jam);
  } else {
    str_jam = String(kon_jam);
  }
  if (kon_mnt < 10) {
    str_mnt = "0" + String(kon_mnt);
  } else {
    str_mnt = String(kon_mnt);
  }
  str = str_jam + ":" + str_mnt;
  return (str);
}
