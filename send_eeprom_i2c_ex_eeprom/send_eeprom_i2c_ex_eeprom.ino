#include <Wire.h>
#include <I2C_eeprom.h>

//1. Alamat 24LC32 = 0x57

#define ADD_I2C 0x57

//Device identifier
I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

int len_mosName = 60;
int len_text = 300;

int mosName_add = 0;
int text_add = 61;

byte output = A3;
int input = 9;
byte r_input;

int lenText = 256;

String textSerial;

String Texts = "test delete char";

int sbh = 1010, lhr = 555, asr = 666, mgr = 999, isy = 340;

//#define pinSDA D5
//#define pinSCL D6

void setup() {

  Serial.begin(9600);

  eeprom.begin();
  if (!eeprom.isConnected()) {
    Serial.print("ERROR: can't find eeprom\nstoped");
    while (1);
  }
  //  Wire.begin();
  delay(100);
  pinMode (output, OUTPUT);
  digitalWrite (output, HIGH);
  delay(10);
  pinMode (input, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  r_input = digitalRead(input);

  if (r_input == LOW) {
    char buffer[40];
    sprintf(buffer, "JWL\n%d\n%d\n%d\n%d\n%d\n", sbh, lhr, asr, mgr, isy );
    //    digitalWrite (output, LOW);
    //    writetxt(text_add, Texts, lenText);
    Serial.print(buffer);
    delay (1000);
    //    readeep(text_add, lenText);
    //    digitalWrite (output, HIGH);
  }
}

char Ch_prm[250];

void serialEvent() {
  String text_srl;
  char rchar;
  char prm[200];
  int chr_idx = 0;
  rchar = Serial.peek();
  if (rchar == 'S' ) {
    while ((rchar != '\n') and (chr_idx < 305)) {
      while (Serial.available()) {
        text_srl = Serial.readString();
        delay(1000);
        rchar = (char)Serial.read();
        Serial.println(text_srl);
        delay(1000);
        prm[chr_idx] = rchar;
        chr_idx ++;
      }
    }
    prm[chr_idx - 1] = '\0';
    //    saveState();
    //    int addres;
    //    String msges;
    //    if (text_srl.substring(0,1) == 'S') {
    //      if (text_srl.substring(1,2) == 'N' and text_srl.substring(2,3) == 'M') {
    //        addres = mn_add;
    //      }
    //      else if (text_srl.substring(1,2) == 'T' and text_srl.substring(2,3) == 'X') {
    //        addres = text_add;
    //      }
    //      //    else if (prm[1] == 'T' and prm[2] == '1') {
    //      addres = text1_add;
    //    }
    //      text_srl
    //      msges = text_srl.substring(3, text_srl.length());
    //      delay(100);
    //      Write_text(msges, addres);
    //      delay (200);
    //    }
    //    text_250 = read_Text(text_add);
    //    Serial.println (text_250);
  }





  //  if (Serial.available()) {
  //    textSerial = Serial.readString();
  //    delay(100);
  //    writetxt(0,    textSerial,      lenText);
  //    /////(address, text data, panjang arrays)
  //    delay(1000);
  //
  //  }
}

void writetxt(unsigned int addres, String text, int length) {

  //  Set block plotter on eeprom use library
  eeprom.setBlock(addres, 0, length);
  /////////////////////////////////////

  // create String to char arrays
  int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  ////////////////////////////

  //  char to read data array from eeprom

  ////////////////////////////////////////

  /////////////////(address     , data              , length text)
  eeprom.writeBlock(addres      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////

  //  read data from eeprom using for loop
}
void readeep(unsigned int addres, int length) {
  char data[length];
  for (int i = 0; i < length; i++) {
    //    if (i % 10 == 0 ) SERIAL_OUT.println();
    //    SERIAL_OUT.print(' ');
    data[i] = eeprom.readByte( addres + i );
    //    SERIAL_OUT.print((char)ee.readByte(i));
  }
  ////////////////////////////////////////

  //char array to data string

  Serial.println((String)data);
}
