

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    
    
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.write("TES TExt \n bla bla bla");
  delay (5000);

}
