void serial() {
  char dchar[70];
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

  if (dataSrl[0] == 'J') {
    if (dataSrl [1] == 'S' and dataSrl [2] == 'B') {
      subuh = dataSrl.substring(3, dataSrl.length()).toInt();
      delay (5);
      //      Serial.println("subuh oke");
    }
    else if (dataSrl [1] == 'D' and dataSrl [2] == 'H') {
      dhuhur = dataSrl.substring(3, dataSrl.length()).toInt();
      delay (5);
      //      Serial.println("dhuzur oke");
    }
    else if (dataSrl [1] == 'A' and dataSrl [2] == 'S') {
      asar = dataSrl.substring(3, dataSrl.length()).toInt();
      delay (5);
      //      Serial.println("asar oke");
    }
    else if (dataSrl [1] == 'M' and dataSrl [2] == 'G') {
      maghrib = dataSrl.substring(3, dataSrl.length()).toInt();
      delay (5);
      //      Serial.println("magrib oke");
    }
    else if (dataSrl [1] == 'I' and dataSrl [2] == 'S') {
      isya = dataSrl.substring(3, dataSrl.length()).toInt();
      delay (5);
      //      Serial.println("isya oke");
      //      exits = 1;
    }
  }
  else if (dataSrl[0] == 'D' and dataSrl [1] == 'T' and dataSrl [2] == 'E') {
    dayDate = dataSrl.substring(3, dataSrl.length());
    delay (5);
    exits = 1;
  }
}

void ping() {
  Serial.print("PNG");
  delay(500);
}
