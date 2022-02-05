
//Pin connected to Strobe (pin 1) of 4094
#define strobePin 2
//Pin connected to Data (pin 2) of 4094
#define dataPin 4
//Pin connected to Clock (pin 3) of 4094
#define clockPin  3

#define strobePin1 8
//Pin connected to Data (pin 2) of 4094
#define dataPin1 9
//Pin connected to Clock (pin 3) of 4094
#define clockPin1  7


byte segment[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};


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
  for (int i = 0 ; i < 8; i++) {
    digitalWrite(strobePin, LOW);
    digitalWrite(strobePin1, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);

//    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
//    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
//    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
//    shiftOut(dataPin1, clockPin1, LSBFIRST, segment[i]);
//
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);

    digitalWrite(strobePin, HIGH);
    digitalWrite(strobePin1, HIGH);
    delay (2000);

  }

}
