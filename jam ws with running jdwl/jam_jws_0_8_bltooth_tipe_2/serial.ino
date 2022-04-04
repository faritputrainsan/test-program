void serial() {
  char bcar;
  int idx = 0;

  bcar = Serial.peek();
  if ((bcar == 'T') or (bcar == 'L')) {
    while ((bcar != '\n') and (idx < 80))
    {
      if (Serial.available()) {
        bcar = (char)Serial.read();
        dchar [idx] = bcar;
        idx++;
      }
    }
    dchar [idx - 1] = '\0';
    if (dchar[0] == 'L')
    {
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
      else if (blutot.substring (0, 3) == "SSS")uji();
    }
  }
}

void uji() {
  rtc.setTime(blutot.substring (3, 5).toInt(), blutot.substring (5, 7).toInt(), 00);
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

  digitalWrite(strobePin, LOW);

  mt_imsak();

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[isb / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[isb % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ilh / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ilh % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ias / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ias % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[img / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[img % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[iis / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[iis % 10]);

  

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[17]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[15]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);

  digitalWrite(strobePin, HIGH);
  delay(5000);
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

  digitalWrite(strobePin, LOW);
  mt_imsak();


  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[isb / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[isb % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ilh / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ilh % 10]);


  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ias / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[ias % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[img / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[img % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[iis / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[iis % 10]);



  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[20]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[14]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[6]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[6]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  digitalWrite(strobePin, HIGH);
  delay(5000);
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

  int ki , ks, kz, ka, km ;
  digitalWrite(strobePin, LOW);

  mt_imsak();
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  if (ksbh < 0) {
    ks = ksbh  * -1;
    shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[ks % 10]);
  }

  else {
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[ksbh / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[ksbh % 10]);
  }

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  if (kzhr < 0) {
    kz = kzhr * -1;
    shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kz % 10]);
  }
  else {
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kzhr / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kzhr % 10]);
  }

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  if (kasr < 0) {
    ka = kasr * -1;
    shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[ka % 10]);
  }
  else {
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kasr / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kasr % 10]);
  }

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  if (kmgr < 0) {
    km = kmgr * -1;
    shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[km % 10]);
  }
  else {
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kmgr / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kmgr % 10]);
  }

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  if (kisy < 0) {
    ki = kisy * -1;
    shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[ki % 10]);
  }
  else {
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kisy / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[kisy % 10]);
  }

  

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[15]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[18]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[4]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[10]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
  shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);

  digitalWrite(strobePin, HIGH);
  delay(5000);
}
