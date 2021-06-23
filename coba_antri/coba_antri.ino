#include<Wire.h>
#include <Keypad.h>
#include<EEPROM.h>
byte counter;
const byte ROWS = 3; //four rows
const byte COLS = 3; //eight columns

char baca1, baca;
String bac;
char hexaKeys[ROWS][COLS] = {
  '0', '1', '2',
  '3', '4', '5',
  '6', '7', '8'
};
int timeup = 3000;
unsigned long tup = 0;

unsigned long cm ;

byte rowPins[ROWS] = {5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
char customKey;

bool state;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);

  for (int i; i < 255 ; i++) {
    EEPROM.put(i, 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  cm = millis();
  key();
}

void key() {
  customKey = customKeypad.getKey();
  if ( cm - tup >= timeup) {
    antri();
  }
  if (customKey) {
    EEPROM.put(counter, customKey);
    Serial.print("tombol =");
    Serial.println(customKey);
    Serial.print("counter =");
    Serial.println(counter);
    EEPROM.get(counter, baca);
    Serial.print("data di EEPROM =");
    Serial.println(baca);
    counter ++;
    state = true;
    tup = cm;
  }
}
int i ;

void antri() {
  if (i <= counter && state == true) {
    state = false;
    EEPROM.get(i, baca1);
    Serial.print("data dikirim =");
    Serial.println(baca1);
    delay (100);
  }
  else if (i >= counter){
    Serial.print("reset conter dan status");
    for (int b; b < counter; b++){
      EEPROM.put(i, 0);
    }
    state = false;
    counter = 0;
    i = 0;
  }
  tunggu();
}

void tunggu() {
  if (Serial.available()) {
    bac = Serial.readString();
    i++;
    Serial.print("serial dari komputer ");
    Serial.println(bac);
    Serial.print("alamat i=");
    Serial.println(i);
    state = true;
  }
}
