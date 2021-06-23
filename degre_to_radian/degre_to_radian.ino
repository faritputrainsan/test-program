void setup() {
 Serial.begin(9600);

 float jarak=60;
 float alpha=65;

 // Hitung nilai radian
    float radian= ((float)2*3.14)*alpha/360;
    
 // Hitung nilai tinggi
    float tinggi= tan(radian)* jarak;

 // Tampilkan nilai
    Serial.print("tinggi =");
    Serial.println(tinggi); 
}

void loop() {

}
