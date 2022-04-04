void t_isya() {
  //digitalWrite(strobePin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_isya / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_isya % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_isya / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_isya % 10]);
}

void t_maghrib() {
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_maghrib / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_maghrib % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_maghrib / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_maghrib % 10]);
}

void t_asar() {

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_ashar / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_ashar % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_ashar / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_ashar % 10]);
}

void t_dzuhur () {
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_dzuhur / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_dzuhur % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_dzuhur / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_dzuhur % 10]);
}

void t_subuh() {
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_subuh / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_subuh % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_subuh / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_subuh % 10]);
}

void t_imsak() {
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_imsak / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[j_imsak % 10]);

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_imsak / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[m_imsak % 10]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mt_isya() {
  //digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void mt_maghrib() {
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void mt_asar() {
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void mt_dzuhur () {
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void mt_subuh() {
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void mt_imsak() {
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
}

void hari(int r) {
  switch (r) {
    case 2:
      //senin
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[4]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[14]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[14]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 3:
      //selasa
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[4]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[11]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 4:
      //rabu
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[18]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[1]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 5:
      //kamis
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[10]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 6:
      //jum'at
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[9]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xef);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[20]);
      break;
    default:
      //sabtu
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[1]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[20]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 1:
      //minggu
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[14]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[6]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[6]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      break;
  }
}

void name_slt(int r) {
  switch (r) {
    default:
      //imsak
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[10]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 1:
      //subuh
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[1]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 2:
      //dhuhur
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[3]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[21]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[18]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 3:
      //asar
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[18]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
    case 4:
      //maghrib
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[6]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[18]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[1]);
      break;
    case 5:
      //isya
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[19]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[22]);
      shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
      break;
  }
}

void iqm(byte islt) {
  //  char tiq [3];
  //  char diq [3];
  iqdtk = 0;
  if (islt == 0)iqmah = EEPROM.read(addsbh);
  else if (islt == 1) iqmah = EEPROM.read(addlhr);
  else if (islt == 2)iqmah = EEPROM.read(addasr);
  else if (islt == 3) iqmah = EEPROM.read(addmgr);
  else if (islt == 4)iqmah = EEPROM.read(addisy);

  while (1) {
    digitalWrite(strobePin, LOW);
    if (islt == 0) {
      mt_imsak();
      t_subuh();
      mt_dzuhur();

      mt_asar();
      mt_maghrib();
      mt_isya();

    }
    else if (islt == 1) {
      mt_imsak();
      mt_subuh();
      t_dzuhur();

      mt_asar();
      mt_maghrib();
      mt_isya();

    }
    else if (islt == 2) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      t_asar();
      mt_maghrib();
      mt_isya();
    }

    else if (islt == 3) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      mt_asar();
      t_maghrib();
      mt_isya();

    }
    else if (islt == 4) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      mt_asar();
      mt_maghrib();
      t_isya();


    }
    shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[8]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[17]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[15]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[12]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[13]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[0]);
    shiftOut(dataPin, clockPin, MSBFIRST, huruf[7]);

    shiftOut(dataPin, clockPin, MSBFIRST, segChar[iqmah / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[iqmah % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[iqdtk / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[iqdtk % 10]);
    digitalWrite(strobePin, HIGH);


    if (iqdtk < 0)
    {
      if (iqmah <= 0 ) {
        break;
      }
      else {
        iqmah --;
        iqdtk = 59;
      }
    }
    iqdtk--;
    delay(1000);
  }
}


void tunggu(byte i) {
  iqdtk = 0;
  digitalWrite(strobePin, LOW);
  mt_isya();
  mt_maghrib();
  mt_asar();
  mt_dzuhur();
  mt_subuh();
  mt_imsak();

  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, MSBFIRST, 0xff);
  digitalWrite(strobePin, HIGH);

  if (i == 0)tggu = EEPROM.read(addsubuh);
  else if (i == 1) tggu = EEPROM.read(addzuhur );
  else if (i == 2)tggu = EEPROM.read(addashar);
  else if (i == 3) tggu = EEPROM.read(addmaghrib);
  else if (i == 4)tggu = EEPROM.read(addisya);

  while (1) {

    if (iqdtk < 0) {
      if (tggu <= 0 ) {
        break;
      }
      else {
        tggu --;
        iqdtk = 59;
      }
    }
    iqdtk --;
    delay (1000);
  }
}

void tggl() {

  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.date / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.date % 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.mon / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.mon % 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, 0x7f);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.year % 1000 % 100 / 10]);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.year % 1000 % 100 % 10]);
}

void jam_mtr() {
  data();
  run();
}

void jdwlT() {
  jdwl();

  t_imsak();
  t_subuh();
  t_dzuhur();

  t_asar();
  t_maghrib();
  t_isya();


}

int interval = 10;
unsigned long previusMillis = 0;
void run() {
  unsigned long currenMillis = millis();
  if (currenMillis - previusMillis >= interval) {
    previusMillis = currenMillis;
    digitalWrite(strobePin, LOW);
    jdwlT();
    x++;
    if (x == 1001)x = 0;
    if (x < 501) {
      tggl();
    }
    else if (x < 1001) {
      hari(t.dow);
    }
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min % 10]);
    digitalWrite(strobePin, HIGH);

  }
}

void display_tepat (int a) {

  int stlh = 5;
  iqdtk = 0;
  while (1) {
    data();
    if (iqdtk < 0)
    {
      if (stlh <= 0 ) {
        break;
      }
      else {
        stlh --;
        iqdtk = 59;
      }
    }
    iqdtk--;
    delay (1000);
    digitalWrite(strobePin, LOW);
    if (a == 0) {
      mt_imsak();
      t_subuh();
      mt_dzuhur();

      mt_asar();
      mt_maghrib();
      mt_isya();

    }
    else if (a == 1) {
      mt_imsak();
      mt_subuh();
      t_dzuhur();

      mt_asar();
      mt_maghrib();
      mt_isya();

    }
    else if (a == 2) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      t_asar();
      mt_maghrib();
      mt_isya();
    }
    else if (a == 3) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      mt_asar();
      t_maghrib();
      mt_isya();
    }
    else if (a == 4) {
      mt_imsak();
      mt_subuh();
      mt_dzuhur();

      mt_asar();
      mt_maghrib();
      t_isya();
    }
    name_slt(a + 1);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min % 10]);

    digitalWrite(strobePin, HIGH);
  }
}
