#define strobePin 4
//Pin connected to Data (pin 2) of 4094
#define dataPin  2 
//Pin connected to Clock (pin 3) of 4094
#define clockPin  3

byte segChar[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};


void setup() {
  // put your setup code here, to run once:
pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x;
  x++;
digitalWrite(strobePin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, segChar[x]);
  digitalWrite(strobePin, HIGH);
}
