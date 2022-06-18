String text_srl;
char rchar;
void serial() {
  char prm[200];
  int chr_idx = 0;
  //  rchar = Serial.peek();
  //  if (rchar == 'S' ) {
  //    while ((rchar != '\n') and (chr_idx < 305)) {
  while (Serial.available()) {
    text_srl = Serial.readString();
    delay(1000);
    //      rchar = (char)Serial.read();
    Serial.println(text_srl);
    delay(1000);
    //    Stat = 0;
    //      prm[chr_idx] = rchar;
    //      chr_idx ++;
    //    }
  }

  //    prm[chr_idx - 1] = '\0';
  //    saveState();
  //    int addres;
  //    String msges;
  //    if (text_srl.substring(0,1) == 'S') {
  //      if (text_srl.substring(1,2) == 'N' and text_srl.substring(2,3) == 'M') {
  //        addres = mn_add;
  //      }
  //      else if (text_srl.substring(1,2) == 'T' and text_srl.substring(2,3) == 'X') {
  //        addres = text_add;
  //      }
  //      //    else if (prm[1] == 'T' and prm[2] == '1') {
  //      //
  //      ////      addres = text1_add;
  //      //    }
  ////      text_srl
  //      msges = text_srl.substring(3, text_srl.length());
  //      delay(100);
  //      Write_text(msges, addres);
  //      delay (200);
  //    }
  //    text_250 = read_Text(text_add);
  //    Serial.println (text_250);
  //  }
  //  else if (rchar == 'J') {
  //    //    data_jadwal = "0";
  //    //    Serial.println(data_jadwal);
  //  }
  //  //  Serial.println(msg);
  //  delay (1000);
}

void saveState() {

}

void setJadwal(String message) {

  //  = jdwlkonversi("555");
  //  = jdwlkonversi("555");
  //  = jdwlkonversi("555");
  //  = jdwlkonversi("555");
  //  = jdwlkonversi("555");
  //  = jdwlkonversi("555");
}

void setTanggal(String message) {

}

void ping() {
  Serial.write("Ping");
  delay(500);
}
