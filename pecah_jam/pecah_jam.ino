
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int jam = konversi(13,24);
  Serial.println(jam);
  delay(1000);
  
}

int konversi(byte jam, byte menit){
  int Combine;
  Combine = (jam * 60) + menit;
  return Combine;
}

int unkonversi(int jam) [] = {
  byte unjam;
  byte unmenit;

  unjam = jam /60;
  unmenit = jam%60;
  Serial.print(unjam);
  Serial.println(unmenit);
  delay (1000);
}
