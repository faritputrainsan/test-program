#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Wire.h>
#define rly 8
#define ctrl 2

char data, blotot;
String bt, almt;
char x;
String b;

int state = LOW;

SoftwareSerial serial(11, 10); //rx  tx

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(rly, OUTPUT);
  pinMode(ctrl, OUTPUT);
  digitalWrite(rly, HIGH);
  digitalWrite(ctrl, LOW);
}

void loop() {
  if (Serial.available()) {
    delay (100);
    bt = Serial.readString();
    Serial.println(bt);
    if (bt.substring(0, bt.length()) == "S5") {
      state = !state;
      if ( state == LOW) {
        digitalWrite(rly,  state);
        delay(10);
//        digitalWrite(ctrl, HIGH);
//        Serial.write("S6on");
//        delay(10);
//        digitalWrite(ctrl, LOW);
      }
      else {
        digitalWrite(rly,  state);
        delay(10);
//        digitalWrite(ctrl, HIGH);
//        Serial.write("S6of");
//        delay(10);
//        digitalWrite(ctrl, LOW);
      }
    }
    else if (bt.substring(0, bt.length()) == "S5ON") {
      state = LOW;
      digitalWrite(rly, state);
//      delay(10);
//      digitalWrite(ctrl, HIGH);
////      Serial.write("1ON");
//      delay(10);
//     digitalWrite(ctrl, LOW);
    }
    else if (bt.substring(0, bt.length()) == "S5OFF") {
      state = HIGH;
      digitalWrite(rly,  state);
//      delay(10);
//      digitalWrite(ctrl, HIGH);
////      Serial.write("1OFF");
//      delay(10);
//      digitalWrite(ctrl, LOW);
    }
    
    else if (bt.substring(0, bt.length()) == "ON") {
      state = LOW;
      digitalWrite(rly, state);
//      delay(10);
//      digitalWrite(ctrl, HIGH);
////      Serial.write("1ON");
//      delay(10);
//     digitalWrite(ctrl, LOW);
    }
    else if (bt.substring(0, bt.length()) == "OFF") {
      state = HIGH;
      digitalWrite(rly,  state);
//      delay(10);
//      digitalWrite(ctrl, HIGH);
////      Serial.write("1OFF");
//      delay(10);
//      digitalWrite(ctrl, LOW);
    }
  }

}
