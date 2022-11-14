#include <SPI.h>
#include <DMD3.h>
#include <RtcDS3231.h>
#include <Wire.h>
#include "avr/pgmspace.h"
#include "EEPROM.h"
// #include "font/BigNumber.h"
#include "font/SystemFont5x7.h"
#include "font/Arial_bold_14.h"
#include "font/segment.h"

// #define FontBig BigNumber
#define FontSeg segment
#define FontSml SystemFont5x7
#define FontTxt Arial_bold_14

RtcDS3231<TwoWire> Rtc(Wire);
RtcDateTime now;
DMD3 DISPLAYs(2, 1);

byte select ;

int DWidth = DISPLAYs.width();
int DHight = DISPLAYs.height();

int jam, mnt, bln, tgl, thn;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Rtc.Begin();
  displays_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  time();
  run(select);
}

void run(byte s) {
  if (s == 0) {
    display_clock(500, 30);
    // DISPLAYs.clear();
  } else  {
    display_dateTime(1000, 5);
    
  }
}

void time() {
  now = Rtc.GetDateTime();
}

void displays_init() {
  DISPLAYs.setDoubleBuffer(true);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(scan);
  brightness(1);
  Tfont(2);
  DISPLAYs.clear();
  DISPLAYs.swapBuffers();
}

void scan() {
  DISPLAYs.refresh();
}

void brightness(int bright) {
  Timer1.pwm(9, 200);
}

void Tfont(byte x) {
  // if (x == 0) DISPLAYs.setFont(FontBig);
  if (x == 1) DISPLAYs.setFont(FontSeg);
  else if (x == 2) DISPLAYs.setFont(FontSml);
  else if (x == 3) DISPLAYs.setFont(FontTxt);
}