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

#define WIDTH  128// panjang led matrix
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
 runningText("Selamat datang disini");
jadwal("04:21","04:31","12:00","15:12","17:30","18:45");
//ronn.setFont(B_STD);
// ronn.printText("Animation Demo",0,0);delay(500);
// ronn.clearSlice_R(0,8,64,16);
}


void runningText(char* TEXT){
  ronn.setFont(B_STD);
  ronn.scrollText_LR(TEXT, 0, 0, WIDTH, 20);delay(3000);
}

void jadwal(String imsak ,String subuh ,String dhuhur  ,String asar ,String maghrib  ,String isya  ){
    
  ronn.clear_D();
  ronn.setFont(font_NEW);
  ronn.scrollText_D(imsak+"    "+subuh+"    "+dhuhur+"    "+asar+"    "+maghrib+"    "+isya, 0, 1 );
  buff.fillRect(40, 0, 1, 16, 1);
  buff.fillRect(83, 0, 1, 16, 1);
//  ronn.scrollText_D("06:30", 43, 0, 64 - 11);
  ronn.scrollText_D(imsak, 86, 1, 64 - 11);
  
  for (int i = 1; i <= 5; i++) {
    delay(400);
    buff.fillRect(18, 0, 2, 14, 0);
    delay(600);
    ronn.printText(":", 18, 0);
  }
  ronn.clear_L();delay(1000);
}

void iqomah(){
  
}

void tanggal(){
  
}
