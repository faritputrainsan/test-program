void serialEvent() {
  char bcar;
  int idx = 0;
  bcar = Serial.peek();
  if ((bcar == 'T') or (bcar == 'L')) {
    while ((bcar != '\n') and (idx < 350)) {
      if (Serial.available()) {
        bcar = (char)Serial.read();
        dchar [idx] = bcar;
        idx++;
      }
    }
    dchar [idx - 1] = '\0';
    if (dchar[0] == 'L') {
      blutot = String(dchar);
      if (blutot.substring(1, 3).equals("AT"))       {
        EEPROM.put(addltg, blutot.substring(3, blutot.length()).toFloat());
      }
      else if (blutot.substring(1, 3).equals("ON"))  {
        EEPROM.put(addbjr, blutot.substring(3, blutot.length()).toFloat());
      }
    }
    else if (dchar[0] == 'T')
    {
      blutot = String(dchar);
      if (blutot.substring(1, 3).equals("AT"))       {
        EEPROM.put(addltg, blutot.substring(3, blutot.length()).toFloat());
      }
      else if (blutot.substring(1, 3).equals("ON"))  {
        EEPROM.put(addbjr, blutot.substring(3, blutot.length()).toFloat());
      }
    }
  }

  else {
    //    display.clear();
    if (Serial.available()) {
      blutot = Serial.readString();
      if (blutot.substring (0, 3) == "SJM")set_jam();
      else if (blutot.substring (0, 3) == "SGM")gmt();
      else if (blutot.substring (0, 3) == "SIQ")Siqomah();
      else if (blutot.substring (0, 3) == "STG")Stunggu();
      else if (blutot.substring (0, 3) == "SKS")koreksi();
      //      else if (blutot.substring (0, 3) == "SSS")uji();
    }
  }
}

void set_jam() {
  rtc.setTime(blutot.substring (3, 5).toInt(), blutot.substring (5, 7).toInt(), blutot.substring (7, 9).toInt());     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(blutot.substring (9, 11).toInt(), blutot.substring (11, 13).toInt(), blutot.substring (13, 17).toInt());     // Set the time to 12:00:00 (24hr format)
  rtc.setDOW(blutot.substring (17, 18).toInt());
}

void gmt() {

  EEPROM.write(addgmt, blutot.substring (3, 4).toInt());
  gmti = EEPROM.read(addgmt);
}

void Siqomah() {

  EEPROM.write(addsbh, blutot.substring (3, 5).toInt());
  EEPROM.write(addlhr, blutot.substring (5, 7).toInt());
  EEPROM.write(addasr, blutot.substring (7, 9).toInt());
  EEPROM.write(addmgr, blutot.substring (9, 11).toInt());
  EEPROM.write(addisy, blutot.substring (11, 13).toInt());

  byte isb, ilh, ias, img, iis;

  isb = EEPROM.read(addsbh);
  ilh = EEPROM.read(addlhr);
  ias = EEPROM.read(addasr);
  img = EEPROM.read(addmgr);
  iis = EEPROM.read(addisy);
}

void Stunggu() {

  EEPROM.write(addsubuh, blutot.substring (3, 5).toInt());
  EEPROM.write(addzuhur, blutot.substring (5, 7).toInt());
  EEPROM.write(addashar, blutot.substring (7, 9).toInt());
  EEPROM.write(addmaghrib, blutot.substring (9, 11).toInt());
  EEPROM.write(addisya, blutot.substring (11, 13).toInt());

  byte isb, ilh, ias, img, iis;

  isb = EEPROM.read(addsubuh);
  ilh = EEPROM.read(addzuhur);
  ias = EEPROM.read(addashar);
  img = EEPROM.read(addmaghrib);
  iis = EEPROM.read(addisya);
}

void koreksi() {

  EEPROM.put(addksbh, blutot.substring (3, 5).toInt());
  EEPROM.put(addkzhr, blutot.substring (5, 7).toInt());
  EEPROM.put(addkasr, blutot.substring (7, 9).toInt());
  EEPROM.put(addkmgr, blutot.substring (9, 11).toInt());
  EEPROM.put(addkisy, blutot.substring (11, 13).toInt());

  EEPROM.get(addksbh, ksbh);
  EEPROM.get(addkzhr, kzhr);
  EEPROM.get(addkasr, kasr);
  EEPROM.get(addkmgr, kmgr);
  EEPROM.get(addkisy, kisy);
}



void sendData() {
  char buffer[40];
  sprintf(buffer, "JSB%d\nJDH%d\nJAS%d\nJMG%d\nJIS%d\n", j_imsak, j_subuh, j_dzuhur,  j_ashar,  j_maghrib,  j_isya);
  while (1) {
    if ( Serials.substring(0, 4) == "Ping") {
      Serials = '\0';
      mySerial.print(buffer);
      sendJadwal();
      
    }
    break;
  }
}

void sendJadwal(){
  
  
}

void sendTanggal(){
  char buffer[30];
//  sprintf(buffer,"DTE%s\n",hari[t.dow]);
  mySerial.print(buffer);
}
