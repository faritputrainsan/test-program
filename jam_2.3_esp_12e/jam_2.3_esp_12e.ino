#include <Wire.h>
#include <RtcDS3231.h>
#include <ESP8266WiFi.h>

RtcDS3231<TwoWire> Rtc(Wire);

#define clk 0
#define d   2
#define str 15

byte dataSeg[] = {0x01, 0xB7, 0xc2, 0x12, 0x34, 0x18, 0x08, 0xb3, 0x00, 0x10};

void setup() {
  // put your setup code here, to run once:

  Wire.begin(13, 12);

  Rtc.Begin();

  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);
  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
//  Rtc.SetSquareWavePin(DS3231SquareWaveClock_1Hz);
  Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);

}

void loop() {
  // put your main code here, to run repeatedly:
  const RtcDateTime now = Rtc.GetDateTime();

  int jam = now.Hour();
  int minute = now.Minute();

  digitalWrite(str, LOW);
  shiftOut(d, clk, MSBFIRST, dataSeg[minute % 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[minute / 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[jam % 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[jam / 10]);
  digitalWrite(str, HIGH);

}


void setting(){
  
}
