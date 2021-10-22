/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

int sensor = 9, s;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {

  Serial.begin(9600);
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object
  pinMode(sensor, INPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
}

void loop() {
  //s = digitalRead(sensor);
  //
  //  if (s == HIGH) {
  //    Serial.println(s);
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(2000);
  //  }

  //  else{
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(100);                       // waits 15ms for the servo to reach the position
  }
  delay(2000);
  //  }

}
