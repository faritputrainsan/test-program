#include <SoftwareSerial.h>
#include <Wire.h>
#include <Keypad.h>

#define l  5
#define d  4
#define c  6

int control = 8;
byte baca, bc;
int ic1;
SoftwareSerial serial(10, 11); //rx  tx

const byte ROWS = 2; //four rows
const byte COLS = 2; //four columns

char hexaKeys[ROWS][COLS] = {
  {'0', '1'},
  {'2', '3'},
  
};

byte rowPins[ROWS] = {7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial.begin(9600);
  pinMode(control, OUTPUT);
  digitalWrite(control, LOW);
  pinMode(l, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();

  if (customKey) {

    switch (customKey) {
      //ic1
      case '0':
        serial.write("S0");
        Serial.write("S0");
        delay(10);
        break;
      case '1':
        digitalWrite(control, HIGH);
        serial.write("S1");
        Serial.write("S1");
        delay(10);
        digitalWrite(control, LOW);
        break;
      case '2':
        digitalWrite(control, HIGH);
        serial.write("S2");
        Serial.write("S2");
        delay(10);
        digitalWrite(control, LOW);
        break;
      case '3':
        digitalWrite(control, HIGH);
        serial.write("S3");
        Serial.write("S3");
        delay(10);
        digitalWrite(control, LOW);
        break;
    }
  }
}
byte tranfer(){
  digitalWrite(control, HIGH);
}
byte resc(){
  digitalWrite(control, LOW);
}
