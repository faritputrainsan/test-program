void runningText(String TEXT) {

  const char* readeep;
  //  String TextEep = read_Text(addres);
  readeep = TEXT.c_str();
  ronn.setFont(B_STD);
  ronn.scrollText_LR(readeep, 0, 0, WIDTH, 20);
  delay(1000);
}

void StaticTxt(String TEXT) {
//  String TEXT = "12:12    22:22    13:13    14:14    15:15    16:16";
  //  int pjg = TEXT.length() + 1;
  //  char TEXT.toCharArray
  ronn.setFont(B_STD);
  ronn.clear_D();
  ronn.scrollText_D(TEXT, 0, 1);
  delay(5000);
  //  ronn.clear_D();
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

void tgl() {
  const String bulan [] PROGMEM = {"JANUARI", "FEBRUARI", "MARET", "APRIL", "MEI",
                                   "JUNI", "JULI", "AGUSTUS", "SEPTEMBER", "OKTOBER",
                                   "NOVEMBER", "DESEMBER"
                                  };
}
