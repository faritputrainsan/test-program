

#define l  5
#define d  4
#define c  6


void setup() {
  // put your setup code here, to run once:
  pinMode(l, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
}
unsigned long dip = 0;
unsigned long cm ;
int kedip;
int ic1 ;
int ic2 ;
int ic3 ;
int ic4 ;
void loop() {
  // put your main code here, to run repeatedly:
  cm = millis();
  digitalWrite(l, LOW);

  if (cm - dip >= 50) {
    dip = cm;
    kedip ++;
    if (kedip <= 10) {
      ic1 = 0;
      ic2 = 0;
      ic3 = 0;
      ic4 = 0;

    }
    else if (kedip <= 20) {
      if (kedip >= 20)  kedip = 0;
      ic1 = 255;
      ic2 = 255;
      ic3 = 255;
      ic4 = 255;
    }
  }

  shiftOut(d, c, MSBFIRST, ic4);
  shiftOut(d, c, MSBFIRST, ic3);
  shiftOut(d, c, MSBFIRST, ic2);
  shiftOut(d, c, MSBFIRST, ic1);
  digitalWrite(l, HIGH);
}
