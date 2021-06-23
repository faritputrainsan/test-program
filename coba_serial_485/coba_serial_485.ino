int control = 2;


void setup() {
  Serial.begin(9600);
  pinMode(control, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(control, HIGH);
  Serial.write("0FF");
  delay(5000);
  digitalWrite(control, LOW);
}
