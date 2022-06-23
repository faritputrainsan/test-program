void serialEvent() {
  char bcar;
  int idx = 0;

  bcar = Serial.peek();
  if ((bcar == 'J') or (bcar == 'L')) {
    while ((bcar != '\n') and (idx < 80)){
      if (Serial.available()) {
        bcar = (char)Serial.read();
        dchar [idx] = bcar;
        idx++;
      }
    }
    Serial.print((String)dchar);
    delay(100);
    dchar [idx - 1] = '\0';
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
  Serial.print("Ping");
  delay(500);
}
