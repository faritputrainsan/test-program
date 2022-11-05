#include <SPI.h>
#include <DMD3.h>
#include <RtcDS3231.h>
#include <Wire.h>



RtcDS3231<TwoWire> Rtc(Wire);
DMD3 DISPLAYs(2, 1);


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

  Rtc.Begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void time(){
RtcDateTime now = Rtc.GetDateTime();
}

void display_clock(){

}

void display_text(){
  
}
