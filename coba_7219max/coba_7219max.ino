//We always have to include the library
#include "LedControl.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/
LedControl lc = LedControl(12, 10, 11, 4);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 250;

void setup() {
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  lc.shutdown(1, false);
  lc.shutdown(2, false);
  lc.shutdown(3, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 6);
  lc.setIntensity(1, 6);
  lc.setIntensity(2, 6);
  lc.setIntensity(3, 6);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}


/*
  This method will display the characters for the
  word "Arduino" one after the other on digit 0.
*/
void writeArduinoOn7Segment() {
  lc.setChar(0, 0, 'a', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x05);
  delay(delaytime);
  lc.setChar(0, 0, 'd', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x1c);
  delay(delaytime);
  lc.setRow(0, 0, B00010000);
  delay(delaytime);
  lc.setRow(0, 0, 0x15);
  delay(delaytime);
  lc.setRow(0, 0, 0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
}

/*
  This method will scroll all the hexa-decimal
  numbers and letters on the display. You will need at least
  four 7-Segment digits. otherwise it won't really look that good.
*/
void scrollDigits() {
  for (int i = 0; i < 13; i++) {
    lc.setRow(0, 0, 0xbb);
    lc.setRow(0, 1, i);
    lc.setRow(0, 2, i);
    lc.setRow(0, 3, i);
    lc.setRow(0, 4, i);
    lc.setRow(0, 5, i);
    lc.setRow(0, 6, i);
    lc.setRow(0, 7, i);
    
    lc.setDigit(1, 0, i, false);
    lc.setDigit(1, 1, i, false);
    lc.setDigit(1, 2, i, false);
    lc.setDigit(1, 3, i, false);
    lc.setDigit(1, 4, i, false);
    lc.setDigit(1, 5, i, false);
    lc.setDigit(1, 6, i, false);
    lc.setDigit(1, 7, i, false);

    lc.setDigit(2, 0, i, false);
    lc.setDigit(2, 1, i, false);
    lc.setDigit(2, 2, i, false);
    lc.setDigit(2, 3, i, false);
    lc.setDigit(2, 4, i, false);
    lc.setDigit(2, 5, i, false);
    lc.setDigit(2, 6, i, false);
    lc.setDigit(2, 7, i, false);

    lc.setDigit(3, 0, i, false);
    lc.setDigit(3, 1, i, false);
    lc.setDigit(3, 2, i, false);
    lc.setDigit(3, 3, i, false);
    lc.setDigit(3, 4, i, false);
    lc.setDigit(3, 5, i, false);
    lc.setDigit(3, 6, i, false);
    lc.setDigit(3, 7, i, false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  delay(delaytime);
}

void loop() {
  scrollDigits();
}
