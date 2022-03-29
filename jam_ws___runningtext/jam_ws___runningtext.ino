/* HUB08 (matrix led) to ARDUINO pin connection
 * LA / A    -> Digital Pin 4
 * LB / B    -> Digital Pin 5
 * LC / C    -> Digital Pin 6
 * LD / D    -> Digital Pin 7
 * S / CLK   -> Digital Pin 13
 * R1 / R    -> Digital Pin 11
 * OE / EN   -> Digital Pin 3
 * L / LAT / STB -> Digital Pin 2
 */


#include <SPI.h>
#include <avr/pgmspace.h>
#include "HUB08SPI.h"
#include "TimerOne.h"
#include "Buffer.h"

#define WIDTH  64// panjang led matrix
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
  display.begin(displaybuf,WIDTH, HEIGHT);
  Timer1.initialize(250);
  Timer1.attachInterrupt(refresh);
  display.setBrightness(2000);
  buff.clear();
}


void loop() {
  // put your main code here, to run repeatedly:
// runningText("test Run");
jadwal();
//ronn.setFont(B_STD);
// ronn.printText("Animation Demo",0,0);delay(500);
// ronn.clearSlice_R(0,8,64,16);
}


void runningText(char* TEXT){
  ronn.setFont(B_STD);
  ronn.scrollText_LR(TEXT, 0, 0, WIDTH, 20);
}

void jadwal(){

//   ronn.clear_U(0,8,64,8,CLEAR);delay(300);
//    ronn.scrollText_U("06:30:55",11,8,64-11);
//    delay(1000-160);
//    for(int i=6;i<=9;i++){
//      ronn.scrollText_U(String(i),36+11,8,5);
//      delay(1000-160);
//    }
//    ronn.scrollText_U("00",30+11,8,11);
//    ronn.scrollText_U("1",21+11,8,5);

    
//    ronn.clear_U();
    
  ronn.clear_D();
  ronn.setFont(B_7SEGMENT);
  ronn.scrollText_D("06:30", 9, 0, 64 - 11);
  for (int i = 1; i <= 5; i++) {
    delay(400);
    buff.fillRect(31, 0, 2, 8, 0);
    delay(600);
    ronn.printText(":", 31, 0);
  }
//  ronn.clear_R();
}
