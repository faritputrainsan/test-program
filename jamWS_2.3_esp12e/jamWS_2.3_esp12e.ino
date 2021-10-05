#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <RtcDS3231.h>
#include "index.h"

RtcDS3231<TwoWire> Rtc(Wire);

#ifndef APSSID
#define APSSID "Jam Control"
#define APPSK  "12345678"
#endif

//#ifndef STASSID
//#define STASSID "XLGO-75C3";
//#define STAPSK  "46266172";
//#endif

WiFiServer server(80);
String request = "";

const char *ssid = APSSID;
const char *pass = APPSK;

//const char* rssid = STASSID;
//const char* rpassword = STAPSK;

//pin pin yang sebagai output
#define clk 0
#define d   2
#define str 15
int LED_Pin = 16;


double lintang, addltg = 0, bujur, addbjr = 4;



//data untuk 7 segment
byte dataSeg[] = {0x01, 0xB7, 0xc2, 0x12, 0x34, 0x18, 0x08, 0xb3, 0x00, 0x10};

// change these values to match your network

//komponen timer millis
unsigned long count = 1000;
unsigned long curentCount = 0;
long xx = 0;
int jam , menit , mnt;

void setup() {
  Serial.begin(115200);
  Wire.begin(13, 12);
  Rtc.Begin();

//  WiFi.mode(WIFI_STA);
//  WiFi.begin();
//
//  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//    Serial.println("Connection Failed! Rebooting...");
//    delay(5000);
//    ESP.restart();
//  }

  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("MY Huney");
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin(); ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  
  WiFi.softAP(ssid, pass);

  
  IPAddress myIP = WiFi.softAPIP();
  server.begin();

  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeClock);
  Rtc.SetSquareWavePinClockFrequency(DS3231SquareWaveClock_1Hz);

  pinMode(LED_Pin, OUTPUT);

  pinMode(clk , OUTPUT);
  pinMode(d   , OUTPUT);
  pinMode(str , OUTPUT);

  Serial.println();
  Serial.println("Serial started at 115200");
  Serial.println("ESP8266_LED_CONTROL_AJAX_03");
  Serial.println();

  Serial.println(myIP);
  Serial.println("Server started");
  dJam();
  mnt = menit - 1;
}

void loop() {
ArduinoOTA.handle();
  dJam();
  while (mnt != menit){
    mnt = menit;
    tampil(jam , menit);
  }
    // Check if a client has connected
    WiFiClient client = server.available();
  // Read the first line of the request
  request = client.readStringUntil('\r');
  
  if ( request.indexOf("SYNC") > 0 ) {
    client.print( header );
    client.print( "Syncron" );
//    client.clear();
    setting();
    dJam();
    tampil(jam, menit);
  }
  else{
  client.flush();
  client.print( header );
  client.print( html_1 );
  }

} // void loop()

//mengambil data RTC i2c
void dJam() {
  const RtcDateTime now = Rtc.GetDateTime();
  jam = now.Hour();
  menit = now.Minute();
}

// menampilkan data ke 7 segment
void tampil(int jam, int minute ) {
  digitalWrite(str, LOW);
  shiftOut(d, clk, MSBFIRST, dataSeg[minute % 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[minute / 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[jam % 10]);
  shiftOut(d, clk, MSBFIRST, dataSeg[jam / 10]);
  digitalWrite(str, HIGH);
}

//seting setiap tombol ditekan
void setting() {
  String bulan = request.substring(9, 12);
  String tgl = request.substring(15, 17);
  String thn = request.substring(20, 24);
  String jams = request.substring(24, 26);
  String mnt = request.substring(27, 29);
  String scn = request.substring(30, 32);

  int blns = bulan.toInt();
  int tgls = tgl.toInt();
  int thns = thn.toInt();

  int jms = jams.toInt();
  int mnts = mnt.toInt();
  int scns = scn.toInt();

  Rtc.SetDateTime(RtcDateTime(thns, blns, tgls, jms, mnts, scns));
}

//timer setiap 1 detik
void timer() {
  unsigned long timeMillis = millis();
  while (timeMillis - curentCount >= count) {
    curentCount = timeMillis;
    xx ++;

  }
}
