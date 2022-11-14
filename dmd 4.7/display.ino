bool state;
byte c;
void display_clock(int spd, int cycle) {
  char buffH[3];
  char buffM[3];
  Tfont(1);


  sprintf(buffH, "%02d", now.Hour());
  sprintf(buffM, "%02d", now.Minute());
  // while (cycle > 0) {
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(buffH)) / 4, 0, buffH);
  DISPLAYs.drawText(((DWidth / 2) + DISPLAYs.textWidth(buffM) / 2 - 1), 0, buffM);

  static uint16_t x;
  static uint16_t tmnow;
  uint16_t tmr = millis();
 
  DISPLAYs.drawFilledCircle(DWidth / 2, 3, 1, state);
  DISPLAYs.drawFilledCircle(DWidth / 2, 12, 1, state);
   if ((tmr - tmnow) > spd) {
    tmnow = tmr;
    state = !state;
    if (c >= cycle) {
      select = 1;
      c = 0;
      DISPLAYs.clear();
    }
    c++;
    Serial.println(c);
  }
  // }
}

void display_text(int speed) {
}

void display_dateTime(int spd, int cycle) {
  char buffD[11];
  char haris[7];
  Tfont(2);

  static uint16_t x;
  static uint16_t tmnow;
  uint16_t tmr = millis();
  

  sprintf(buffD, "%02d-%02d-%04d", now.Day(), now.Month(), now.Year());
  sprintf(haris, "%s", Ndays(2));
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(buffD)) / 2, 0, buffD);
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(haris)) / 2, 8, haris);
  if ((tmr - tmnow) > spd) {
    tmnow = tmr;
    state = !state;
    if (c >= cycle) {
      select = 0;
      c = 0;
      DISPLAYs.clear();
    }
    c++;
    Serial.println(c);
  }
}