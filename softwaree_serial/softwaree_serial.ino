#include <SoftwareSerial.h>


SoftwareSerial blt(8, 9);

String bc;
char dchar[100];
String bb;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  blt.begin(9600);
}

void loop() {
  if (blt.available()) {
    bc = blt.readString();
    Serial.print (bc);

  }
//  int no_idx = 0;
//  char schar;
//
//  schar = blt.peek();
//  if ((schar == 'J') or (schar == 'L')) {
//    while ((schar != '\n') and (no_idx < 200)) {
//      if (blt.available()) {
//        schar = (char)blt.read();
//        dchar [no_idx] = schar;
//        no_idx++;
//               Serial.println(schar);
//      }
//    }
//    dchar [no_idx - 1] = '\0';
//    bb = (String)schar;
//    Serial.println(dchar);
//
//    //isi_jam();
//  }
//
}


//Serial.print (bc.substring(3,8)); senin
//Serial.print (bc.substring(3,9)); selasa
//Serial.print (bc.substring(3,7)); rabu
