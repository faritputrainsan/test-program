#include <Wire.h>

//1. Alamat = 0x57

#define ADD_I2C 0x57

int input = 9;
byte r_input;

String textData = "Test external eeprom";

//#define pinSDA D5
//#define pinSCL D6

void setup() {

  Serial.begin(9600);
  Wire.begin();
  delay(100);

  pinMode (input, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  r_input = digitalRead(input);

  if (r_input == LOW) {
    writeData(1, random(0,100));
    
//    Serial.println(readData(1));
    delay(500);
  }
}

char Ch_prm[250];

void serialEvent() {
  //  char data;
  //  int index = 0;
  //  String textSerial;
  //  if(Serial.available()){
  //    textSerial = Serial.readString();
  //
  //  }
  //  if (textSerial.substring(0,1) == "T"){
  //   writetxt(0, textSerial);
  //  }
}

void writetxt(unsigned int addres, String text) {
  //  String text;

  for (int i; i < text.length(); i++ ) {
    writeData(addres, text[i]);
    addres++;
    delay(2);
  }
  writeData(addres, '\n');
  delay(5);

}


void writeData(unsigned int address, int data) {

  wireTransmission(address);
  Wire.write(data);
  Serial.print("write Data  ");
  Serial.println(data);
  Wire.endTransmission();
  delay(5);
}

void  wireTransmission(unsigned int address) {
  Wire.beginTransmission(ADD_I2C);
  Wire.write((int)(address >> 8));   //MSB
  Wire.write((int)(address & 0xFF)); //LSB
}

byte readData(unsigned int address) {

  byte data ;
  wireTransmission(address);
  Wire.endTransmission();
  Wire.requestFrom(ADD_I2C, 1);
  delay(5);
  if (Wire.available()) {
    Serial.print("read data : ");
    data = Wire.read();
    Serial.println(data);
    delay(5);
  }
  return data;
}
