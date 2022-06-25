void serial() {
  char bcar;
  int idx = 0;

  bcar = Serial.peek();
  if ((bcar == 'J') or (bcar == 'L')) {
    while ((bcar != '\n') and (idx < 380)){
      if (Serial.available()) {
        bcar = (char)Serial.read();
        dchar [idx] = bcar;
        idx++;
      }
    }
    dchar [idx - 1] = '\0';
    data();
//    Serial.print((String)dchar);
  }
}

void data(){
  String dataSrl = String(dchar);
  if (dchar[0]=='J'){
    if (dchar [1] == 'S' and dchar [2] == 'B'){
      subuh = dataSrl.substring(3,dataSrl.length());
      Serial.print("subuh");
//      Serial.println(jdwlkonversi(subuh));
    }
    else if(dchar [1] == 'D' and dchar [2] == 'H'){
//      Serial.println("dhuzur oke");
    }
    else if(dchar [1] == 'A' and dchar [2] == 'S'){
//      Serial.println("asar oke");
    }
    else if(dchar [1] == 'M' and dchar [2] == 'G'){
//      Serial.println("magrib oke");
    }
    else if(dchar [1] == 'I' and dchar [2] == 'S'){
//      Serial.println("isya oke");
    }
  }
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
  Serial.print("Ping\n");
  delay(500);
}
