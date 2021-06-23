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

int d=4,s=5,c=6;

const byte ROWS = 8; //four rows
const byte COLS = 8; //four columns
//define the cymbols on the buttons of the keypads
int hexaKeys[ROWS][COLS] = {
  {0, 1, 2, 3, 4, 5, 6, 7},
  {8, 9, 1, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 2, 28, 29, 30, 31},
  {3, 33, 34, 35, 36, 37, 38, 39},
  {40, 41, 42, 43, 44, 45, 4, 8},
  {48, 49, 50, 51, 52, 53, 54, 55},
  {56, 57, 58, 59, 60, 61, 62, 63}
};
byte rowPins[ROWS] = {22, 23, 24, 25, 26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3, A4, A5, A6, A7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode (c,OUTPUT);
  pinMode (s,OUTPUT);
  pinMode (d,OUTPUT);
}

void loop() {
  String customKey = (String)customKeypad.getKey();

  if (customKey) {
    Serial.println('S'+(customKey));
  }
}
