#include <I2C_eeprom.h>

#define ADD_I2C 0x57

I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  eeprom.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(text_read( 160,  123));
  delay (1000);
}

void WriteText(unsigned int address, String text, int length) {
  /////////////////////////////////////
  eeprom.setBlock(address, '\0', length);
  /////////////////////////////////////

  ////////////////////////////////
  // create String to char arrays
  unsigned int len = text.length() + 1;
  char data2[len];
  text.toCharArray(data2, len);
  ////////////////////////////////

  /////////////////(address      , data              , length text)
  eeprom.writeBlock(address      , (uint8_t *) &data2, sizeof(data2));
  //////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
String text_read( unsigned int length,  unsigned int address) {
  char data[length];
  for (unsigned int i = 0; i <  length; i++) {
    data[i] = eeprom.readByte( address + i  );
  }
  ////////////////////////////////////////
  // kembalikan String
  // merubah char ke String
  return (String)data;
}
