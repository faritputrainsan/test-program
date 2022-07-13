void runningText(String TEXT) {
  ronn.setFont(B_STD);
  ronn.scrollText_LR(TEXT.c_str(), 0, 0, WIDTH, 20);
  delay(3000);
}

void StaticTxt(String TEXT, int x, int y) {
  ronn.setFont(B_STD);
  ronn.clear_D();
  ronn.scrollText_D(TEXT, x, y);
  delay(5000);
}

void jadwal() {
  ronn.setFont(font_NEW);
  ronn.clear_D();

  char buffer[51];
  sprintf(buffer, "%s    %s    %s    %s    %s    %s",
          jdwlkonversi(subuh - 10).c_str(), jdwlkonversi(subuh).c_str(),
          jdwlkonversi(dhuhur).c_str(), jdwlkonversi(asar).c_str(),
          jdwlkonversi(maghrib).c_str(), jdwlkonversi(isya).c_str()) ;

  ronn.scrollText_D(buffer , 1, 1 );
  //  Serial.println(buffer);
  buff.fillRect(41, 0, 1, 16, 1);
  buff.fillRect(84, 0, 1, 16, 1);
  buff.fillRect(127, 0, 1, 16, 1);
  buff.fillRect(170, 0, 1, 16, 1);
  buff.fillRect(213, 0, 1, 16, 1);
  delay (5000);
  ronn.clear_D();
  delay(1000);
}

void displayTpt(byte state) {
  int djwl [] = { 0, subuh  , dhuhur , asar  , maghrib , isya};
  const String slt[] PROGMEM = { "IMSAK", "SUBUH", "DHUHUR", "ASAR", "MAGHRIB", "ISYA'" };
  char buffer[15];
  sprintf(buffer, "%s  %s", slt[state].c_str(),  jdwlkonversi(djwl[state]).c_str());
  StaticTxt(buffer, 0, 1);
  while (tmbl() == LOW) {

  }
  delay(1000);
}

void iqmah() {
  const String iqm = "IQOMAH";
  StaticTxt(iqm, 96, 1);
  while (tmbl() == LOW) {

  }
  delay(1000);
}

void tunggu() {
  ronn.clear_D();
  while (tmbl() == LOW) {

  }
  delay(1000);
}
