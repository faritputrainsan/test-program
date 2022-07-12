void serialEvent() {
  digitalWrite(res, LOW);
  String blutot;
  char dchar [70];
  char bcar;
  int idx = 0;

  //      Serial.println(blutot);

  bcar = Serial.peek();
  if ((bcar == 'L') or bcar == 'M') {
    while ((bcar != '\n') and (idx < 165)) {
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
    else if (dchar[0] == 'M') {
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
//    Serial.println(Serial.readString());
    saveData(Serial.readString());
  }
}

void saveData(String data) {

  // setting jam
  if (data.substring (0, 3) == "SJM") {
    rtc.setTime(data.substring (3, 5).toInt(), data.substring (5, 7).toInt(), data.substring (7, 9).toInt());     // Set the time to 12:00:00 (24hr format)
    rtc.setDate(data.substring (9, 11).toInt(), data.substring (11, 13).toInt(), data.substring (13, 17).toInt());    // Set the time to 12:00:00 (24hr format)
    rtc.setDOW(data.substring (17, 18).toInt());
  }
  // setting GMT
  else if (data.substring (0, 3) == "SGM") {
    EEPROM.write(addgmt, data.substring (3, 4).toInt());
    gmti = EEPROM.read(addgmt);
  }
  //  timer iqomah
  else if (data.substring (0, 3) == "SIQ") {
    EEPROM.write(addsbh, data.substring (3, 5).toInt());
    EEPROM.write(addlhr, data.substring (5, 7).toInt());
    EEPROM.write(addasr, data.substring (7, 9).toInt());
    EEPROM.write(addmgr, data.substring (9, 11).toInt());
    EEPROM.write(addisy, data.substring (11, 13).toInt());
  }
  //  timer tunggu
  else if (data.substring (0, 3) == "STG") {
    EEPROM.write(addsubuh, data.substring (3, 5).toInt());
    EEPROM.write(addzuhur, data.substring (5, 7).toInt());
    EEPROM.write(addashar, data.substring (7, 9).toInt());
    EEPROM.write(addmaghrib, data.substring (9, 11).toInt());
    EEPROM.write(addisya, data.substring (11, 13).toInt());
  }
  //  seting koreksi jadwal
  else if (data.substring (0, 3) == "SKS") {
    EEPROM.put(addksbh, data.substring (3, 5).toInt());
    EEPROM.put(addkzhr, data.substring (5, 7).toInt());
    EEPROM.put(addkasr, data.substring (7, 9).toInt());
    EEPROM.put(addkmgr, data.substring (9, 11).toInt());
    EEPROM.put(addkisy, data.substring (11, 13).toInt());
  }
  //  simpan texts ke external eeprom
  else if (data.substring (0, 3) == "TXS")WriteText(Text_add, data.substring(3, data.length()));
  //  simpan nama majid ke external eeprom
  else if (data.substring (0, 3) == "TMN")WriteText(mosName_add, data.substring(3, data.length()));
  // send data ke mcu running text
  else if (data.substring (0, 3) == "PNG")sendData();

}

void sendData() {
    sendJadwal();
    delay(100);
    sendTanggal();
    delay(100);

}

void sendJadwal() {
  char buffers[40];
  sprintf(buffers, "JSB%d\nJDH%d\nJAS%d\nJMG%d\nJIS%d\n", j_subuh, j_dzuhur,  j_ashar,  j_maghrib,  j_isya);
    Serial.print(buffers);
}

void sendTanggal() {
  const String hari []  = { "", "AHAD", "SENIN", "SELASA", "RABU", "KAMIS", "JUM'AT", "SABTU"};
  const String bulan []  = { "", "JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI", "JUNI",
                             "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER", "NOVEMBER", "JANUARI"};
  char buffers[30];
  //    sprintf(buffer, "DTE%s,  %d %s %d\n", hari[t.dow], t.date, bulan[t.mon], t.year)
  sprintf(buffers, "DTE%s,  %d %s %d\n", hari[t.dow].c_str(), t.date, bulan[t.mon].c_str(), t.year);
   Serial.print(buffers);
}
