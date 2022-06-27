#include <DS3231.h>
#include <EEPROM.h>
#include <I2C_eeprom.h>

#include "PrayerTimes.h"
#include <SoftwareSerial.h>
#include "avr/pgmspace.h"

SoftwareSerial mySerial(2, 3);
///////////////////////(RX,TX)

DS3231  rtc(SDA, SCL);
Time  t;

#define ADD_I2C 0x57
I2C_eeprom eeprom(ADD_I2C, I2C_DEVICESIZE_24LC32);

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
#define strobePin 11
//Pin connected to Data (pin 2) of 4094
#define dataPin   12
//Pin connected to Clock (pin 3) of 4094
#define clockPin  10
// Init DS3231

byte ampli = A1;
byte res = A3;


///////////////////////////////////////////////////////////////////////////////////////
////////////////variable baca serial//////////////////////


String blutot;
char dchar [51];
int x;
char text [200];
char text1 [100];
char iqmn [15];
char tgu [15];
char jwl [40];

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////variable data sevensegmen/////////////////////////
//byte segChar[] = {0x80, 0xed, 0x42, 0x48, 0x2d, 0x18, 0x10, 0xcd, 0x00, 0x08};
//byte segChar[] = {0x7b, 0x42, 0x37, 0x76, 0x4e, 0x7c, 0x7d, 0x52, 0x7f, 0x7e};

int segChar[] = {0xbf, 0x0a, 0xdd, 0x5f, 0x6b, 0x77, 0xf7, 0x1a, 0xff, 0x7f};

//const String hari[] = {"SENIN","SELASA","RABU","KAMIS","JUM'AT","SABTU","AHAD"};

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////variable data jam//////////////////////////////////////
int iqdtk;

int j_ims, m_ims, j_sub, m_sub, j_dzu, m_dzu, j_ash, m_ash, j_mag, m_mag, j_isy, m_isy;
int j_imsak, j_subuh, j_dzuhur,  j_ashar,  j_maghrib,  j_isya;


void setup() {

  Serial.begin(9600);
  eeprom.begin();
  mySerial.begin(9600);

  rtc.begin();
  rtc.setOutput (OUTPUT_SQW);
  rtc.setSQWRate (SQW_RATE_1);

  pinMode( strobePin , OUTPUT);
  pinMode( dataPin    , OUTPUT);
  pinMode( clockPin   , OUTPUT);
  pinMode( ampli   , OUTPUT);
  pinMode( res   , OUTPUT);
  digitalWrite(res, LOW);
  delay(500);
  digitalWrite(res, HIGH);

}
String Serials ;
void loop() {

  jam_mtr();
  jdwl();

  if(mySerial.available()){
    Serials = mySerial.readString();
    sendData();
  }

  //
  //  Serial.print(t.hour);
  //  Serial.print(" : ");
  //  Serial.print(t.min);
  //  Serial.print(" : ");
  //  Serial.println(t.sec);
  //  delay(1000);
  //
  //  jam_mtr();


}

void data() {
  t = rtc.getTime();
}

void jdwl() {

  //  EEPROM.get (addltg, lintang);  //Latitude
  //  EEPROM.get (addbjr, bujur);   //Longitude
  //  gmti = EEPROM.read(addgmt);                   //Zona Waktu GMT WIB biasanya 7
  
  gmti = 7 ;
  lintang = -7, 45; //Latitude
  bujur = 110, 21 ; //Longitude

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
  if (j_subuh == combine(t.hour, t.min))
  {
    beep();
    display_tepat(0);

    iqm(0);
    beep1();
    tunggu(0);
  }
  else if (j_dzuhur == combine(t.hour, t.min))
  {
    beep();
    display_tepat(1);

    iqm(1);
    beep1();
    tunggu(1);
  }
  else if (j_ashar == combine(t.hour, t.min))
  {
    beep();
    display_tepat(2);

    iqm(2);
    beep1();
    tunggu(2);
  }
  else if (j_maghrib == combine(t.hour, t.min))
  {
    beep();
    display_tepat(3);

    iqm(3);
    beep1();
    tunggu(3);
  }
  else if (j_isya == combine(t.hour, t.min))
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
