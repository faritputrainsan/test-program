//Pin connected to Strobe (pin 1) of 4094
#define strobePin 15
//Pin connected to Data (pin 2) of 4094
#define dataPin 2
//Pin connected to Clock (pin 3) of 4094
#define clockPin  0

//Pin connected to Strobe (pin 1) of 4094
//#define strobePin1 8
////Pin connected to Data (pin 2) of 4094
//#define dataPin1 9
////Pin connected to Clock (pin 3) of 4094
//#define clockPin1  7

//byte segment[] = {0x39, 0xF8, 0x00, 0x00, 0x00, 0x2C, 0x00, 0xFF, 0xFF, 0xFF};
//T-Z
//byte segment[] = {0x1A, 0xB9, 0x8B, 0x8E, 0x8A, 0x78, 0x0B, 0x0E, 0x9B, 0x1C};
//K-S
//byte segment[] = {0x48, 0x38, 0x79, 0x68, 0x09, 0x1B, 0x98, 0x3A, 0xEE, 0xE8};
//a-j
//byte segment[] = {0x80, 0xEE, 0x49, 0x4C, 0x2E, 0x1C, 0x18, 0xC6, 0x08, 0x04};
//0-9

byte segment[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xFF, 0xFF};
//byte segment1[] = {0x80,0xEC, 0x42, 0x48, 0x2C, 0x18, 0x10, 0xCC, 0x00, 0x08};

const unsigned char huruf[] PROGMEM =
{ 0x04, 0x03, 0x29, 0x06, 0x20, 0x61, 0x80, 0x43, 0xCE, 0x0E, 0x41,
  //a/////b/////c/////d/////e/////f/////g/////h/////i/////j/////k
  //0/////1/////2/////3/////4/////5/////6/////7/////8/////9/////10
  0x2B, 0x68, 0xC8, 0x48, 0x07, 0x60, 0xC0, 0x69, 0x81, 0x23, 0x0A, 0x82
  //l/////m1////m2////n/////o/////p/////q/////r/////s/////t/////u/////y
  //11////12///13/////14////15////16////17////18////19////20////21////22
};

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
  for (int i = 0 ; i < 10; i++) {
    digitalWrite(strobePin, LOW);
//    digitalWrite(strobePin1, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);

    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i]);

    digitalWrite(strobePin, HIGH);
//    digitalWrite(strobePin1, HIGH);
    delay (500);

  }

}
