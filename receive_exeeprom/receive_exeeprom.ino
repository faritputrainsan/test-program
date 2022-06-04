#include <Wire.h>

//1. Alamat = 0x57

#define ADD_I2C 0x57

int input = 9;
byte r_input;

String textData = "Test external eeprom";
String TEXT_ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String textSerial;

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
    writetxt(1, TEXT_ABC);
    
//    Serial.println(readData(1));
    delay(500);

    Serial.print(readText(1));
    delay (500);
  }
}

char Ch_prm[250];

void serialEvent() {
    char data;
    int index = 0;
    
    if(Serial.available()){
      textSerial = Serial.readString();
      delay(100);
      writetxt(0, textSerial);
    }

    delay(1000);
    Serial.print(readText(1));
//    if (textSerial.substring(0,1) == "T"){
//     
//    }
}

void writetxt(unsigned int addres, String text) {
  //  String text;

  for (int i = 0; i < text.length(); i++ ) {
    writeEEprom(addres, text[i]);
    Serial.println(text[i]);
    addres++;
    delay(100);
  }
  writeEEprom(addres, '\n');
  delay(5);

}

void writeEEprom(unsigned int address, int data) {
  wireTransmission(address);
  Wire.write(data);
  Serial.print("write Data  ");
//  Serial.println(data,HEX);
  Serial.println(data);
  Wire.endTransmission();
  delay(5);
}

void  wireTransmission(unsigned int address) {
  Wire.beginTransmission(ADD_I2C);
  Wire.write((int)(address >> 8));   //MSB
  Wire.write((int)(address & 0xFF)); //LSB
}

int readEEprom(unsigned int address) {
  byte data ;
  wireTransmission(address);
  Wire.endTransmission();
  Wire.requestFrom(ADD_I2C, 1);
  delay(5);
  if (Wire.available()) {
    data = Wire.read();
    Serial.print("read data : ");
    Serial.println(data);
    delay(5);
  }
  return data;
}

String readText(int addrss){
  int strLen = readEEprom(addrss);
  char readTxt[strLen];
  int i = 0;
  while(i < strLen){
    readTxt[i] = readEEprom(addrss + i);
    i++;
    if (readEEprom(addrss + i) == '\n'){
      break;
    }
  }
  return String (readTxt);
}
