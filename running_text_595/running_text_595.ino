/*
 * Kode Ditulis oleh  : Moh. Badar Wildanie
 * Sub routine        : Hardware API dot matrix untuk HTTP dan WS
 * Client             : APK Android
 * Berikan sumber jika ingin membagikan kode ini.
 * Hargailah pembuat dengan membagikan situs ini kepada orang lain / teman-teman anda dan berikan sumber
 * http://badar-blog.blogspot.com/ -> Berbagi tutorial dunia IT secara jelas dan gratis
 */
 
#include <font5x7.h>
 
#include <EEPROM.h>
 
// Setting SSID dan Password WiFi (Mode AP)

// Pendeklarasian variabel objek server dan websocket

// Penentuan PIN
byte verticalData = 7;
byte verticalClock = 5;

byte horizontalData = 2;
byte horizontalClock = 4;

const byte latch = 3;
 
// Penentuan lebar dan tinggi
const byte lebar = 120;
const byte tinggi = 8;
 
// Penentuan tulisan / running text
String tulisan = "MENGAPA KENAPa        ";
 
// Perhitungan jumlah modul untuk dibuatkan array bitmap
//const byte jumlahModul = lebar/8;
//byte bitmap[tinggi][jumlahModul];
 
// Cuma ngetes aja sih
byte smiley[] = {0x00, 0x04, 0x72, 0x02, 0x02, 0x72, 0x04, 0x00};
 
void setup() {
  // Setting pin yang digunakan sebagai output
  pinMode(horizontalData, OUTPUT);
  pinMode(horizontalClock, OUTPUT);
  pinMode(verticalData, OUTPUT);
  pinMode(verticalClock, OUTPUT);
  pinMode(latch, OUTPUT);
 
  // Mengambil data teks EEPROM
//  tulisan = readString();
}
 
// Penentuan konfigurasi scrolling dan variabelnya
int scrollSpeed = 60; // Atur ini untuk mengubah kecepatan
unsigned long scrollTiming = 0;
int scrollStep = 0;
 
// Fungsi untuk melakukan scrolling text
void scrollingText() {
 
  // Melakukan pergeseran bitmap kekiri disetiap [scrollSpeed] milidetik
  if (millis() - scrollTiming >= scrollSpeed) {
    scrollTiming = millis();
    scrollStep++;
 
    // Mereset scroll step jika melebihi jumlah lebar karakter (6 kolom + jarak antar karakter)
    // (Scroll step digunakan untuk mengetahui karakter mana yang akan di print berdasarkan sejauh mana pergeseran)
    if (scrollStep > tulisan.length() * 6) scrollStep = 0;
    uint8_t charIndexScreen = floor((scrollStep - 1) / 6);  // Indeks karakter dari variabel tulisan
    uint8_t charIndex = tulisan[charIndexScreen] - 32;  // Indeks karakter berdasarkan kode ASCII yang ada di library font5x7
    uint8_t col = (scrollStep - 1) % 6; // Kolom dari setiap karakter yang akan di print (juga berdasarkan pergeseran / scrollstep) pastinya
 
    // Melakukan pergeseran bitmap ke arah kiri 
    // selagi menambahkan bit baru berdasarkan [col] untuk membentuk huruf baru
    for (int row = 0; row < tinggi; row++) {
 
      // melakukan perulangan setiap modul, agar pada modul 1 dapat bergeser ke modul 2 dst..
      for (int cols = 0; cols < jumlahModul; cols++) {
        bitmap[row][cols] <<= 1; // Ini gan pergeserannya
        bitmap[row][0] |= bitRead(pgm_read_byte(&Font5x7[charIndex*5+col]), row);
        bitWrite(bitmap[row][cols], 0, bitRead(bitmap[row][cols-1], 7));
      }
 
      // Menambahkan bit baru untuk huruf baru di kanan
      bitmap[row][0] <<= 1;
//      if (col >= 5) {
//        bitmap[row][0] |= 0; // Jika col lebih dari 5, maka kita gunakan untuk spasi antar huruf
//      }
//      else {
//         // Jika tidak, berarti kita tambahkan bit baru tsb..
//      }
    }
  }
}
void loop() {
  scrollingText(); // Melakukan scrolling text ALIAS pergeseran bit ke kiri
  refresh(); // menampilkan bitmap ke dot matrix
}
 
// Fungsi untuk menampilkan array bitmap ke dot matrix
void refresh() {
  // perulangan untuk melakukan scan baris (Vertical Scan dan Vertical sync / V-Sync)
  // pada dasarnya, setiap baris led dihidupkan kemudian berganti kebaris berikutnya dst..
  for (byte row = 0; row < tinggi; row++) {
    digitalWrite(latch, LOW);
    // menampilkan bitmap berdasarkan baris yang terdapat pada array bitmap
    for (int modul = jumlahModul-1; modul >= 0; modul--){
      shiftOut(horizontalData, horizontalClock, LSBFIRST, bitmap[row][modul]);
    }
    byte rows = 1<< row;
    shiftOut(verticalData, verticalClock, MSBFIRST, ~rows);  // ini gan pergeseran vscan nya
    digitalWrite(latch, HIGH); // setelah semua bit terkirim, ditampilkan ke output led
    delay(1);
  }
}
