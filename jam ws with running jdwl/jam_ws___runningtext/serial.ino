void serial() {
  char rchar;
  
  String savemsg;

  rchar = Serial.peek();
  Serial.println("serial");
  if (rchar == 'M') {
    msg = Serial.readString();
    savemsg = msg.substring(2,msg.length());
    Serial.println("OK");
    
    //
    
    saveText(savemsg);
  }
  //  Serial.println(msg);



  delay (1000);
}

void saveText(String message) {
  String Text;
  Serial.println(message);
  EEPROM.put(10,message);
  delay (2000);
  EEPROM.get(10, name_mosque);
//   = Text;
  delay (2000);
  StaticTxt(name_mosque);
  Serial.print("this text ");
   Serial.println(name_mosque);
  
  // message 2
  //  EEPROM.put(10,message);
  //  // mosque name
  //  EEPROM.put(20,message);
}

void getText(byte state) {

}
void setJadwal() {
  data_jadwal = "";
}

void setTanggal() {

}
