int x;
int y;
int latchPin1 = 5; //Arduino pin connected to blue 12 RCLK of 74HC595
int clockPin1 = 6; //Arduino pin connected to green 11 SRCLK of 74HC595
int dataPin1 = 7; //Arduino pin connected to violet 14 SER of 74HC595
//-- Rows (Positive Anodes) --
int latchPin2 = 9; //Arduino pin connected to yellow Latch 12 RCLK of 74HC595
int clockPin2 = 10; //Arduino pin connected to white Clock 11 SRCLK of 74HC595
int dataPin2 = 8; //Arduino pin connected to grey Data 14 SER of 74HC595
//=== B I T M A P ===
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 7 is # of LED matrix we have
byte bitmap[8][7]; // Change the 7 to however many matrices you want to use.
int numZones = sizeof(bitmap) / 8;
int maxZoneIndex = numZones - 1;
int numCols = numZones * 8;
byte alphabets[][5] = {
  {0, 0, 0, 0, 0},
  {31, 36, 68, 36, 31},//A
  {127, 73, 73, 73, 54},//B
  {62, 65, 65, 65, 34},//C
  {127, 65, 65, 34, 28},
  {127, 73, 73, 65, 65},
  {127, 72, 72, 72, 64},
  {62, 65, 65, 69, 38},
  {127, 8, 8, 8, 127},
  {0, 65, 127, 65, 0},
  {2, 1, 1, 1, 126},
  {127, 8, 20, 34, 65},
  {127, 1, 1, 1, 1},
  {127, 32, 16, 32, 127},
  {127, 32, 16, 8, 127},
  {62, 65, 65, 65, 62},
  {127, 72, 72, 72, 48},
  {62, 65, 69, 66, 61},
  {127, 72, 76, 74, 49},
  {50, 73, 73, 73, 38},
  {64, 64, 127, 64, 64},
  {126, 1, 1, 1, 126},
  {124, 2, 1, 2, 124},
  {126, 1, 6, 1, 126},
  {99, 20, 8, 20, 99},
  {96, 16, 15, 16, 96},
  {67, 69, 73, 81, 97},
};
//=== S E T U P ===
void setup() {
  Serial.begin(9600);
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
  //-- Clear bitmap --
  for (int row = 0; row > 8; row++) {
    for (int zone = 0; zone <= maxZoneIndex; zone++) {
      bitmap[row][zone] = 0;
    }
  }
}
//=== F U N C T I O N S ===
// This routine takes whatever we've setup in the bitmap array and display it on the matrix
void RefreshDisplay(){
  for (int row = 0; row < 8; row++) {
    int rowbit = 1 << row;
    digitalWrite(latchPin2, LOW); //Hold latchPin LOW for as long as we're transmitting data
    shiftOut(dataPin2, clockPin2, MSBFIRST, rowbit); //Transmit data
    //-- Start sending column bytes --
    digitalWrite(latchPin1, LOW); //Hold latchPin LOW for as long as we're transmitting data
    //-- Shift out to each matrix (zone is 8 columns represented by one matrix)
    for (int zone = maxZoneIndex; zone >= 0; zone--) {
      shiftOut(dataPin1, clockPin1, MSBFIRST, bitmap[row][zone]);
    }
    //-- Done sending Column bytes, flip both latches at once to eliminate flicker
    digitalWrite(latchPin1, HIGH);
    digitalWrite(latchPin2, HIGH);
    //-- Wait a little bit to let humans see what we've pushed out onto the matrix --
    delayMicroseconds(500);
    Serial.println(rowbit);
  }
}
// Converts row and colum to actual bitmap bit and turn it off/on
void loop(){
  RefreshDisplay();
}
