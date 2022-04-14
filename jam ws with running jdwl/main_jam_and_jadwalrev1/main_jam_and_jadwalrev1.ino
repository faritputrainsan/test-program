#include <Wire.h>
#include <DS3231.h>
#include <EEPROM.h>
#include "PrayerTimes.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
///////////////////////(RX,TX)

DS3231  rtc(SDA, SCL);
Time  t;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////variable EEPROM////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double lintang, addltg = 0 , bujur, addbjr = 4;
byte iqmah, addsbh = 8 , addlhr = 9 , addasr = 10 , addmgr = 11 , addisy = 12;
byte gmti, addgmt = 13;

byte   tggu, addsubuh = 14,  addzuhur = 15 ,   addashar = 16,  addmaghrib = 17, addisya = 18;

int  ksbh, kzhr, kasr, kmgr, kisy, addksbh = 19, addkzhr = 21, addkasr = 23, addkmgr = 25, addkisy = 27;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////variable timer MILLIS()////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long previuMillis = 0;
unsigned long interval2 = 500;

///////////////////////////////////////////////////////////////////////////////////////
///////////////variable PIN OUTPUT///////////////////////////////////////////////////////

//int ampli = 14;
//Pin connected to Strobe (pin 1) of 4094
#define strobePin A2
//Pin connected to Data (pin 2) of 4094
#define dataPin   A0
//Pin connected to Clock (pin 3) of 4094
#define clockPin  A1
// Init DS3231

///////////////////////////////////////////////////////////////////////////////////////
////////////////variable baca serial//////////////////////
byte ampli = A3;
String blutot;
char dchar [51];
int x;

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////variable data sevensegmen/////////////////////////
//byte segChar[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};
//byte segChar[] = {0x7b, 0x42, 0x37, 0x76, 0x4e, 0x7c, 0x7d, 0x52, 0x7f, 0x7e};

byte segChar[] = {0x10, 0x73, 0x24, 0x21, 0x43, 0x81, 0x80, 0x33, 0x00, 0x01, 0xE7, 0xFF};
//byte segChar[] = {0x81,0xB7,0xC2,0x92,0xB4,0x98,0x88,0xB3,0x80,0x90,0xE7,0xFF};

//byte segChar[] = {0x10, 0x73, 0x24, 0x21, 0x43, 0x81, 0x80, 0x33, 0x00, 0x01, 0xE7, 0xFF};

const unsigned char huruf[] PROGMEM =
{ 0x40, 0x30, 0x72, 0x60, 0x02, 0x16, 0x90, 0x34, 0xed, 0xe8, 0x14,
  //a/////b/////c/////d/////e/////f/////g/////h/////i/////j////k
  //0/////1/////2/////3/////4/////5/////6/////7/////8/////9////10
  0xb2, 0x86, 0x8c, 0x84, 0x70, 0x06, 0x0c, 0x96, 0x18, 0x32, 0xa0, 0x28
  //l/////m1////m2////n/////o/////p/////q/////r/////s////t/////u////y
  //11////12///13/////14////15////16////17////18////19///20////21///22
};

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////variable data jam/////////////////////////////
int iqdtk;

int j_ims, m_ims, j_sub, m_sub, j_dzu, m_dzu, j_ash, m_ash, j_mag, m_mag, j_isy, m_isy;
int m_imsak, j_imsak, m_subuh, j_subuh, m_dzuhur, j_dzuhur, m_ashar, j_ashar, m_maghrib, j_maghrib, m_isya, j_isya;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  mySerial.begin(9600);

  rtc.begin();
  rtc.setOutput (OUTPUT_SQW);
  rtc.setSQWRate (SQW_RATE_1);

  pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);
  pinMode( ampli   , OUTPUT);
}

void loop() {
//  serial();
  jdwl();


sendData("04:21,04:31,12:00,15:12,17:30,18:45",1);

  jam_mtr();
  tepat();
}

void data() {
  t = rtc.getTime();
}

void jdwl() {

  EEPROM.get (addltg, lintang);  //Latitude
  EEPROM.get (addbjr, bujur);   //Longitude
  gmti = EEPROM.read(addgmt);                   //Zona Waktu GMT WIB biasanya 7

  EEPROM.get(addksbh, ksbh);
  EEPROM.get(addkzhr, kzhr);
  EEPROM.get(addkasr, kasr);
  EEPROM.get(addkmgr, kmgr);
  EEPROM.get(addkisy, kisy);

  double times[sizeof(TimeName) / sizeof(char*)];
  int hours, minutes;     //jam sholat dan  menit sholat
  int z;
  set_calc_method(ISNA);        //Methode perhitungan mengikuti ISNA
  set_asr_method(Shafii);       //Pendapat Imam Syafi'i
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);           //Sudut Waktu Subuh
  set_isha_angle(18);           ////Sudut Waktu Isya
  get_prayer_times( t.year, t.mon,  t.date, lintang, bujur, gmti, times);

  get_float_time_parts(times[0], hours, minutes);
  j_subuh = combine(hours, minutes + ksbh);

  j_imsak = j_subuh - 10;

  //  get_float_time_parts(times[1], hours, minutes);
  get_float_time_parts(times[2], hours, minutes);
  j_dzuhur = combine(hours, minutes + kzhr);

  get_float_time_parts(times[3], hours, minutes);
  j_ashar = combine(hours, minutes + kasr);


  get_float_time_parts(times[4], hours, minutes);
  j_maghrib = combine(hours, minutes + kmgr);

  get_float_time_parts(times[6], hours, minutes);
  j_isya = combine(hours, minutes + kisy);
}

void tepat() {
  if (j_subuh == combine(t.hour,t.min))
  {
    beep();
    display_tepat(0);

    iqm(0);
    beep1();
    tunggu(0);
  }
  else if (j_dzuhur == combine(t.hour,t.min))
  {
    beep();
    display_tepat(1);

    iqm(1);
    beep1();
    tunggu(1);
  }
  else if (j_ashar == combine(t.hour,t.min))
  {
    beep();
    display_tepat(2);

    iqm(2);
    beep1();
    tunggu(2);
  }
  else if (j_maghrib == combine(t.hour,t.min))
  {
    beep();
    display_tepat(3);

    iqm(3);
    beep1();
    tunggu(3);
  }
  else if (j_isya == combine(t.hour,t.min))
  {
    beep();
    display_tepat(4);

    iqm(4);
    beep1();
    tunggu(4);
  }
}

void beep() {

  int beb = 2000;
  while (1) {
    digitalWrite(strobePin, HIGH);
    digitalWrite(ampli, 0);
    delay(beb);
    digitalWrite(ampli, 1);
    delay(beb);
    beb = beb - 200;
    if (beb == 0)
    {
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(100);
      digitalWrite(ampli, 1);
      delay(100);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      delay(50);
      digitalWrite(ampli, 1);
      delay(50);
      digitalWrite(ampli, 0);
      break;
    }
  }
}

void beep1() {
  digitalWrite(ampli, 1);
  delay(1000);
  digitalWrite(ampli, 0);
  delay(500);
  digitalWrite(ampli, 1);
  delay(1000);
  digitalWrite(ampli, 0);
  delay(500);
  digitalWrite(ampli, 1);
  delay(1000);
  digitalWrite(ampli, 0);
  delay(500);

}

int combine(byte cjam, byte cmin) {
  int result;
  result = (cjam * 60) + cmin;
  return result;

}