#include <Arduino.h>
#include <HX711.h>


const int D_OUT=12;
const int CLK = 13;

HX711 scale;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  scale.begin(D_OUT,CLK);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (scale.is_ready()) {
    scale.set_scale();    
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...");
    delay(5000);
    long reading = scale.get_units(15);
    Serial.print("Result: ");
    Serial.println(reading);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);
}
