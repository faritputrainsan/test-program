void serialEvent(){
  char* rchar;

  rchar =Serial.peek();
}

void saveText(String message, String message2, String mosque){
  // Message
  EEPROM.put(0,message);

  // message 2
  EEPROM.put(10,message2);
  // mosque name
  EEPROM.put(20,mosque);
}

void getText(byte state){
  switch (state){
    case 1 :
    break;
  }
}
void setJadwal(){
  data_jadwal = "";
}

void setTanggal(){
  
}
