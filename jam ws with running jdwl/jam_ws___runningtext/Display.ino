void runningText(char* TEXT) {
  ronn.setFont(B_STD);
  ronn.scrollText_LR(TEXT, 0, 0, WIDTH, 20); delay(3000);
}

void StaticTxt(char* TEXT){
  
}

void jadwal(String imsak, String subuh, String dhuhur, String asar, String maghrib, String isya ) {

  ronn.clear_D();
  ronn.setFont(font_NEW);

  ronn.scrollText_D(imsak+"    "+subuh+"    "+dhuhur+"    "+asar+"    "+maghrib+"    "+isya , 0, 1 );
  buff.fillRect(40, 0, 1, 16, 1);
  buff.fillRect(83, 0, 1, 16, 1);delay (5000);
  //  ronn.scrollText_D("06:30", 43, 0, 64 - 11);
  //  ronn.scrollText_D(, 86, 1, 64 - 11);

//  for (int i = 1; i <= 5; i++) {
//    delay(400);
//    buff.fillRect(18, 0, 2, 14, 0);
//    delay(600);
//    ronn.printText(":", 18, 0);
//  }
    ronn.clear_D();delay(1000);
}

void tgl(String message){
  
}
