int strobePin = 2;
int dataPin = 3;
int clockPin = 4;
int strobePin1 = 5;
int dataPin1 = 6;
int clockPin1 = 7;

int scan = 8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(strobePin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(strobePin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < 8; i++) {
    int row = 1 <<  i;
    digitalWrite(strobePin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, row);
    digitalWrite(strobePin1, LOW); //Hold latchPin LOW for as long as we're transmitting data
    //-- Shift out to each matrix (zone is 8 columns represented by one matrix)
   // for (int data = 8; data >= 8; data--) {
      shiftOut(dataPin1, clockPin1, MSBFIRST, 0xf0);
      shiftOut(dataPin1, clockPin1, MSBFIRST, 0x10);
      shiftOut(dataPin1, clockPin1, MSBFIRST, 0x0f);
      
//    }
    digitalWrite(strobePin, HIGH);
    digitalWrite(strobePin1, HIGH);
    delayMicroseconds(50);
//    delay(500);
//    Serial.println(~row);
  }
}
