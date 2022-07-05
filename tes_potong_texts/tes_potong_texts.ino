String texts = "selamat datang di gunungkidul yogyakarta indonesia ini adalah contoh texts yang panjang lebih dari 60 dan akan di potong potong menjadi 60 60 60 dan akan menjadi data texts dengan panjang 606060 okokokokok!!!";
String text60 = "ini adalah teks 60 karakter yang harus 60 karakter dan passs";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

unsigned int TextLength = texts.length();
unsigned int MaxText = 60;

int lenSplitTxt = TextLength / MaxText;

void loop() {
  // put your main code here, to run repeatedly:




  int x = 0, y = 0;
  for (int i = 0; i < lenSplitTxt+1; i++) {
//    reset string untuk di isi lagi
    String splitText = " ";
    x = 60 * y;
    y ++;
    //    x = 60;
    int xx = 60 * y;
    Serial.print("y = ");
    Serial.println(y);
    Serial.print("x = ");
    Serial.println(x);
    splitText = texts.substring(x, xx);
    Serial.println(splitText);
    delay(1000);
    
    Serial.print("xx = ");
    Serial.println(xx);
    Serial.println(" ");
    Serial.println(" ");
    delay(1000);
  }


  //  for (unsigned int i = 0; i < TextLength; i++){
  //    if (TextLength){
  //
  //    }
  //}
  //
  //  Serial.println(lenSplitTxt);
  //  Serial.println(texts.length());
  delay(2000);
}

// okey
