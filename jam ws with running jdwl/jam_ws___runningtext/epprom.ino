void WriteText(unsigned int address, String text, int length) {
  /////////////////////////////////////
  eeprom.setBlock(address, '\0', length);
  /////////////////////////////////////

  ////////////////////////////////
  // create String to char arrays
  unsigned int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  ////////////////////////////////

  /////////////////(address      , data              , length text)
  eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////
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
