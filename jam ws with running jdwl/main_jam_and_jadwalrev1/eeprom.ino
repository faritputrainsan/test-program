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

  Wire.end();
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
  return data;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
String text_read(unsigned int address) {
  int lengths = readData(address);
  Serial.println(lengths);
  char readTxt[lengths];
  int i = 0;
  while (i <= lengths) {
    readTxt[i] = readData(address + 1 + i);
    i++;

  }
  Wire.end();
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
