#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
   sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed  

}

//intrerupt on receive
ISR (USART_RX_vect){
   

}

//use eeprom function to read/write to EEPROM
void loop() {
//   Serial.print("10000");
}
