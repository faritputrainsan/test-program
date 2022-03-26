#include <SPI.h>
#include <avr/pgmspace.h>
#include "HUB08SPI.h"
#include "TimerOne.h"
#include "Buffer.h"



#define WIDTH 64 // panjang led matrix
#define HEIGHT 16 // tinggi led matrix


HUB08SPI display;

uint8_t displaybuf[WIDTH * HEIGHT /8];
Buffer buff(displaybuf, WIDTH, 16);

#include "ronnAnimation.h"

void refresh(){
  display.scan();
}

void setup() {

  Serial.begin(9600);
  display.begin(displaybuf,WIDTH, HEIGH);
  Timer1.initialize(250);
  Timer1.attachInterrupt(refresh);
  display.setBrightness(2000);
  buff.clear();
}


void loop() {
  // put your main code here, to run repeatedly:

}


void runningText(String TEXT){
  
}
