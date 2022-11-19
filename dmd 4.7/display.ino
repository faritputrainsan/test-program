bool state;
byte c;
int x;
void display_clock(int spd, int cycle) {
  char buffH[3];
  char buffM[3];
  Tfont(1);

  sprintf(buffH, "%02d", now.hour());
  sprintf(buffM, "%02d", now.minute());
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(buffH)) / 4, 0, buffH);
  DISPLAYs.drawText(((DWidth / 2) + DISPLAYs.textWidth(buffM) / 2 - 1), 0, buffM);

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
    // Serial.println(c);
  }
}

void display_text(int spd, String text) {
  int fs = DISPLAYs.textWidth(text) + DWidth;
  Tfont(3);

  static uint16_t tmnow;
  uint16_t tmr = millis();
  if ((tmr - tmnow) > spd) {
    tmnow = tmr;
    DISPLAYs.drawText(DWidth - x, 0, text);
    // Serial.println(DWidth - x);
    if (x < fs) {
      ++x;
    } else {
      x = 0;
      select = 0;
      DISPLAYs.clear();
      return;
    }
  }
}

void display_dateTime(int spd, int cycle) {
  char buffD[11];
  char haris[7];
  Tfont(2);
  static uint16_t tmnow;
  uint16_t tmr = millis();

  sprintf(buffD, "%02d-%02d-%04d", now.day(), now.month(), now.year());
  sprintf(haris, "%s", Ndays(2));
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(buffD)) / 2, 0, buffD);
  DISPLAYs.drawText((DWidth - DISPLAYs.textWidth(haris)) / 2, 8, haris);
  if ((tmr - tmnow) > spd) {
    tmnow = tmr;
    if (c >= cycle) {
      select = 2;
      x = 0;
      c = 0;
      state = true;
      DISPLAYs.clear();
    }
    c++;
  }
}