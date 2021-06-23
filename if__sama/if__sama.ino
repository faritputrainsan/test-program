int x;
int Ix = 0;

unsigned long count = 5000;
unsigned long curentCount = 0;


void setup() {

  Serial.begin (9600);
  x = Ix - 1;

}

void loop() {
  unsigned long mil =  millis();

  while (mil - curentCount >= count){
    curentCount = mil;
    Ix ++;
    Serial.println ("masuk ke while" );
    Serial.println (Ix );
    Serial.println (x );
  }
  

  if ( x != Ix){
    x = Ix;
   Serial.println ("berhasil masuk ke \"IF" );
   Serial.println (Ix );
    Serial.println (x );
  }
  

}
