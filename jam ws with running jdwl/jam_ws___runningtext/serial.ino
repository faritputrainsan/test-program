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
    Serial.print((String)dchar);
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
