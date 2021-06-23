//Pin connected to Strobe (pin 1) of 4094
#define strobePin 5
//Pin connected to Data (pin 2) of 4094
#define dataPin 6
//Pin connected to Clock (pin 3) of 4094
#define clockPin  4

//Pin connected to Strobe (pin 1) of 4094
#define strobePin1 8
//Pin connected to Data (pin 2) of 4094
#define dataPin1 9
//Pin connected to Clock (pin 3) of 4094
#define clockPin1  7


byte segment[] = {0x23, 0x0A, 0x82, 0xC8, 0x48, 0x07, 0x60, 0xC0, 0x69, 0x81};
byte segment1[] = {0x80,0xEC, 0x42, 0x48, 0x2C, 0x18, 0x10, 0xCC, 0x00, 0x08};

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

    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);

     shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);

     shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
     shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
     
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);
    shiftOut(dataPin1, clockPin1, LSBFIRST, segment1[i]);

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
