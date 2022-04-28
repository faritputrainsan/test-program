void runningText(char* TEXT) {
  ronn.setFont(B_STD);
  ronn.scrollText_LR(TEXT, 0, 0, WIDTH, 20); delay(3000);
}

void StaticTxt(byte state) {
  String TEXT ="Masjid Yasmin III Nur Al-Fattah";
  int pjg = TEXT.length()+1;
//  char TEXT.toCharArray
  ronn.setFont(B_STD);
  ronn.clear_D();
  ronn.scrollText_D(TEXT, 0, 1);
  delay(5000);
  //  ronn.clear_D();
}

void jadwal(String imsak, String subuh, String dhuhur, String asar, String maghrib, String isya ) {

  ronn.clear_D();
  ronn.setFont(font_NEW);

  ronn.scrollText_D(imsak + "    " + subuh + "    " + dhuhur + "    " + asar + "    " + maghrib + "    " + isya , 1, 1 );
  buff.fillRect(41, 0, 1, 16, 1);
  buff.fillRect(84, 0, 1, 16, 1);
  buff.fillRect(127, 0, 1, 16, 1);
  buff.fillRect(170, 0, 1, 16, 1);
  buff.fillRect(213, 0, 1, 16, 1);
  delay (5000);
  ronn.clear_D(); delay(1000);
}

void tgl(String message) {

}
