void WriteText(unsigned int address,String text, int length){
  eeprom.setBlock(address, 0, length);
  /////////////////////////////////////

  // create String to char arrays
  int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  ////////////////////////////

  //  char to read data array from eeprom
  
  ////////////////////////////////////////


  /////////////////(address,    data                ,   length text)
  eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////

  //  read data from eeprom using for loop
  
}

String text_read(unsigned int length){
  char data[length];
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
