#include <DS3231.h>
#include <EEPROM.h>
#include <Wire.h>

#include "PrayerTimes.h"
#include <SoftwareSerial.h>
#include "avr/pgmspace.h"

SoftwareSerial mySerial(2, 3);
///////////////////////(RX,TX)

DS3231  rtc(SDA, SCL);
Time  t;

#define ADD_I2C 0x57
//I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////variable EEPROM////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double lintang, addltg = 0 , bujur, addbjr = 4;
byte addsbh = 8 , addlhr = 9 , addasr = 10 , addmgr = 11 , addisy = 12;
byte gmti, addgmt = 13;

byte addsubuh = 14,  addzuhur = 15 ,   addashar = 16,  addmaghrib = 17, addisya = 18;

int  ksbh, kzhr, kasr, kmgr, kisy, addksbh = 19, addkzhr = 21, addkasr = 23, addkmgr = 25, addkisy = 27;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////variable timer MILLIS()////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//unsigned long previuMillis = 0;
//unsigned long interval2 = 500;

///////////////////////////////////////////////////////////////////////////////////////
///////////////variable PIN OUTPUT///////////////////////////////////////////////////////

//int ampli = 14;
//Pin connected to Strobe (pin 1) of 4094
#define strobePin 11
//Pin connected to Data (pin 2) of 4094
#define dataPin   12
//Pin connected to Clock (pin 3) of 4094
#define clockPin  10
// Init DS3231

#define ampli  9
#define res  A3
#define pull  A2


unsigned int mosName_add = 0;
unsigned int Text_add = 65;
byte st = 0;
bool ok = 0;

///////////////////////////////////////////////////////////////////////////////////////
////////////////variable baca serial//////////////////////

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////variable data sevensegmen/////////////////////////
//byte segChar[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};
//byte segChar[] = {0x7b, 0x42, 0x37, 0x76, 0x4e, 0x7c, 0x7d, 0x52, 0x7f, 0x7e};

int segChar[] = {0xbf, 0x0a, 0xdd, 0x5f, 0x6b, 0x77, 0xf7, 0x1a, 0xff, 0x7f};
int dates ;

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////variable data jam//////////////////////////////////////

int j_imsak, j_subuh, j_dzuhur,  j_ashar,  j_maghrib,  j_isya;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.setOutput (OUTPUT_SQW);
  rtc.setSQWRate (SQW_RATE_1);

  pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);
  pinMode( ampli   , OUTPUT);
  pinMode( res   , OUTPUT);
  pinMode( pull   , OUTPUT);
  digitalWrite(res, LOW);
  data();
  dates = t.date;
  delay(500);
}

void loop() {
  digitalWrite(res, HIGH);
  jam_mtr();
  jdwl();
  tepat();
  if (mySerial.available()) {
    String slavedt = mySerial.readString();
    if ( slavedt.substring(0, 3) == "PNG") {
      sendData(st);
      if (st == 0) {
        ok = 0;
      }
      else {
        ok = 1;
      }
    }
  }
  else if (ok == 1) {
    dis_tpt(st);
    delay (100);
    st = 0;
    ok = 0;
//    digitalWrite(res, LOW);
  }
}

void data() {
  t = rtc.getTime();
}

void jdwl() {

  EEPROM.get (addltg, lintang);  //Latitude
  EEPROM.get (addbjr, bujur);   //Longitude
  gmti = EEPROM.read(addgmt);                   //Zona Waktu GMT WIB biasanya 7

  //  gmti = 7 ;
  //  lintang = -7, 45; //Latitude
  //  bujur = 110, 21 ; //Longitude

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
  //  + kisy
  j_isya = combine(hours, minutes );
}

void tepat() {
  if (j_subuh == combine(t.hour, t.min) and st == 0) {
    digitalWrite(res, LOW);
    st = 1;
  }
  else if (j_dzuhur == combine(t.hour, t.min) and st == 0) {
    digitalWrite(res, LOW);
    st = 2;
  }
  else if (j_ashar == combine(t.hour, t.min)and st == 0) {
    digitalWrite(res, LOW);
    st = 3;
  }
  else if (j_maghrib == combine(t.hour, t.min)and st == 0) {
    digitalWrite(res, LOW);
    st = 4;
  }
  else if (j_isya == combine(t.hour, t.min)and st == 0) {
    digitalWrite(res, LOW);
    st = 5;
  }
  else if (dates != t.date) {
    digitalWrite(res, LOW);
    st = 0;
    dates = t.date;
  }
}

void dis_tpt(byte i) {
  digitalWrite(pull, LOW);
  beep();
  display_tepat();
  digitalWrite(pull, LOW);
  iqm(i - 1);
  digitalWrite(pull, LOW);
  beep1();
  tunggu(i - 1);
}

void beep() {
  int bep = 0;
  while (bep < 10) {
    bep ++;
    digitalWrite(ampli, 1);
    delay(1000);
    digitalWrite(ampli, 0);
    delay(1000);
  }
}

void beep1() {
  int bep = 0;
  while (bep < 3) {
    bep ++;
    digitalWrite(ampli, 1);
    delay(1000);
    digitalWrite(ampli, 0);
    delay(1000);
  }

}

int combine(byte cjam, byte cmin) {
  int result;
  result = (cjam * 60) + cmin;
  return result;
}
