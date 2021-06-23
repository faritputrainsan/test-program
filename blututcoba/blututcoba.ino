#include<Wire.h>
#include<EEPROM.h>
#include<SoftwareSerial.h>
String blut;
SoftwareSerial Ser(3, 30); // rx , tx

#define l  5
#define d  4
#define c  6

#define x  2

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Ser.begin(9600);
  pinMode(l, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(x, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(l, LOW);
  

digitalWrite(x, HIGH);
  if (Ser.available()) {
    blut = Ser.readString();


    if (blut.substring (0, blut.length()) == "sync") {

    }
    else if (blut.substring (0, blut.length()) == "offall") {
      shiftOut(d, c, MSBFIRST, 0xff);
      shiftOut(d, c, MSBFIRST, 0xff);
      shiftOut(d, c, MSBFIRST, 0xff);
      shiftOut(d, c, MSBFIRST, 0xff);
    }
    else if (blut.substring (0, blut.length()) == "onall") {
      shiftOut(d, c, MSBFIRST, 0x00);
      shiftOut(d, c, MSBFIRST, 0x00);
      shiftOut(d, c, MSBFIRST, 0x00);
      shiftOut(d, c, MSBFIRST, 0x00);
    }
    else if (blut.substring (0, blut.length()) == "B2on") {
      //     x41 = x4 = true;
    }
    else if (blut.substring (0, blut.length()) == "B2off") {
      //      x41 = x4 = false;
    }
    else if (blut.substring (0, blut.length()) == "B3on") {

    }
    else if (blut.substring (0, blut.length()) == "B3off") {

    }
    else if (blut.substring (0, blut.length()) == "B4on") {

    }
    else if (blut.substring (0, blut.length()) == "B4off") {

    }
    else if (blut.substring (0, blut.length()) == "B5on") {

    }
    else if (blut.substring (0, blut.length()) == "B5off") {

    }
  }
  digitalWrite(l, HIGH);
  delay(1000);
  digitalWrite(x, LOW);
  delay(1000);
  
  }
