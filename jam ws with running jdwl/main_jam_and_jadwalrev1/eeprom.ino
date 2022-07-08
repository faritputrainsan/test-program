void WriteText(unsigned int address, const String text,  unsigned int lengths) {

  eeprom.setBlock(address, 0, lengths);
  Serial.println(text);
  unsigned int TextLength = text.length();
  unsigned int MaxText = 60;
  int lenSplitTxt = TextLength / MaxText;

  int x = 0, y = 0, z = 0;
  for (int i = 0; i < lenSplitTxt + 1; i++) {
    //    reset string untuk di isi lagi
    String splitText = " ";
    x = MaxText * y;
    int adds = address + x;
    z = 1;
    y ++;
    //    x = 60;
    int xx = MaxText * y;
    splitText = text.substring(x, xx);

    Serial.println(splitText);
    unsigned int lentxt = splitText.length();
    char data2[lentxt] = " ";
    splitText.toCharArray(data2, lentxt);
    eeprom.writeBlock(adds    , (uint8_t *) &data2, sizeof(data2));
    Serial.println(adds);
    delay(1000);
  }

  delay(2000);
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
