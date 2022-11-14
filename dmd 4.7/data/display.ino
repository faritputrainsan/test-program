#include <SPI.h>
#include <DMD3.h>
#include <RtcDS3231.h>
#include <Wire.h>
#include "avr/pgmspace.h"
#include "EEPROM.h"
#include "font/BigNumber.h"
#include "font/SystemFont5x7.h"


RtcDS3231<TwoWire> Rtc(Wire);
DMD3 DISPLAYs(2, 1);

int DWidth = DISPLAYs.width();
int DHight = DISPLAYs.height();


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

void speed(unsigned int spd){
    
}

void scan(){
DISPLAYs.refresh();
}
