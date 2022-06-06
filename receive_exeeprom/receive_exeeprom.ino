#include <Wire.h>
#include <I2C_eeprom.h>



//1. Alamat 24LC32 = 0x57

#define ADD_I2C 0x57

//Device identifier
I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

int input = 9;
byte r_input;

int lenText = 256;

String textSerial;

//#define pinSDA D5
//#define pinSCL D6

void setup() {

  Serial.begin(9600);

  eeprom.begin();
  if (!eeprom.isConnected()) {
    Serial.print("ERROR: can't find eeprom\nstoped");
    while (1);
  }
  //  Wire.begin();
  delay(100);

  pinMode (input, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  r_input = digitalRead(input);

  if (r_input == LOW) {
    //    writetxt(1, TEXT_ABC);

    //    Serial.println(readData(1));
    delay(500);

    //    Serial.print(readText(1));
    delay (500);
  }
}

char Ch_prm[250];

void serialEvent() {

  if (Serial.available()) {
    textSerial = Serial.readString();
    delay(100);
    writetxt(0,    textSerial,      lenText);
    /////(address, text data, panjang arrays)
    delay(1000);
  }
}

void writetxt(unsigned int addres, String text, int length) {
  //  String text;

  //  Set block plotter on eeprom use library
  eeprom.setBlock(addres, 0, length);
  /////////////////////////////////////

  // create String to char arrays
  int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  ////////////////////////////

  //  char to read data array from eeprom
  char data[length];
  ////////////////////////////////////////


  /////////////////(address,    data                ,   length text)
  eeprom.writeBlock(addres      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////

  //  read data from eeprom using for loop
  for (int i = 0; i < length; i++) {
    //    if (i % 10 == 0 ) SERIAL_OUT.println();
    //    SERIAL_OUT.print(' ');
    data[i] = eeprom.readByte(i);
    //    SERIAL_OUT.print((char)ee.readByte(i));
  }
  ////////////////////////////////////////

  //char array to data string
  
  Serial.println((String)data);
}

//manual access external eeprom using build in Wire lib

//void writeEEprom(unsigned int address, int data) {
//  wireTransmission(address);
//  Wire.write(data);
//  Serial.print("write Data  ");
//  //  Serial.println(data,HEX);
//  Serial.println(data);
//  Wire.endTransmission();
//  delay(5);
//}
//
//void  wireTransmission(unsigned int address) {
//  Wire.beginTransmission(ADD_I2C);
//  Wire.write((int)(address >> 8));   //MSB
//  Wire.write((int)(address & 0xFF)); //LSB
//}
//
//int readEEprom(unsigned int address) {
//  byte data ;
//  wireTransmission(address);
//  Wire.endTransmission();
//  Wire.requestFrom(ADD_I2C, 1);
//  delay(5);
//  if (Wire.available()) {
//    data = Wire.read();
//    Serial.print("read data : ");
//    Serial.println(data);
//    delay(5);
//  }
//  return data;
//}
//
//String readText(int addrss) {
//  int strLen = readEEprom(addrss);
//  char readTxt[strLen];
//  int i = 0;
//  while (i < strLen) {
//    readTxt[i] = readEEprom(addrss + i);
//    i++;
//    if (readEEprom(addrss + i) == '\0') {
//      break;
//    }
//  }
//  return String (readTxt);
//}
