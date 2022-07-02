void WriteText(unsigned int address, String text, unsigned int lengths) {
  /////////////////////////////////////
  Serial.println(text);
  Serial.println(text.length());
  
  eeprom.setBlock(address, '\0', lengths);
  /////////////////////////////////////
  //strcpy();
  ////////////////////////////////
  // create String to char arrays
  unsigned int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  Serial.println(len);
  ////////////////////////////////

  /////////////////(address      , data              , length text)
  //  eeprom.writeBlock(address      , (uint8_t *) &text, sizeof(text));
  eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////
Serial.println(text_read(lengths, address));
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
String text_read( unsigned int length,  unsigned int address) {

  char data[length];
  for (unsigned int i = 0; i <  length; i++) {
    data[i] = eeprom.readByte( address + i  );
  }
  ////////////////////////////////////////
  // kembalikan String
  //      merubah char ke String
  return (String)data;
}
