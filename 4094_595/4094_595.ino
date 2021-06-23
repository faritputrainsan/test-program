
//Pin connected to Strobe (pin 1) of 4094
#define strobePin 5
//Pin connected to Data (pin 2) of 4094
#define dataPin 6
//Pin connected to Clock (pin 3) of 4094
#define clockPin  4

#define strobePin1 8
//Pin connected to Data (pin 2) of 4094
#define dataPin1 9
//Pin connected to Clock (pin 3) of 4094
#define clockPin1  7


byte segment[] = {0x10, 0x7b, 0x24, 0x21, 0x43, 0x81, 0x80, 0x3b, 0x08, 0x01};

void setup() {
  // put your setup code here, to run once:

  pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);

  pinMode( strobePin1 , OUTPUT);
  pinMode( dataPin1    , OUTPUT);
  pinMode( clockPin1   , OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  //
  for (int i = 0 ; i < 10; i++) {
    digitalWrite(strobePin, LOW);
    digitalWrite(strobePin1, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);

    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);

    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);

    digitalWrite(strobePin, HIGH);
    digitalWrite(strobePin1, HIGH);
    delay (500);

  }

}
