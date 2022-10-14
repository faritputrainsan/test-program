#include <Wire.h>

//// RTC DS3231
//#include <RtcDS3231.h>
//RtcDS3231<TwoWire> Rtc(Wire);

// RTC 1307
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);

#define menu A0
#define upR A1
#define downR A2
#define left A3
#define right 7
#define upL 8
#define downL 9

int count;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode( menu, INPUT );
  pinMode( upR, INPUT );
  pinMode( downR, INPUT );
  pinMode( left, INPUT );
  pinMode( right, INPUT );
  pinMode( upL, INPUT );
  pinMode( downL, INPUT );
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count);
  delay(1000);
}
