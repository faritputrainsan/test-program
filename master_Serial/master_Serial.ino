#include <SoftwareSerial.h>


SoftwareSerial serials(2,3);

byte pin_stat = A3;
String text ;


void setup() {

  Serial.begin(9600);
  serials.begin(9600);

  pinMode (pin_stat, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {

  if (Serial.available()){
    text = Serial.readString();
    delay(1000);
    digitalWrite(pin_stat,HIGH);
    delay(1000);
    serials.write(text.c_str());
      
  }
  // put your main code here, to run repeatedly:

}
