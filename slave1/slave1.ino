#include <EEPROM.h>
#include <Wire.h>
#define rly 8
#define ctrl 2

char data, blotot;
String bt, almt;
char x;
String b;
String blutot;
char dchar [10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rly, OUTPUT);
  pinMode(ctrl, OUTPUT);
  digitalWrite(rly, HIGH);
  digitalWrite(ctrl, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tgle;
  if (Serial.available()) {
    char bcar;
    int idx = 0;

    bcar = Serial.peek();
    if ((bcar == 'T') or (bcar == 'L')) {
      while ((bcar != '\n') and (idx < 80))
      {
        if (Serial.available()) {
          bcar = (char)Serial.read();
          dchar [idx] = bcar;
          idx++;
        }
      }
      dchar [idx - 1] = '\0';
      if (dchar[0] == 'L')
      {
        blutot = String(dchar);
        if (blutot.substring(1, 3).equals("AT"))       {
          EEPROM.put(0, blutot.substring(3, blutot.length()).toFloat());
        }
        else if (blutot.substring(1, 3).equals("ON"))  {
          EEPROM.put(0, blutot.substring(3, blutot.length()).toFloat());
        }
      }
      else if (dchar[0] == 'T')
      {
        blutot = String(dchar);
        if (blutot.substring(1, 3).equals("AT"))       {
          
        }
        else if (blutot.substring(1, 3).equals("ON"))  {
          
        }
      }
    }
    else {
      //    display.clear();
      if (Serial.available()) {
        
      }
    }
    bt = Serial.readString();
    EEPROM.get(0, b);
    if (bt.substring(0, 4) == "SET=") {
      EEPROM.put(0, bt.substring(2, bt.length()));
    }
    else if (bt.substring(0, bt.length()) == b) {
      if (tgle = 0) {
        tgle = 1;
        digitalWrite(rly, LOW);
        digitalWrite(ctrl, HIGH);
        Serial.write("=on");
        delay(10);
        digitalWrite(ctrl, LOW);
      }
      else {
        tgle = 0;
        digitalWrite(rly, HIGH);
        digitalWrite(ctrl, HIGH);
        Serial.write("S1=of");
        delay(10);
        digitalWrite(ctrl, LOW);
      }
    }
    else if (bt.substring(0, bt.length()) == "ON") {
      digitalWrite(rly, LOW);
      digitalWrite(ctrl, HIGH);
      delay(10);
      digitalWrite(ctrl, LOW);
      tgle = 1;
    }
    else if (bt.substring(0, bt.length()) == "OFF") {

      digitalWrite(rly, HIGH);
      digitalWrite(ctrl, HIGH);
      delay(10);
      digitalWrite(ctrl, LOW);
      tgle = 0;
    }
  }
}
