bool state = 1;
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   state = !state;
   Serial.println(state);
   delay(2000);
   state = state;
   Serial.println(state);
   delay(2000);
}
