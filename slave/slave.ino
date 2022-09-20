#include <EEPROM.h>
#include <Wire.h>
#define rly 8
#define ctrl 2

char data, blotot;
String bt, almt;
char x;
String b;
int a;
int state = 1;
int tgle = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rly, OUTPUT);
  pinMode(ctrl, OUTPUT);
   a = state;
  digitalWrite(rly, HIGH);
  digitalWrite(ctrl, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available()) {
    bt = Serial.readString();
    EEPROM.get(0, b);
    if (bt.substring(0, 4) == "SET=") {
      EEPROM.put(0, bt.substring(2, bt.length()));
    }
   if (bt.substring(0, bt.length()) == "S0") {
      
      state != a ;
      
      digitalWrite(rly,  );
      digitalWrite(ctrl, HIGH);
//      Serial.write("S0=on");
      delay(10);
      digitalWrite(ctrl, LOW);
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
