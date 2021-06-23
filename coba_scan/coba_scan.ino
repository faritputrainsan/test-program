int strobePin = 2;
int dataPin = 3;
int clockPin = 4;
int strobePin1 = 5;
int dataPin1 = 6;
int clockPin1 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(strobePin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(strobePin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    int row = 1 <<  i;
    digitalWrite(strobePin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, row);
    //    delayMicroseconds(300);
    digitalWrite(strobePin1, LOW);//Hold latchPin LOW for as long as we're transmitting data

    shiftOut(dataPin1, clockPin1, MSBFIRST, 0x00);
    digitalWrite(strobePin1, HIGH);
    digitalWrite(strobePin, HIGH);
    //    cleard();
            delay(1000);
//    delayMicroseconds(200);
  }

}
