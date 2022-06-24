
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 0;
  while (x < 10) {
    Serial.print("while x: ");
    Serial.println(x);
    x ++;
    delay(1000);
    //    hasil 0-9
  }

  for (int y = 0; y < 10; y++) {
    Serial.print("for y: ");
    Serial.println(y);
    delay(1000);
    //    hasil 0-9
  }
  int y = 0;
  do {
    Serial.print("do while y: ");
    Serial.println(y);
    y++;
    delay(1000);
    //    hasil 0-10
  } while (y < 10);
}
