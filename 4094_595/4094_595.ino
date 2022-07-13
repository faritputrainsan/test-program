
//Pin connected to Strobe (pin 1) of 4094
#define strobePin 11
//Pin connected to Data (pin 2) of 4094
#define dataPin 12
//Pin connected to Clock (pin 3) of 4094
#define clockPin  10

//#define strobePin1 8
////Pin connected to Data (pin 2) of 4094
//#define dataPin1 9
////Pin connected to Clock (pin 3) of 4094
//#define clockPin1  7


//byte segment[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};

byte segment[] = {0xbf, 0x0a, 0xdd, 0x5f, 0x6b, 0x77, 0xf7, 0x1a, 0xff, 0x7f};

byte tes[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//                   c     d      b     a    f     g      e
// 0xC6  0xf3

void setup() {
  // put your setup code here, to run once:

  pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);

//  pinMode( strobePin1 , OUTPUT);
//  pinMode( dataPin1    , OUTPUT);
//  pinMode( clockPin1   , OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  //
  for (int i = 0 ; i < 8; i++) {
    digitalWrite(strobePin, LOW);
//    digitalWrite(strobePin1, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0xf3);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);
//    shiftOut(dataPin, clockPin, LSBFIRST, segment[i]);

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
//    digitalWrite(strobePin1, HIGH);
    delay (2000);

  }

}
