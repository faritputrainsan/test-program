#include <Wire.h>

//1. Alamat = 0x57

#define ADD_I2C 0x57

#define pinSDA D5
#define pinSCL D6

void setup() {

  Serial.begin(9600);
  Wire.begin(pinSDA, pinSCL);
  delay(100);
  writeData(1, 12);
  Serial.println(readData( 1));
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent() {
  char data;
  int index = 0;

  data = Serial.peek();

  if (data == 'T') {
    while (data != '\n' and (index <= 255)) {
      if(Serial.available()){
        data = '1';
      }
    }
    Serial.print(data);
  }




}

void writeData(byte address, byte data) {

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
