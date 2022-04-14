void serialEvent() {
  char rchar;

  rchar = Serial.peek();
  if ((rchar == 'M') || (rchar == 'T')) {
    //    while(){
    //
    //    }
    if (Serial.available()) {
       msg = Serial.readString();
      save();
    }


  }

  else if (rchar == 'J') {

    data_jadwal = "0";
    //    Serial.println(data_jadwal);
  }
  //  Serial.println(msg);



  delay (1000);
}

void save() {
  // use global variable to write to EEPROM
 
  EEPROM.put(adds_mosque, msg);
 

  delay (1000);
  getText();
//  Serial.println("")
//    Serial.println("OK");
  //  getText();
  // message 2
  //  EEPROM.put(10,message);
  //  // mosque name
  //  EEPROM.put(20,message);
}

void getText() {

EEPROM.get(adds_mosque, Text);
delay (1000);

//  delay (2000);
  //  Serial.print("this text ");
  //  Serial.println(name_mosque);
}
void setJadwal() {


}

void setTanggal() {

}
