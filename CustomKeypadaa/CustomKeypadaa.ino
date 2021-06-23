/* @file CustomKeypad.pde
  || @version 1.0
  || @author Alexander Brevig
  || @contact alexanderbrevig@gmail.com
  ||
  || @description
  || | Demonstrates changing the keypad size and key values.
  || #
*/
#include <Keypad.h>

#define l  6
#define d  4
#define c  5


int control = 2;
int ic1;
const byte ROWS = 2; //four rows
const byte COLS = 2; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0', '1'},
  {'2', '3'}
};
byte rowPins[ROWS] = {A0, A1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {29, 28}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(control, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    switch (customKey) {
      //ic1
      case '0':
        digitalWrite(control, HIGH);
        Serial.write("S0");
        ic1 + 1;
        digitalWrite(control, LOW);
        break;
      case '1':
        digitalWrite(control, HIGH);
        Serial.write("S1");
        ic1 + 2;
        digitalWrite(control, LOW);
        break;
      case '2':
        digitalWrite(control, HIGH);
        Serial.write("S2");
        ic1 + 4;
        digitalWrite(control, LOW);
        break;

      case '3':
        digitalWrite(control, HIGH);
        Serial.write("S3");
        ic1 + 8;
        digitalWrite(control, LOW);
        break;
    }
  }
  digitalWrite(l, LOW);

  shiftOut(d, c, MSBFIRST, 0XF0);
  //  shiftOut(d, c, MSBFIRST, ic2);
  //  shiftOut(d, c, MSBFIRST, ic3);
  //  shiftOut(d, c, MSBFIRST, ic4);
  //  shiftOut(d, c, MSBFIRST, ic5);
  //  shiftOut(d, c, MSBFIRST, ic6);
  //  shiftOut(d, c, MSBFIRST, ic7);
  //  shiftOut(d, c, MSBFIRST, ic8);

  digitalWrite(l, HIGH);
}
