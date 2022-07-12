void serial() {
  char dchar[160];
  char bcar;
  int idx = 0;


  bcar = Serial.peek();
  if ((bcar == 'J') or (bcar == 'D')) {
    while ((bcar != '\n') and (idx < 160)) {
      if (Serial.available()) {
        bcar = (char)Serial.read();
        dchar [idx] = bcar;
        idx++;
      }
    }
    dchar [idx - 1] = '\0';
    data(dchar);
    //        Serial.print((String)dchar);
  }
}

void data(String dataSrl) {

//  if (dchar[0] == 'J') {
//    if (dchar [1] == 'S' and dchar [2] == 'B') {
//      subuh = dataSrl.substring(3, dataSrl.length()).toInt();
//      delay (5);
//      //      Serial.println("subuh oke");
//    }
//    else if (dchar [1] == 'D' and dchar [2] == 'H') {
//      dhuhur = dataSrl.substring(3, dataSrl.length()).toInt();
//      delay (5);
//      //      Serial.println("dhuzur oke");
//    }
//    else if (dchar [1] == 'A' and dchar [2] == 'S') {
//      asar = dataSrl.substring(3, dataSrl.length()).toInt();
//      delay (5);
//      //      Serial.println("asar oke");
//    }
//    else if (dchar [1] == 'M' and dchar [2] == 'G') {
//      maghrib = dataSrl.substring(3, dataSrl.length()).toInt();
//      delay (5);
//      //      Serial.println("magrib oke");
//    }
//    else if (dchar [1] == 'I' and dchar [2] == 'S') {
//      isya = dataSrl.substring(3, dataSrl.length()).toInt();
//      delay (5);
//      //      Serial.println("isya oke");
//      //      exits = 1;
//    }
//  }
//  else if (dchar[0] == 'D' and dchar [1] == 'T' and dchar [2] == 'E') {
//    dayDate = dataSrl.substring(3, dataSrl.length());
//    delay (5);
//    exits = 1;
//  }
}

void ping() {
  Serial.print("Ping\n");
  delay(500);
}
