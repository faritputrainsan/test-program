#include<SoftwareSerial.h>

SoftwareSerial serial(3, 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  delay (1000);
  serial.write("TES");
  delay (3000);
}
