void serialEvent() {
  char rchar;

  rchar = Serial.peek();
  if ((rchar == 'M')|| (rchar == 'T')) {
    msg = Serial.readString();
    saveText();
  }

  else if(rchar == 'J'){
    
    data_jadwal = "0";
//    Serial.println(data_jadwal);
  }
  //  Serial.println(msg);



  delay (1000);
}

void saveText() {
// use global variable to write to EEPROM
  EEPROM.put(100, msg);
  
  delay (2000);
//  Serial.println("OK");
//  getText();
  // message 2
  //  EEPROM.put(10,message);
  //  // mosque name
  //  EEPROM.put(20,message);
}

void getText() {
  
  
  
  delay (2000);
//  Serial.print("this text ");
//  Serial.println(name_mosque);
}
void setJadwal() {
  
  
}

void setTanggal() {

}
