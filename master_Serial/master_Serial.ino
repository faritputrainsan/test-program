#include <SoftwareSerial.h>


SoftwareSerial serials(2, 3);

byte pin_stat = A3;
byte input = 9;
byte baca_input;
String text ;

void setup() {

  Serial.begin(9600);
  serials.begin(9600);

  pinMode (pin_stat, OUTPUT);
  pinMode (input,INPUT);
  
  // put your setup code here, to run once:

}

void loop() {
baca_input = digitalRead(input);
  if(baca_input == LOW){
    Serial.println("TES");
    digitalWrite(pin_stat, HIGH);
    delay(1000);
    serials.write("STXThis text for announcement and ohter for 250 letters Selamat datang di masjid yasmin III gading");
    delay(1000);
    digitalWrite(pin_stat, LOW);

    
  }
  if (Serial.available()) {
    text = Serial.readString();
    delay(1000);
    digitalWrite(pin_stat, HIGH);
    //    delay(1000);
    serials.write(text.c_str());
    delay(1000);
    digitalWrite(pin_stat, LOW);
    delay(1000);
  }
}
