int pin [] = {
  1, A3, A2, A1
};

int inp = 0;
int timer(10);
int jumlah = 4;
void setup() {
  // put your setup code here, to run once:
  for ( int y = 0;  y < jumlah; y++) {
    pinMode(pin[y], OUTPUT );
  }
  pinMode (inp, INPUT);
}

void loop() {
  for (int thisPin = 0; thisPin < jumlah; thisPin++) {
    // turn the pin on:
    digitalWrite(pin[thisPin], HIGH);
    int bc = digitalRead (inp);
    if (bc == HIGH)rem();
    delay(timer);
    // turn the pin off:
    digitalWrite(pin[thisPin], LOW);
  }
}

void rem() {
  int x= 1;
  while (x==1) {
    int bc = digitalRead (inp);
    if (bc == LOW) x= 0;
    //if (bc == HIGH)rem();
    digitalWrite(pin[0], HIGH);
    digitalWrite(pin[1], HIGH);
    digitalWrite(pin[2], HIGH);
    digitalWrite(pin[3], HIGH);
    delay (10);

    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], LOW);
    digitalWrite(pin[2], LOW);
    digitalWrite(pin[3], LOW);
    delay (5);
  }
}
