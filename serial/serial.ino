#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial serial(11, 10); //rx  tx
int control = 2, led = 6;
int tombol = 7, t;

String bt;

void setup() {
  Serial.begin(9600);
  serial.begin(9600);
  pinMode(control, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(tombol, INPUT);
  digitalWrite(control, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  t = digitalRead(tombol);
  if (t == LOW) {
    ab();
    digitalWrite(control, HIGH);
    Serial.println("S0");
    serial.write("S0");
    delay(20);
    digitalWrite(control, LOW);
  }
  if (serial.available()) {
    bt = serial.readString();
    Serial.print(bt);
    if (bt.substring(0, bt.length()) == "S0=on") {
      digitalWrite(led, HIGH);
    }
    if (bt.substring(0, bt.length()) == "S0=off") {
      digitalWrite(led, LOW);
    }
  }
}
void ab() {
  delay (200);
  while (t == LOW) {
    t = digitalRead(tombol);
  }
}
