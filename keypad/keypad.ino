
const byte ROWS = 8; //four rows
const byte COLS = 8; //four columns

int hexaKeys[ROWS][COLS] = {
  {0, 1, 2, 3, 4, 5, 6, 7},
  {8, 9, 1, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 2, 28, 29, 30, 31},
  {3, 33, 34, 35, 36, 37, 38, 39},
  {40, 41, 42, 43, 44, 45, 4, 8},
  {48, 49, 50, 51, 52, 53, 54, 55},
  {56, 57, 58, 59, 60, 61, 62, 63}
};

byte rowPins[ROWS] = {22, 23, 24, 25, 26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3, A4, A5, A6, A7}; //connect to the column pinouts of the keypad


void setup() {
  // put your setup code here, to run once:
  for (int i = 0;i<8;i++){
    pinMode(rowPins[i],OUTPUT);
    pinMode(colPins[i],INPUT);
  }
}

void loop() {
  

}
