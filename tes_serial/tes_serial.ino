#include<SoftwareSerial.h>
//#include <avr/pgmspace.h>

SoftwareSerial serial(2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  serialEvent();

}

void serialEvent() {
  if (serial.available() != 0) {
    String baca = serial.readString();
//    Serial.println(serial.readString());
    Serial.println("OK");
    Serial.println(baca);
    
    if (baca.substring(0, baca.length()) == "TES") {
      Serial.println("OKE");
    }
  }
}
