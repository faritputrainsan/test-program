void iqm(byte islt) {
  //  char tiq [3];
  //  char diq [3];
  int iqmah[] = {EEPROM.read(addsbh), EEPROM.read(addlhr), EEPROM.read(addasr),
                 EEPROM.read(addmgr), EEPROM.read(addisy)
                };
  int iqdtk = 0;
  byte dtiqm = iqmah[islt];
  //  if (islt == 0)iqmah = EEPROM.read(addsbh);
  //  else if (islt == 1) iqmah = EEPROM.read(addlhr);
  //  else if (islt == 2)iqmah = EEPROM.read(addasr);
  //  else if (islt == 3) iqmah = EEPROM.read(addmgr);
  //  else if (islt == 4)iqmah = EEPROM.read(addisy);

  while (1) {
    digitalWrite(strobePin, LOW);
//    if (islt == 0) {
//
//
//    }
//    else if (islt == 1) {
//
//    }
//    else if (islt == 2) {
//
//    }
//
//    else if (islt == 3) {
//
//    }
//    else if (islt == 4) {
//
//    }

    shiftOut(dataPin, clockPin, MSBFIRST, segChar[dtiqm / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[dtiqm % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[dtiqm / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[dtiqm % 10]);
    digitalWrite(strobePin, HIGH);


    if (iqdtk < 0)
    {
      if (dtiqm <= 0 ) {
        break;
      }
      else {
        dtiqm --;
        iqdtk = 59;
      }
    }
    iqdtk--;
    delay(1000);
  }
}


void tunggu(byte i) {
  int iqdtk = 0;
  byte   tggu[] = {EEPROM.read(addsubuh), EEPROM.read(addzuhur ),
                   EEPROM.read(addashar),EEPROM.read(addmaghrib),
                   EEPROM.read(addisya)
                  };
  digitalWrite(strobePin, LOW);
  byte dttg = tggu[i];
  //  if (i == 0)tggu = EEPROM.read(addsubuh);
  //  else if (i == 1) tggu = EEPROM.read(addzuhur );
  //  else if (i == 2)tggu = EEPROM.read(addashar);
  //  else if (i == 3) tggu = EEPROM.read(addmaghrib);
  //  else if (i == 4)tggu = EEPROM.read(addisya);

  while (1) {
    if (iqdtk < 0) {
      if (dttg <= 0 ) {
        break;
      }
      else {
        dttg --;
        iqdtk = 59;
      }
    }
    iqdtk --;
    delay (1000);
  }
}

void jam_mtr() {
  data();
  run();
}

void run() {
  data_jam();
}

void data_jam() {
  digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, segChar[t.min % 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, segChar[t.min / 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, segChar[t.hour % 10]);
  shiftOut(dataPin, clockPin, LSBFIRST, segChar[t.hour / 10]);
  digitalWrite(strobePin, HIGH);
}

void display_tepat (int a) {
  int stlh = 5;
  int iqdtk = 0;
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

    }
    else if (a == 1) {

    }
    else if (a == 2) {

    }
    else if (a == 3) {

    }
    else if (a == 4) {

    }
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min % 10]);

    digitalWrite(strobePin, HIGH);
  }
}
