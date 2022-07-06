String texts = "selamat datang di gunungkidul yogyakarta indonesia ini adalah contoh texts yang panjang lebih dari 60 dan akan di potong potong menjadi 60 60 60 dan akan menjadi data texts dengan panjang 606060 okokokokok!!!";
String text60 = "ini adalah teks 60 karakter yang harus 60 karakter dan passs";

String dSerial;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void splits(String tes){
  unsigned int TextLength = tes.length();
unsigned int MaxText = 60;
int lenSplitTxt = TextLength / MaxText;

  int x = 0, y = 0;
  for (int i = 0; i < lenSplitTxt+1; i++) {
//    reset string untuk di isi lagi
    String splitText = " ";
    x = MaxText * y;
    y ++;
    //    x = 60;
    int xx = MaxText * y;

    splitText = tes.substring(x, xx);
    Serial.println(splitText);
    delay(1000);
  }

  delay(2000);
}

void serialEvent(){
  dSerial = Serial.readString();
  splits(dSerial.substring(3,dSerial.length()));
}

// okey
