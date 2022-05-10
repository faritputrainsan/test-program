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
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include "HUB08SPI.h"
#include "TimerOne.h"
#include "Buffer.h"

//#define WIDTH  256// panjang led matrix
#define WIDTH  64// panjang led matrix
#define HEIGHT 16 // tinggi led matrix

HUB08SPI display;

uint8_t displaybuf[WIDTH * HEIGHT / 8];
Buffer buff(displaybuf, WIDTH, 16);

#include "ronnAnimation.h"

void refresh() {
  display.scan();
}

int pin_interupt;

String mn_mosque;

//char* Text1 = "KLMN";


String text_250;


int text_add = 51;
int mn_add = 0;

//String dates = "";

  
void setup() {
  Serial.begin(115200);
  display.begin(displaybuf, WIDTH, HEIGHT);
  Timer1.initialize(250);
  Timer1.attachInterrupt(refresh);
  display.setBrightness(2000);
  buff.clear();
}

void loop() {
//  runningText("TEST HAHAHAHAH");
//    Serial.print(readeeps);
  //  delay(5000);
  //  EEPROM.get(0,Text);

  //  Serial.println("this loop");
  //   Text;

  //  Serial.println(Text);
  //  StaticTxt(Text); delay(1000);
  //  Serial.println(Text);
  //  Serial.println(name_mosque);
  //  delay(5000);
//  StaticTxt(1);
//  jadwal();


  //ronn.setFont(B_STD);
  // ronn.printText("Animation Demo",0,0);delay(500);
  // ronn.clearSlice_R(0,8,64,16);
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
