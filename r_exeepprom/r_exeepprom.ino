#include <Wire.h>

//1. Alamat = 0x57

#define ADD_I2C 0x57

#define input A3

byte r_input;


//#define pinSDA D5
//#define pinSCL D6

void setup() {

  Serial.begin(9600);
  Wire.begin();
  delay(100);

//  writeData(1, 12);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  r_input = digitalRead(input);
  
  if(r_input== LOW){
    Serial.println(readData(1));
    delay(1001);
  }
}

//char Ch_prm[250];
//
//void serialEvent() {
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
//
//
//
////  data = Serial.peek();
////  if (data == 'T') {
////    while (data != '\n' and (index <= 255)) {
////      if(Serial.available()){
////        data = (char) Serial.read();
////        Ch_prm[index] = data;
////        index ++;
////      }
////    }
////    Serial.print(data);
////  }
//}

void writetxt(unsigned int addres, String text) {
  //  String text;

  for (int i; i < text.length(); i++ ) {
    writeData(addres, text[i]);
    addres++;
  }
}


void writeData(unsigned int address, byte data) {

  Wire.beginTransmission(ADD_I2C);
  Wire.write((int)(address >> 8));   //MSB
  Wire.write((int)(address & 0xFF)); //LSB
  Wire.write(data);
  Serial.print("write Data  ");
  Serial.println(data);
  Wire.endTransmission();
  delay(5);
}

byte readData(byte address) {

  byte data ;
  Wire.beginTransmission(ADD_I2C);
  Wire.write((int)(address >> 8));   //MSB
  Wire.write((int)(address & 0xFF));  //LSB
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
