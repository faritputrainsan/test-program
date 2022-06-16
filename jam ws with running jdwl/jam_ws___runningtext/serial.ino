//String text_srl;
//char rchar;
//void serial() {
//  char prm[200];
//  int chr_idx = 0;
//
//
//  while (Stat == 1) {
//    //  rchar = Serial.peek();
//    //  if (rchar == 'S' ) {
//    //    while ((rchar != '\n') and (chr_idx < 305)) {
//    while (Serial.available()) {
//      text_srl = Serial.readString();
//      delay(1000);
//      //      rchar = (char)Serial.read();
//      Serial.println(text_srl);
//      delay(1000);
//      Stat = 0;
//      //      prm[chr_idx] = rchar;
//      //      chr_idx ++;
//      //    }
//    }
//
//    //    prm[chr_idx - 1] = '\0';
//    //    saveState();
//
//    //    int addres;
//    //    String msges;
//    //
//    //    if (text_srl.substring(0,1) == 'S') {
//    //      if (text_srl.substring(1,2) == 'N' and text_srl.substring(2,3) == 'M') {
//    //        addres = mn_add;
//    //      }
//    //      else if (text_srl.substring(1,2) == 'T' and text_srl.substring(2,3) == 'X') {
//    //        addres = text_add;
//    //      }
//    //      //    else if (prm[1] == 'T' and prm[2] == '1') {
//    //      //
//    //      ////      addres = text1_add;
//    //      //    }
//    ////      text_srl
//    //      msges = text_srl.substring(3, text_srl.length());
//    //
//    //      delay(100);
//    //      Write_text(msges, addres);
//    //      delay (200);
//    //
//    //
//    //    }
//    //    text_250 = read_Text(text_add);
//    //    Serial.println (text_250);
//    //  }
//
//    //  else if (rchar == 'J') {
//    //    //    data_jadwal = "0";
//    //    //    Serial.println(data_jadwal);
//    //  }
//    //  //  Serial.println(msg);
//    //  delay (1000);
//  }
//
//}
//
//void saveState() {
//
//}
//
//void Write_text(String msg, int addrs) {
//    Serial.println(msg);
//    Serial.print("panjang: ");
//    Serial.println(msg.length());
//    Serial.print("Address: ");
//    Serial.println(addrs);
//
//  for (int index = 0; index < msg.length() - 1; index++) {
//    EEPROM.update(addrs, msg[index]);
//    delay(10);
//        Serial.print("Writing ");
//        Serial.print(msg[index]);
//        Serial.print(" in address ");
//        Serial.println(addrs);
//    addrs++;
//  }
//  EEPROM.update(addrs, '\0');
//  EEPROM.read(addrs);
//}
//
//String read_Text(int addrs) {
//  int strLen = EEPROM.read(addrs);
//  char readChar [strLen];
//  String readGreeting;
//  int i = 0;
//
//  while (i < strLen) {
//    readChar[i] = EEPROM.read(addrs + i);
//    i++;
//
//  }
//  readChar[strLen] = '\0';
//
//  return String (readChar);
//}
//
//void setJadwal(String message) {
//  data_jadwal = message;
//}
//
//void setTanggal(String message) {
//  dates = message;
//}
//
//void ping() {
//  Serial.write("Ping");
//  delay(500);
//}
