#include <SoftwareSerial.h>


SoftwareSerial serials(2,3);
byte pin_input = 9;

byte baca;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serials.begin(9600);

  pinMode(pin_input, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  baca = digitalRead(pin_input);
  if (baca == LOW) {
    Serial.write("TES TExt \n bla bla bla");
    delay (5000);
  }


}
