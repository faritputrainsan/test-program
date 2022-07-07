void WriteText(unsigned int address, String text,  unsigned int lengths) {

  //  String text = blutot.substring(3, blutot.length());
  //  String text ;
  Serial.println(text);
  unsigned int TextLength = text.length();
  unsigned int MaxText = 60;
  int lenSplitTxt = TextLength / MaxText;

  int x = 0, y = 0;
  for (int i = 0; i < lenSplitTxt + 1; i++) {
    //    reset string untuk di isi lagi
    String splitText = " ";
    x = MaxText * y;
    y ++;
    //    x = 60;
    int xx = MaxText * y;

    splitText = text.substring(x, xx);
    delay(1000);
    Serial.println(splitText);
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
