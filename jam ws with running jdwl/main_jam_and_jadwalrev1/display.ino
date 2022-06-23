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


    }
    else if (islt == 1) {

    }
    else if (islt == 2) {

    }

    else if (islt == 3) {

    }
    else if (islt == 4) {

    }

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

void jam_mtr() {
  data();
  run();
}

int interval = 10;
unsigned long previusMillis = 0;
void run() {
  //  unsigned long currenMillis = millis();
  //  if (currenMillis - previusMillis >= interval) {
  //    previusMillis = currenMillis;
  data_jam();

  //  }
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
