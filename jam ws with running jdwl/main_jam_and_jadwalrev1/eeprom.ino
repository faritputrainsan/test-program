void WriteText(unsigned int address, String text, unsigned int lengths) {
  /////////////////////////////////////
  //  Serial.println(text);
  //  Serial.println(text.length());

  eeprom.setBlock(address, '\0', lengths);
  /////////////////////////////////////
  //strcpy();
  ////////////////////////////////
  // create String to char arrays
  ////////////////////////////////


  unsigned int TextLength = text.length();
  unsigned int MaxText = 60;
  int lenSplitTxt = TextLength / MaxText;
  int x = 0, y = 0;

  for (int i = 0; i < lenSplitTxt; i++) {
    String splitText = " ";
    x = MaxText * y;
    y++;
    int xx = MaxText * y;
    splitText = text.substring(x, xx);
    unsigned int len = splitText.length() + 1;
    char data2[len];
    splitText.toCharArray(data2, len);
    eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
    delay(100);
  }

  //  unsigned int Tlength = text.length() + 1;
  //  unsigned int lengthMax = 60;
  //  String splitText ;
  //  int x = 0;
  //  int y = 1;
  //  for (unsigned int i =  0; i  < Tlength ; i++) {
  //    if (Tlength / lengthMax == 0) {
  //      splitText = text.substring(x, lengthMax * y);
  //      unsigned int len = text.length() + 1;
  //      char data2[len];
  //      text.toCharArray(data2, len);
  //      eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //    }
  //    else if (Tlength % lengthMax == 0) {
  //      splitText = text.substring(x, lengthMax * y);
  //      unsigned int len = text.length() + 1;
  //      char data2[len];
  //      text.toCharArray(data2, len);
  //      /////////////////(address      , data              , length text)
  //      eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //    }
  //    //    Serial.println(len);
  //  }
  //  eeprom.writeBlock(address      , (uint8_t *) &text, sizeof(text));
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
