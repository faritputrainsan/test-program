int x = 0x10;
#define d  A0
#define clk  A1
#define lac A2

int y[]= {0x37,0x42,0x12,0x34,0x18,0x08,0x33,0x00,0x10,0
  
};
void setup() {
  // put your setup code here, to run once:
  pinMode(d, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(lac, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(lac, LOW);
  shiftOut(d, clk, MSBFIRST, x);
  
  digitalWrite(lac, HIGH);
}
