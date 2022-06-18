void runningText(String TEXT) {

  const char* readeep;
//  String TextEep = read_Text(addres);
  readeep = TEXT.c_str();
  ronn.setFont(B_STD);
//  ronn.scrollText_LR(readeep, 0, 0, WIDTH, 20);
}

void StaticTxt(byte state) {
  String TEXT = "32 SEPTEMBER 2022";
//  int pjg = TEXT.length() + 1;
  //  char TEXT.toCharArray
  ronn.setFont(B_STD);
  ronn.clear_D();
  ronn.scrollText_D(TEXT, 0, 1);
  delay(5000);
  //  ronn.clear_D();
}

void jadwal() {


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
