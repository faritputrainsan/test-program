#include <EEPROM.h>

String a ="AKU=KAMU";

String b;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  EEPROM.put(0,a);
}

void loop() {
  // put your main code here, to run repeatedly:
 EEPROM.get(0,b);
 Serial.println(b); 
 delay (1000);
}
