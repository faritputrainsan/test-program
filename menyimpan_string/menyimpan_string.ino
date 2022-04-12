#include <EEPROM.h>

String a = "AKU=KAMU dia ya dia aja hahahaha tes panjang text yang akan di save ke dalam eeprom dan bagaimana size text itu di store ke dalam memori eeprom ya 200 text apakah eppromnya cukup atau tidak, masih kurang dari 200 tambah jadi 250 character hemmm 5lagi berapa penggunaan eeprom ini huruf kok aneh sekali";
//String a2 = "MENCOBA menyimpan 100 karakter kedalam dua variable berbeda kurang dari 100 character masih kurang  ";
String a3 = "Message Text";
String b;
String b2;
int y;
byte x = 100;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  EEPROM.put(0, a);
//  EEPROM.put(10, a2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(a2.length());
//  Serial.println(EEPROM.length());
//  y=EEPROM.read(1023);
  EEPROM.get(10, b2);
//  EEPROM.get(10, b2);
//  Serial.println(y);
  delay(1000);
  Serial.println(b2);
//  Serial.println(b2);
  delay (5000);
}
