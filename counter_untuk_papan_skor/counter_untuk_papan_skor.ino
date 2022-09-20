#include <Wire.h>


//// RTC DS3231
//#include <RtcDS3231.h>
//RtcDS3231<TwoWire> Rtc(Wire);

// RTC 1307
#include <RtcDS1307.h>
RtcDS1307<TwoWire> Rtc(Wire);

#define menu 3
#define upR 4
#define downR 5
#define left 6
#define right 7
#define upL 8
#define downL 9



int count;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count);
  delay(1000);
}
