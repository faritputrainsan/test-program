void iqm(byte islt) {

  int iqmah[] = {EEPROM.read(addsbh), EEPROM.read(addlhr),
                 EEPROM.read(addasr), EEPROM.read(addmgr),
                 EEPROM.read(addisy)
                };
//  int dtiqm = combine(1, 0) ;
    int dtiqm = combine(iqmah[islt], 0) ;
  while ( dtiqm >= 0) {
    digitalWrite(pull, LOW);
    digitalWrite(strobePin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm % 60 % 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm % 60 / 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm / 60 % 10]);
    shiftOut(dataPin, clockPin, LSBFIRST, segChar[dtiqm / 60 / 10]);
    digitalWrite(strobePin, HIGH);
    dtiqm--;
    delay(1000);
  }
  digitalWrite(pull, HIGH);
  delay(100);
}

void tunggu(byte i) {
  int   tggu[] = {EEPROM.read(addsubuh), EEPROM.read(addzuhur ),
                   EEPROM.read(addashar), EEPROM.read(addmaghrib),
                   EEPROM.read(addisya)
                  };
//  int dttg = combine(2, 0);/
  int dttg = combine(tggu[i], 0);
  digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  digitalWrite(strobePin, HIGH);
  while (dttg >= 0) {
    digitalWrite(pull, LOW);
    dttg --;
    delay (1000);
  }
  digitalWrite(pull, HIGH);
  delay(100);
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

void display_tepat () {
  int stlh = combine(3, 0);
  while (stlh >= 0) {
    jam_mtr();
    stlh --;
    delay (1000);
  }
  digitalWrite(pull, HIGH);
  delay(100);
}

void display_OK() {
  digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xf3);
  shiftOut(dataPin, clockPin, LSBFIRST, 0xC6);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  shiftOut(dataPin, clockPin, LSBFIRST, 0x00);
  digitalWrite(strobePin, HIGH);
  delay(3000);
}
