#include <Wire.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <RtcDS3231.h>



/*--------------------- RGB DISPLAY PINS -------------------------*/
#define A_PIN  16 //D16
#define B_PIN  14 //D14
#define C_PIN  4  //D4
#define D_PIN  27 //D27
#define E_PIN  -1 //

#define R1_PIN  19//D19
#define R2_PIN  5 //D5
#define G1_PIN  13//D13
#define G2_PIN  12//D12
#define B1_PIN  18//D18
#define B2_PIN  17//D17

#define CLK_PIN  2  //D2
#define LAT_PIN  26//D26
#define OE_PIN  15 //D15

/*--------------------- MATRIX LILBRARY CONFIG -------------------------*/
#define PANEL_RES_X 64      // Number of pixels wide of each INDIVIDUAL panel module. 
#define PANEL_RES_Y 32     // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 1      // Total number of panels chained one to another
 

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
