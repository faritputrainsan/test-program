#include <Wire.h>


#define ADD_I2C 0x57

//String Text = "Selamat datang di Smarttraintech Solusi digital anda silahkan berbelanja dengan senang hati anda sopan kami segan kepuasan anda adalah kebahagiaan kami kami akan selalu melayani anda dengan sepenuh hati jiwa dan raga tak akan terganti kan oleh waktu htres";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  Wire.begin();
  //  WriteText(0, Text);
  //  delay (500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  Serial.println(Text.length());
  String baca = text_read(0);
  delay(1000);
  Serial.println(baca);
  delay(1000);
  String baca1 = text_read(65);
  delay(1000);
  Serial.println(baca1);
  delay(2000);

}

void wireInnit(unsigned int address) {
  Wire.begin();
  Wire.beginTransmission(ADD_I2C);
  Wire.write((int)(address >> 8));   //MSB
  Wire.write((int)(address & 0xFF));  //LSB
}

void WriteText(unsigned int address, const String text) {
  unsigned int lengths = text.length();
  saveData(address, lengths);
  for (int i = 0; i <= lengths; i++ ) {
    saveData(address + 1 + i, text[i]);
  }

  //  Wire.end();
}

void saveData(unsigned int address, int data) {
  wireInnit(address);
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}

int readData(unsigned int address) {
  int data;
  wireInnit(address);
  Wire.endTransmission();
  Wire.requestFrom(ADD_I2C, 1);
  delay(10);
  if (Wire.available()) {
    data = Wire.read();
  }
  Wire.end();
  return data;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
String text_read(unsigned int address) {
  int lengths = readData(address) + 1;
  //  Serial.println(lengths);
  char readTxt[lengths];
  int i = 0;
  while (i < lengths) {
    readTxt[i] = readData(address + 1 + i);
    i++;
    delay(10);
  }

  return String(readTxt);
  //  char data[length];
  //  /for (unsigned int i = 0; i <  length; i++) {
  //    //    data[i] = eeprom.readByte( address + i  );
  //  }
  //  ////////////////////////////////////////
  //  // kembalikan String
  //  //      merubah char ke String
  //  return (String)data;
}
