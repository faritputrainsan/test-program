int x;
int y;
int latchPin1 = 3; //Arduino pin connected to blue 12 RCLK of 74HC595
int clockPin1 = 4; //Arduino pin connected to green 11 SRCLK of 74HC595
int dataPin1 =2;  //Arduino pin connected to violet 14 SER of 74HC595

//-- Rows (Positive Anodes) --
int latchPin2 = 6; //Arduino pin connected to yellow Latch 12 RCLK of 74HC595
int clockPin2 = 5; //Arduino pin connected to white Clock 11 SRCLK of 74HC595
int dataPin2 = 7;  //Arduino pin connected to grey Data 14 SER of 74HC595

//=== B I T M A P ===
//Bits in this array represents one LED of the matrix
// 8 is # of rows, 7 is # of LED matrix we have
byte bitmap[8][20]; // Change the 7 to however many matrices you want to use.
int numZones = sizeof(bitmap) / 8;
int maxZoneIndex = numZones-1;
int numCols = numZones * 8;

byte alphabets[][5] = {
  {0,0,0,0,0},
  {31, 36, 68, 36, 31},
  {127, 73, 73, 73, 54},
  {62, 65, 65, 65, 34},
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
  pinMode(latchPin1, OUTPUT);
  pinMode(clockPin1, OUTPUT);
  pinMode(dataPin1, OUTPUT);

  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
 
  //-- Clear bitmap --
  for (int row = 0; row > 8; row++) {
    for (int zone = 0; zone <= maxZoneIndex; zone++) {
      bitmap[row][zone] = 1; 
    }
  }
}

//=== F U N C T I O N S ===
// This routine takes whatever we've setup in the bitmap array and display it on the matrix
void RefreshDisplay()
{
  for (int row = 0; row < 8; row++) {
    int rowbit = 1 << row;
    digitalWrite(latchPin2, LOW);  //Hold latchPin LOW for as long as we're transmitting data
    shiftOut(dataPin2, clockPin2, MSBFIRST,~rowbit);   //Transmit data

    //-- Start sending column bytes --
    digitalWrite(latchPin1, LOW);  //Hold latchPin LOW for as long as we're transmitting data

    //-- Shift out to each matrix (zone is 8 columns represented by one matrix)
    for (int zone = maxZoneIndex; zone >= 0; zone--) {
      shiftOut(dataPin1, clockPin1, MSBFIRST, ~bitmap[row][zone]);
    }

    //-- Done sending Column bytes, flip both latches at once to eliminate flicker
    digitalWrite(latchPin1, HIGH);
    digitalWrite(latchPin2, HIGH);

    //-- Wait a little bit to let humans see what we've pushed out onto the matrix --
    delayMicroseconds(500);
    
  }
}

// Converts row and colum to actual bitmap bit and turn it off/on
void Plot(int col, int row, bool isOn)
{
  int zone = col / 8;
  int colBitIndex = x % 8;
  byte colBit = 1 << colBitIndex;
  if (isOn)
    bitmap[row][zone] =  bitmap[y][zone] | colBit;
  else
    bitmap[row][zone] =  bitmap[y][zone] & (colBit);
}
// Plot each character of the message one column at a time, updated the display, shift bitmap left.
void AlphabetSoup()
{
  char msg[] = "BELAJAR RUNNING TEKS DENGAN ARDUINO ";

  for (int charIndex=0; charIndex < (sizeof(msg)-1); charIndex++)
  {
    int alphabetIndex = msg[charIndex] - '@';
    if (alphabetIndex < 0) alphabetIndex=0;
   
    //-- Draw one character of the message --
    for (int col = 0; col < 6; col++)
    {
      for (int row = 0; row < 8; row++)
      {
        bool isOn = 0;
        if (col<5) isOn = bitRead( alphabets[alphabetIndex][col], 7-row ) == 1;
        Plot( numCols-1, row, isOn);
      }
     
      //-- The more times you repeat this loop, the slower we would scroll --
      for (int refreshCount=0; refreshCount < 7; refreshCount++) //change  this value to vary speed
        RefreshDisplay();
      //-- Shift the bitmap one column to left --
      for (int row=0; row<8; row++)
      {
        for (int zone=0; zone < numZones; zone++)
        {
          bitmap[row][zone] = bitmap[row][zone] >> 1;
                    // Roll over lowest bit from the next zone as highest bit of this zone.
          if (zone < maxZoneIndex) bitWrite(bitmap[row][zone], 7,bitRead(bitmap[row][zone+1],0));

        }
      }
    }
  }
}

//=== L O O P ===
void loop() {
  AlphabetSoup();
}
