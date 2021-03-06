#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

#define data_col 2
#define clk_col 4
#define lat_col 3

#define data_row 7
#define clk_row 5
#define lat_row 6

int stepX , stepY;
byte tinggi = 8;
int lebar = 152;

#define textChar
int col,row;

int length;

int data;

char text [textChar]= "Test Running Text";

const unsigned char font[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // sp
  0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,  // !
  0x00, 0x07, 0x07, 0x00, 0x00, 0x00,  // "
  0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00,  // #
  0x12, 0x2a, 0x7f, 0x2a, 0x24, 0x00,  // $
  0x46, 0x26, 0x10, 0xc8, 0xc4, 0x00,  // %
  0x50, 0x22, 0x55, 0x49, 0x36, 0x00,  // &
  0x00, 0x00, 0x03, 0x05, 0x00, 0x00,  // '
  0x00, 0x41, 0x22, 0x1c, 0x00, 0x00,  // (
  0x00, 0x1c, 0x22, 0x41, 0x00, 0x00,  // )
  0x14, 0x08, 0x3E, 0x08, 0x14, 0x00,  // *
  0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,  // +
  0x00, 0x00, 0x30, 0x50, 0x00, 0x00,  // ,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x00,  // -
  0x00, 0x00, 0x60, 0x60, 0x00, 0x00,  // .
  0x02, 0x04, 0x08, 0x10, 0x20, 0x00,  // /
  //  0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xFF,  // /
  0x3E, 0x45, 0x49, 0x51, 0x3E, 0x00,  // 0
  0x00, 0x40, 0x7F, 0x42, 0x00, 0x00,  // 1
  0x46, 0x49, 0x51, 0x61, 0x42, 0x00,  // 2
  0x31, 0x4B, 0x45, 0x41, 0x21, 0x00,  // 3
  0x10, 0x7F, 0x12, 0x14, 0x18, 0x00,  // 4
  0x39, 0x45, 0x45, 0x45, 0x27, 0x00,  // 5
  0x30, 0x49, 0x49, 0x4A, 0x3C, 0x00,  // 6
  0x03, 0x05, 0x09, 0x71, 0x01, 0x00,  // 7
  0x36, 0x49, 0x49, 0x49, 0x36, 0x00,  // 8
  0x1E, 0x29, 0x49, 0x49, 0x06, 0x00,  // 9
  0x00, 0x00, 0x36, 0x36, 0x00, 0x00,  // :
  0x00, 0x00, 0x36, 0x56, 0x00, 0x00,  // ;
  0x08, 0x14, 0x22, 0x41, 0x00, 0x00,  // <
  0x14, 0x14, 0x14, 0x14, 0x14, 0x00,  // =
  0x00, 0x41, 0x22, 0x14, 0x08, 0x00,  // >
  0x06, 0x09, 0x51, 0x01, 0x02, 0x00,  // ?
  0x3E, 0x51, 0x59, 0x49, 0x32, 0x00,  // @
  0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,  // A
  0x36, 0x49, 0x49, 0x49, 0x7F, 0x00,  // B
  //  0xF7, 0x94, 0x94, 0x94, 0x63, 0x00,  // B
  0x22, 0x41, 0x41, 0x41, 0x3E, 0x00,  // C
  0x1C, 0x22, 0x41, 0x41, 0x7F, 0x00,  // D
  0x41, 0x49, 0x49, 0x49, 0x7F, 0x00,  // E
  0x01, 0x09, 0x09, 0x09, 0x7F, 0x00,  // F
  0x7A, 0x49, 0x49, 0x41, 0x3E, 0x00,  // G
  0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,  // H
  0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,  // I
  0x01, 0x3F, 0x41, 0x40, 0x20, 0x00,  // J
  0x41, 0x22, 0x14, 0x08, 0x7F, 0x00,  // K
  0x40, 0x40, 0x40, 0x40, 0x7F, 0x00,  // L
  0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00,  // M
  0x7F, 0x10, 0x08, 0x04, 0x7F, 0x00,  // N
  0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,  // O
  0x06, 0x09, 0x09, 0x09, 0x7F, 0x00,  // P
  0x5E, 0x21, 0x51, 0x41, 0x3E, 0x00,  // Q
  0x46, 0x29, 0x19, 0x09, 0x7F, 0x00,  // R
  0x31, 0x49, 0x49, 0x49, 0x46, 0x00,  // S
  0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,  // T
  0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,  // U
  0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00,  // V
  0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00,  // W
  0x63, 0x14, 0x08, 0x14, 0x63, 0x00,  // X
  0x07, 0x08, 0x70, 0x08, 0x07, 0x00,  // Y
  0x43, 0x45, 0x49, 0x51, 0x61, 0x00,  // Z
  0x00, 0x41, 0x41, 0x7F, 0x00, 0x00,  // [
  0x55, 0x2A, 0x55, 0x2A, 0x55, 0x00,  // slash
  0x00, 0x7F, 0x41, 0x41, 0x00, 0x00,  // ]
  0x04, 0x02, 0x01, 0x02, 0x04, 0x00,  // ^
  0x40, 0x40, 0x40, 0x40, 0x40, 0x00,  // _
  0x00, 0x00, 0x04, 0x02, 0x01, 0x00,  // '
  0x78, 0x54, 0x54, 0x54, 0x20, 0x00,  // a
  0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,  // b
  0x20, 0x44, 0x44, 0x44, 0x38, 0x00,  // c
  0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,  // d
  0x18, 0x54, 0x54, 0x54, 0x38, 0x00,  // e
  0x02, 0x01, 0x09, 0x7E, 0x08, 0x00,  // f
  0x3E, 0x52, 0x52, 0x52, 0x0C, 0x00,  // g
  0x78, 0x04, 0x04, 0x08, 0x7F, 0x00,  // h
  0x00, 0x40, 0x7D, 0x44, 0x00, 0x00,  // i
  0x3D, 0x44, 0x40, 0x20, 0x00, 0x00,  // j
  0x44, 0x28, 0x10, 0x7F, 0x00, 0x00,  // k
  0x00, 0x40, 0x7F, 0x41, 0x00, 0x00,  // l
  0x78, 0x04, 0x18, 0x04, 0x7C, 0x00,  // m
  0x78, 0x04, 0x04, 0x08, 0x7C, 0x00,  // n
  0x38, 0x44, 0x44, 0x44, 0x38, 0x00,  // o
  0x08, 0x14, 0x14, 0x18, 0x7C, 0x00,  // p
  0x7C, 0x14, 0x14, 0x14, 0x08, 0x00,  // q
  0x08, 0x04, 0x04, 0x08, 0x7C, 0x00,  // r
  0x20, 0x54, 0x54, 0x54, 0x48, 0x00,  // s
  0x20, 0x40, 0x44, 0x3F, 0x04, 0x00,  // t
  0x7C, 0x20, 0x40, 0x40, 0x3C, 0x00,  // u
  0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00,  // v
  0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,  // w
  0x44, 0x28, 0x10, 0x28, 0x44, 0x00,  // x
  0x3C, 0x50, 0x50, 0x50, 0x0C, 0x00,  // y
  0x44, 0x4C, 0x54, 0x64, 0x44, 0x00,  // z
  0x18, 0x3C, 0x78, 0x3C, 0x18, 0x00,  // {  ini lambang hati
  0xC6, 0xEE, 0xFE, 0xEE, 0xC6, 0x00,  // | ini lambang hourglass
  0x00, 0x06, 0x09, 0x09, 0x06, 0x00,  // } ini lambang derajat
  0x10, 0x20, 0x10, 0x08, 0x10, 0x00   // ~
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(data_col , OUTPUT);
  pinMode(clk_col , OUTPUT);
  pinMode(lat_col , OUTPUT);

  pinMode(data_row , OUTPUT);
  pinMode(clk_row , OUTPUT);
  pinMode(lat_row , OUTPUT);

  length = strlen(text);
}

void loop() {
 textRunning ();
}

void textRunning () {
 for(int rows=0;rows <= tinggi; rows++ ){
    row = 1 << rows;
    digitalWrite(lat_row,LOW);
    shiftOut(data_row, clk_row, MSBFIRST, row);

    Serial.println(row);
    digitalWrite(lat_row, HIGH);
 }

 data = pgm_read_byte(&(font[((text[textChar] - ' ' ))]));
 Serial.println (data);
 
}

void textStatic(char text) {

}

void refreshDisplays() {

}
