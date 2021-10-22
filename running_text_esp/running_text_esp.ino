/*
 * Kode Ditulis oleh  : Moh. Badar Wildanie
 * Sub routine        : Hardware API dot matrix untuk HTTP dan WS
 * Client             : APK Android
 * Berikan sumber jika ingin membagikan kode ini.
 * Hargailah pembuat dengan membagikan situs ini kepada orang lain / teman-teman anda dan berikan sumber
 * http://badar-blog.blogspot.com/ -> Berbagi tutorial dunia IT secara jelas dan gratis
 */
 
#include <font5x7.h>
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <WebSocketsServer.h>
#include <EEPROM.h>
 
// Setting SSID dan Password WiFi (Mode AP)
const char *ssid = "WnNetAP ESP";
const char *pass = "qweqweqwe";
IPAddress IP(192,168,1,1);
IPAddress NETMASK(255,255,255,0);
IPAddress NETWORK (192,168,1,1);
IPAddress DNS(192,168,1,1);
 
// Pendeklarasian variabel objek server dan websocket
ESP8266WebServer server(80);
//WebSocketsServer ws(81);
 
// Penentuan PIN
byte verticalData = D0;
byte verticalClock = D1;
byte horizontalData = D2;
byte horizontalClock = D3;
const byte latch = D5;
 
// Penentuan lebar dan tinggi
const byte lebar = 24;
const byte tinggi = 8;
 
// Penentuan tulisan / running text
String tulisan = "MENGAPA KENAPa        ";
 
// Perhitungan jumlah modul untuk dibuatkan array bitmap
const byte jumlahModul = lebar/8;
byte bitmap[tinggi][jumlahModul];
 
// Cuma ngetes aja sih
byte smiley[] = {0x00, 0x04, 0x72, 0x02, 0x02, 0x72, 0x04, 0x00};
 
void setup() {
  // Setting pin yang digunakan sebagai output
  pinMode(horizontalData, OUTPUT);
  pinMode(horizontalClock, OUTPUT);
  pinMode(verticalData, OUTPUT);
  pinMode(verticalClock, OUTPUT);
  pinMode(latch, OUTPUT);
 
  // Memulai WiFi sebagai AP
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  WiFi.config(IP, NETWORK, NETMASK, DNS); 
 
  // Memulai Server
  server.on("/setText", HTTP_POST, setText);
  server.begin();
 
  // Memulai Web Socket
  ws.begin();
  ws.onEvent(wsEvent);
 
  // Mengambil data teks EEPROM
  tulisan = readString();
}
 
// Penentuan konfigurasi scrolling dan variabelnya
int scrollSpeed = 70; // Atur ini untuk mengubah kecepatan
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
    if (scrollStep > tulisan.length() * 6) scrollStep = 1;
    uint8_t charIndexScreen = floor((scrollStep - 1) / 6);  // Indeks karakter dari variabel tulisan
    uint8_t charIndex = tulisan[charIndexScreen] - 32;  // Indeks karakter berdasarkan kode ASCII yang ada di library font5x7
    uint8_t col = (scrollStep - 1) % 6; // Kolom dari setiap karakter yang akan di print (juga berdasarkan pergeseran / scrollstep) pastinya
 
    // Melakukan pergeseran bitmap ke arah kiri 
    // selagi menambahkan bit baru berdasarkan [col] untuk membentuk huruf baru
    for (int row = 0; row < tinggi; row++) {
 
      // melakukan perulangan setiap modul, agar pada modul 1 dapat bergeser ke modul 2 dst..
      for (int col = 1; col < jumlahModul; col++) {
        bitmap[row][col] <<= 1; // Ini gan pergeserannya
        bitWrite(bitmap[row][col], 0, bitRead(bitmap[row][col-1], 7));
      }
 
      // Menambahkan bit baru untuk huruf baru di kanan
      bitmap[row][0] <<= 1;
      if (col >= 5) {
        bitmap[row][0] |= 0; // Jika col lebih dari 5, maka kita gunakan untuk spasi antar huruf
      }
      else {
        bitmap[row][0] |= bitRead(pgm_read_byte(&Font5x7[charIndex*5+col]), row); // Jika tidak, berarti kita tambahkan bit baru tsb..
      }
    }
  }
}
void loop() {
  server.handleClient(); // mendengarkan permintaan client berulang-ulang (bawaan dari ESP8266)
  ws.loop();  // mendengarkan permintaan client bidang web socket berulang-ulang (bawaan dari ESP8266)
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
      shiftOut(horizontalData, horizontalClock, LSBFIRST, ~bitmap[row][modul]);
    }
    shiftOut(verticalData, verticalClock, MSBFIRST, 1 << row);  // ini gan pergeseran vscan nya
    digitalWrite(latch, HIGH); // setelah semua bit terkirim, ditampilkan ke output led
    delay(1);
  }
}
 
 
// API EEPROM untuk setting tulisan
// kalau bingung komen di artikel aja ya gan..
void writeString(String text) {
  int textLength = text.length();
  byte a = textLength & 0xFF;
  byte b = (textLength >> 8) & 0xFF;
  
  EEPROM.begin(1024);
  EEPROM.write(0, a);
  EEPROM.write(1, b);
  for (int i = 0; i < text.length(); i++) {
    EEPROM.write(2+i, text[i]);
  }
  EEPROM.commit();
}
String readString() {
  EEPROM.begin(1024);
  byte a = EEPROM.read(0);
  byte b = EEPROM.read(1);
  
  if (a != 255 || b != 255) {
    long res = b;
    res = res << 8;
    res = res | a;
    char abjad[res + 1];
    for (int i = 0; i < res; i++) {
      abjad[i] = EEPROM.read(2+i);
    }
    abjad[res] = '\0';
    EEPROM.end();
    return String(abjad);
  }
  else {
    EEPROM.end();
    return "Teks kosong    ";
  }
}
 
// Fungsi yang dijalan saat ada HTTP POST dari client dengan path "/setText" dan membawa data argumen "text"
// Kemudian, teks tersebut disimpan di eeprom untuk ditampilkan ke dotmatriks
void setText() {
  if (server.hasArg("text")) {
    tulisan = server.arg("text");
    writeString(tulisan); // Ini gan, baris kode untuk nyimpan di EEPROM
    scrollStep = 0;
    server.send(200, "text/plain", "Perintah berhasil dieksekusi");
  }
}
 
// Fungsi ini digunakan untuk menangani permintaan websocket
// websocket ini digunakan untuk broadcast teks ke seluruh client saat ada perubahan
void wsEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED :
      break;
    case WStype_CONNECTED : 
      Serial.println("Somebody connected");
      break;
    case WStype_TEXT :
      String command = String((char *) &payload[0]);
      if (command == "getTulisan") {
        String tulisanRe = "{\"command\": \"getTulisan\", \"response\": \"" +tulisan+ "\"}";
        char tulisanChar[tulisanRe.length()];
        tulisanRe.toCharArray(tulisanChar, tulisanRe.length()+1);
        Serial.println(tulisanChar);
        ws.sendTXT(num, tulisanChar, tulisanRe.length());
      }
      break;
  }
}
