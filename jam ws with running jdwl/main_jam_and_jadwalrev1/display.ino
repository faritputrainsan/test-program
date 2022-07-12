void iqm(byte islt) {
  
  int iqmah[] = {EEPROM.read(addsbh), EEPROM.read(addlhr), EEPROM.read(addasr),
                 EEPROM.read(addmgr), EEPROM.read(addisy)
                };
  int dtiqm = combine(iqmah[islt], 0) ;
  while ( dtiqm >= 0) {
    digitalWrite(strobePin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm % 60 % 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm % 60 / 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm / 60 % 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm / 60 / 10]);
    digitalWrite(strobePin, HIGH);
    dtiqm--;
    delay(1000);
  }

}

void tunggu(byte i) {
  byte   tggu[] = {EEPROM.read(addsubuh), EEPROM.read(addzuhur ),
                   EEPROM.read(addashar), EEPROM.read(addmaghrib),
                   EEPROM.read(addisya)
                  };
  int dttg = combine(tggu[i], 0);
  digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xff);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xff);
  digitalWrite(strobePin, HIGH);
  while (dttg > 0) {
    dttg --;
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
  int stlh = combine(3, 0);
  while (stlh >= 0) {
    stlh --;
    delay (1000);
    digitalWrite(strobePin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.hour % 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min / 10]);
    shiftOut(dataPin, clockPin, MSBFIRST, segChar[t.min % 10]);
    digitalWrite(strobePin, HIGH);
  }
}
