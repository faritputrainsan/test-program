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

#define WIDTH  256// panjang led matrix
#define HEIGHT 16 // tinggi led matrix

HUB08SPI display;

uint8_t displaybuf[WIDTH * HEIGHT / 8];
Buffer buff(displaybuf, WIDTH, 16);

#include "ronnAnimation.h"

void refresh() {
  display.scan();
}

String data_jadwal = "";

//char* Text = "ABCD";
//char* Text1 = "KLMN";
char prm[260];
char msg[100];
char text[200];
char text1[100];
char mosque_name[50];

const String name_mosque;
const int adds_mosque = 10;

String dates = "";
//String test_text = "Tes ini disini kenapa annoying bangeet epprom e";

void setup() {

  Serial.begin(9600);
  display.begin(displaybuf, WIDTH, HEIGHT);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(refresh);
  display.setBrightness(2000);
  buff.clear();
  //  EEPROM.get(adds_mosque, Text);

}


void loop() {
  // put your main code here, to run repeatedly:
  // runningText("Selamat datang disini");
  //  Serial.print(jdwlkonversi("804"));

  //  delay(5000);


  //  EEPROM.get(0,Text);

  //  Serial.println("this loop");
  //   Text;

  //  Serial.println(Text);
  //  StaticTxt(Text); delay(1000);
  //  Serial.println(Text);

  //  Serial.println(name_mosque);
  //  delay(5000);
  StaticTxt(1);
  to_jadwal(data_jadwal);


  //ronn.setFont(B_STD);
  // ronn.printText("Animation Demo",0,0);delay(500);
  // ronn.clearSlice_R(0,8,64,16);
}

void to_jadwal(String data) {
  String imsak = jdwlkonversi("804");
  String subuh = jdwlkonversi("100");
  String dhuhur = jdwlkonversi("360");
  String asar = jdwlkonversi("230");
  String maghrib  = jdwlkonversi("1000");
  String isya = jdwlkonversi("999");
  //  String imsak = jdwlkonversi(data.substring(0,1));
  //  String subuh = jdwlkonversi(data.substring(0,1));
  //  String dhuhur = jdwlkonversi(data.substring(0,1));
  //  String asar = jdwlkonversi(data.substring(0,1));
  //  String maghrib  = jdwlkonversi(data.substring(0,1));
  //  String isya = jdwlkonversi(data.substring(0,1));
  jadwal(imsak, subuh, dhuhur, asar, maghrib, isya);
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
