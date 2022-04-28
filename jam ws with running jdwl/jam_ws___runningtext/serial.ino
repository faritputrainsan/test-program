void serialEvent() {
  int chr_idx = 0;
  char rchar;

  rchar = Serial.peek();
  if (rchar == 'S' ) {
    while ((rchar != '\n') and (chr_idx < 201)) {
      if (Serial.available()) {
        rchar = (char)Serial.read();
        //        Serial.print(rchar);
        prm[chr_idx] = rchar;
        chr_idx ++;
      }
    }

    prm[chr_idx - 1] = '\0';
    saveState();
  }

  else if (rchar == 'J') {
    data_jadwal = "0";
    //    Serial.println(data_jadwal);
  }
  //  Serial.println(msg);
  delay (1000);
}

void saveState() {
  String text_srl;
  int addres;
  String msges;
  if (prm[0] == 'S') {
    if (prm[1] == 'N' and prm[2] == 'M') {
      addres = mn_add;
    }
    else if (prm[1] == 'T' and prm[2] == 'X') {
      addres = text_add;
    }
    else if (prm[1] == 'T' and prm[2] == '1') {

      addres = text1_add;
    }
    text_srl = String(prm);
    msges = text_srl.substring(3, text_srl.length());
    Serial.print (msges);
    delay(100);
    Write_text(msges, addres);
    delay (200);
    read_text(addres);
  }
}


void Write_text(String msg, int addrs) {
  Serial.println(msg);
  Serial.print("panjang: ");
  Serial.println(msg.length());
  Serial.print("Address: ");
  Serial.println(addrs);

  for (int index = 0; index < msg.length() - 1; index++) {
    EEPROM.update(addrs, msg[index]);

    delay(10);

    Serial.print("Writing ");
    Serial.print(msg[index]);
    Serial.print(" in address ");
    Serial.println(addrs);
    addrs++;
  }
  EEPROM.write(addrs, '\0');
  EEPROM.read(addrs);
}

void read_text(int addrs) {
  char readChar = "";
  String readGreeting = "";

  while (readChar != '\0') {
    Serial.print("Reading ");

    readChar = EEPROM.read(addrs);
    delay(10);
    if (readChar != '\0') {
      if (addrs == mn_add){
        mn_mosque += readChar;
      }
      else if(addrs == text_add){
         runnings = (char*) readGreeting;
      }
      else if(addrs == text1_add){
        running1 += readChar;
      }
      
    }

    addrs++;

    Serial.print(readChar);
    Serial.print(" in address ");
    Serial.println(addrs);
  }
  Serial.print("Final string read from EEPROM: ");
  Serial.println(runnings);
}

void setJadwal(String message) {
  data_jadwal = message;
}

void setTanggal(String message) {
  dates = message;
}

void ping() {
  Serial.write("Ping");
  delay(500);
}
