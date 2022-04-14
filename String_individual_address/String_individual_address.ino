#include <EEPROM.h>
//String greeting = "hello world";
//int addr = 0;

int text_length = 200;
int name_addrs = 0;
int name_length = 50;
int text_addrs = name_length + 1;


void setup() {
  Serial.begin(115200);

  Serial.println("");
  Serial.println("");

//  Serial.print("Word to write: ");
//  Serial.println(greeting);
//  Serial.print("Word length to write: ");
//  Serial.println(greeting.length());

  // Write to EEPROM
  

//  writeTXT(greeting,addr);

  Serial.println("");
  Serial.println("Begin reading back the array: ");
  readTXT(name_addrs);
}

void loop() {}


void serialEvent(){
  char rchar;
  String msg;
//  addr = 0;
  rchar = Serial.peek();
  if ((rchar == 'M') || (rchar == 'T')) {
    
    if (Serial.available()) {
      msg = Serial.readString();
      writeTXT(msg, name_addrs);
      Serial.println("ok");
      readTXT(name_addrs);
    }
  }

  else if (rchar == 'J') {

    ///
    //    Serial.println(data_jadwal);
  }
}
void writeTXT(String msg, int addrs){

  Serial.println(msg); 
   Serial.print("panjang: "); 
   Serial.println(msg.length()); 
  Serial.print("Address: "); 
  Serial.println(addrs); 
  
  for (int index = addrs; index < msg.length(); index++) {
    EEPROM.update(addrs, msg[index]);
    
    delay(10);

    Serial.print("Writing ");
    Serial.print(msg[index]);
    Serial.print(" in address ");
    Serial.println(addrs);
    addrs++;
  }
  
  EEPROM.write(addrs, '\0');
  EEPROM.read(addrs);
}

void readTXT(int addrs){
  char readChar = "";
  String readGreeting = "";

  while (readChar != '\0') {
    Serial.print("Reading ");

    readChar = EEPROM.read(addrs);
    delay(10);
    if (readChar != '\0') {
      readGreeting += readChar;
    }

    addrs++;

    Serial.print(readChar);
    Serial.print(" in address ");
    Serial.println(addrs);
  }

  Serial.print("Final string read from EEPROM: ");
  Serial.println(readGreeting);
}
