/*
  Program Ini dibuat oleh tim ayongoprek.com

  Ini adalah contoh program Scrolling Text untuk menjalankan Modul Dot Matrix 8x8 yang berbasiskan IC Shift Register 74HC595.
  Program yang diberikan di bawah ini dapat dikontrol oleh bluetooth dari smartphone Android menggunakan aplikasi yang disediakan

  Parameter yang dapat dikontrol dari smartphone antara lain:
  - Jumlah Kolom Display
  - Jumlah Baris Display
  - Isi text yang ditampilkan
  - Kecepatan Scrolling

  Semua Parameter diatas dapat disimpan di dalam EEPROM, yang berarti ketika mikrokontroller dimatikan,
  nilai parameter yang di set tidak berubah dari nilai yang telah di set sebelumnya

  Untuk informasi lebih lengkap tentang cara menghubungkan modul Dot Matrix 8x8, dapat dilihat di
  ----->>http://www.ayongoprek.com
*/
//#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <EEPROM.h>

//Definisi PIN pada arduino yang digunakan pada Mikrokontroler untuk berkomunikasi dengan Shift register
//Sesuaikan Parameter ini dengan koneksi pada arduino anda
#define HC595_COL_DS         2
#define HC595_COL_SHCP       4
#define HC595_COL_STCP       3


#define HC595_ROW_DS         7
#define HC595_ROW_SHCP       5
#define HC595_ROW_STCP       6
//#define LED                 13

//Definisi yang menentukan banyaknya karakter yang diperbolehkan di dalam Scrolling Text
#define	Text_Size		150

//Definisi Mode Display
#define Text_Only		0
#define Graphic			1
#define Animation		2

//Definisi Mode UART
#define Perintah		0
#define Tulis_Text		1
#define Time_Out		65000

//Definisi dari Command Set yang digunakan sistem untuk berkomunikasi melalui UART
#define Set_Speed		65
#define Set_Column		66
#define Set_Row			67
#define Save_Config		68
#define Save_Text		69
#define Debug			70
#define Display_ON		80
#define Display_OFF		81
#define Text_Data		82
#define Text_Data_End	 255

/*
  ------------------------------------------------------
  Daftar Inisialisasi variabel global Dalam Program, Beserta Data Type nya, dan Nilai Awalnya
  ------------------------------------------------------
*/
unsigned long previousMillis = 0;        //Variabel Untuk menyimpan nilai millis yang digunakan untuk blinking LED

//alamat penyimpanan Variabel di EEPROM
//---------------------------------------------------------------------
int Display_Row = 0;
int Display_Column = 1;
int Scroll_Speed = 4;
int Display_Text = 6;
//alamat variabel di EEPROM yang menyatakan apakah variabel ROW. COL. Speed, dan Text telah ter konfigurasi di EEPROM
//hal ini dibutuhkan karena arduino IDE tidak memiliki kemampuan untuk menginisialisasi nilai EEPROM secara otomatis
//karena apabila nilai dibaca dari EEPROM tanpa di inisialisasi dahulu nilainya, akan terjadi error.
int Text_Configure = 2;
int Param_Configure = 3;
//---------------------------------------------------------------------

uint16_t DISP_COL_CNT = 152;
volatile uint8_t DISP_ROW_CNT = 8;
volatile uint8_t disp_mode = Text_Only;
volatile uint16_t Scr_Speed = 50;

volatile int a = 0;
volatile int a2, a3 = 0;
volatile uint8_t row = 0;
volatile uint16_t cnt = 0;

volatile int16_t col = 0;
volatile int chr = 0;
volatile int8_t m = 0;

uint8_t data;
uint8_t length;

volatile uint8_t temp = 0;
uint8_t uart_data[5];
uint8_t uart_mode = Perintah;
uint8_t uart_counter = 0;
uint16_t uart_timeout = 0;
uint8_t Send_Data = 0;
uint8_t Text_Counter = 0;

//Buffer Text yang akan ditampilkan
char text[Text_Size] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ  abcdefghijklmnopqrstuvwxyz";

//Font Yang Digunakan di dalam Program, yang ditampilkan ke LED Matrix
const unsigned char smallFont[] PROGMEM =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // sp
  0x00, 0x00, 0x2f, 0x00, 0x00, 0x00,  // !
  0x00, 0x07, 0x07, 0x00, 0x00, 0x00,  // "
  0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00,  // #
  0x12, 0x2a, 0x7f, 0x2a, 0x24, 0x00,  // $
  0x46, 0x26, 0x10, 0xc8, 0xc4, 0x00,  // %
  0x50, 0x22, 0x55, 0x49, 0x36, 0x00,  // &
  0x00, 0x00, 0x03, 0x05, 0x00, 0x00,  // '
  0x00, 0x41, 0x22, 0x1c, 0x00, 0x00,  // (
  0x00, 0x1c, 0x22, 0x41, 0x00, 0x00,  // )
  0x14, 0x08, 0x3E, 0x08, 0x14, 0x00,  // *
  0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,  // +
  0x00, 0x00, 0x30, 0x50, 0x00, 0x00,  // ,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x00,  // -
  0x00, 0x00, 0x60, 0x60, 0x00, 0x00,  // .
  0x02, 0x04, 0x08, 0x10, 0x20, 0x00,  // /
  //  0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xFF,  // /
  0x3E, 0x45, 0x49, 0x51, 0x3E, 0x00,  // 0
  0x00, 0x40, 0x7F, 0x42, 0x00, 0x00,  // 1
  0x46, 0x49, 0x51, 0x61, 0x42, 0x00,  // 2
  0x31, 0x4B, 0x45, 0x41, 0x21, 0x00,  // 3
  0x10, 0x7F, 0x12, 0x14, 0x18, 0x00,  // 4
  0x39, 0x45, 0x45, 0x45, 0x27, 0x00,  // 5
  0x30, 0x49, 0x49, 0x4A, 0x3C, 0x00,  // 6
  0x03, 0x05, 0x09, 0x71, 0x01, 0x00,  // 7
  0x36, 0x49, 0x49, 0x49, 0x36, 0x00,  // 8
  0x1E, 0x29, 0x49, 0x49, 0x06, 0x00,  // 9
  0x00, 0x00, 0x36, 0x36, 0x00, 0x00,  // :
  0x00, 0x00, 0x36, 0x56, 0x00, 0x00,  // ;
  0x08, 0x14, 0x22, 0x41, 0x00, 0x00,  // <
  0x14, 0x14, 0x14, 0x14, 0x14, 0x00,  // =
  0x00, 0x41, 0x22, 0x14, 0x08, 0x00,  // >
  0x06, 0x09, 0x51, 0x01, 0x02, 0x00,  // ?
  0x3E, 0x51, 0x59, 0x49, 0x32, 0x00,  // @
  0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,  // A
  0x36, 0x49, 0x49, 0x49, 0x7F, 0x00,  // B
  //  0xF7, 0x94, 0x94, 0x94, 0x63, 0x00,  // B
  0x22, 0x41, 0x41, 0x41, 0x3E, 0x00,  // C
  0x1C, 0x22, 0x41, 0x41, 0x7F, 0x00,  // D
  0x41, 0x49, 0x49, 0x49, 0x7F, 0x00,  // E
  0x01, 0x09, 0x09, 0x09, 0x7F, 0x00,  // F
  0x7A, 0x49, 0x49, 0x41, 0x3E, 0x00,  // G
  0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,  // H
  0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,  // I
  0x01, 0x3F, 0x41, 0x40, 0x20, 0x00,  // J
  0x41, 0x22, 0x14, 0x08, 0x7F, 0x00,  // K
  0x40, 0x40, 0x40, 0x40, 0x7F, 0x00,  // L
  0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00,  // M
  0x7F, 0x10, 0x08, 0x04, 0x7F, 0x00,  // N
  0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,  // O
  0x06, 0x09, 0x09, 0x09, 0x7F, 0x00,  // P
  0x5E, 0x21, 0x51, 0x41, 0x3E, 0x00,  // Q
  0x46, 0x29, 0x19, 0x09, 0x7F, 0x00,  // R
  0x31, 0x49, 0x49, 0x49, 0x46, 0x00,  // S
  0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,  // T
  0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,  // U
  0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00,  // V
  0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00,  // W
  0x63, 0x14, 0x08, 0x14, 0x63, 0x00,  // X
  0x07, 0x08, 0x70, 0x08, 0x07, 0x00,  // Y
  0x43, 0x45, 0x49, 0x51, 0x61, 0x00,  // Z
  0x00, 0x41, 0x41, 0x7F, 0x00, 0x00,  // [
  0x55, 0x2A, 0x55, 0x2A, 0x55, 0x00,  // slash
  0x00, 0x7F, 0x41, 0x41, 0x00, 0x00,  // ]
  0x04, 0x02, 0x01, 0x02, 0x04, 0x00,  // ^
  0x40, 0x40, 0x40, 0x40, 0x40, 0x00,  // _
  0x00, 0x00, 0x04, 0x02, 0x01, 0x00,  // '
  0x78, 0x54, 0x54, 0x54, 0x20, 0x00,  // a
  0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,  // b
  0x20, 0x44, 0x44, 0x44, 0x38, 0x00,  // c
  0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,  // d
  0x18, 0x54, 0x54, 0x54, 0x38, 0x00,  // e
  0x02, 0x01, 0x09, 0x7E, 0x08, 0x00,  // f
  0x3E, 0x52, 0x52, 0x52, 0x0C, 0x00,  // g
  0x78, 0x04, 0x04, 0x08, 0x7F, 0x00,  // h
  0x00, 0x40, 0x7D, 0x44, 0x00, 0x00,  // i
  0x3D, 0x44, 0x40, 0x20, 0x00, 0x00,  // j
  0x44, 0x28, 0x10, 0x7F, 0x00, 0x00,  // k
  0x00, 0x40, 0x7F, 0x41, 0x00, 0x00,  // l
  0x78, 0x04, 0x18, 0x04, 0x7C, 0x00,  // m
  0x78, 0x04, 0x04, 0x08, 0x7C, 0x00,  // n
  0x38, 0x44, 0x44, 0x44, 0x38, 0x00,  // o
  0x08, 0x14, 0x14, 0x18, 0x7C, 0x00,  // p
  0x7C, 0x14, 0x14, 0x14, 0x08, 0x00,  // q
  0x08, 0x04, 0x04, 0x08, 0x7C, 0x00,  // r
  0x20, 0x54, 0x54, 0x54, 0x48, 0x00,  // s
  0x20, 0x40, 0x44, 0x3F, 0x04, 0x00,  // t
  0x7C, 0x20, 0x40, 0x40, 0x3C, 0x00,  // u
  0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00,  // v
  0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,  // w
  0x44, 0x28, 0x10, 0x28, 0x44, 0x00,  // x
  0x3C, 0x50, 0x50, 0x50, 0x0C, 0x00,  // y
  0x44, 0x4C, 0x54, 0x64, 0x44, 0x00,  // z
  0x18, 0x3C, 0x78, 0x3C, 0x18, 0x00,  // {	ini lambang hati
  0xC6, 0xEE, 0xFE, 0xEE, 0xC6, 0x00,  // |	ini lambang hourglass
  0x00, 0x06, 0x09, 0x09, 0x06, 0x00,  // }	ini lambang derajat
  0x10, 0x20, 0x10, 0x08, 0x10, 0x00  // ~
};

/*
  ------------------------------------------------------
  Program Setup yang dijalankan sekali saja
  ------------------------------------------------------
*/
void setup()
{
  //Inisialisasi Serial Port
  Serial.begin(9600);
  // Prescaler = FCPU/64
//  TCCR2B |= 1 << CS22;
//  //Enable Overflow Interrupt Timer 0
//  TIMSK2 |= 1 << TOIE2;
//  //Nol kan Nilai Counter / inisialisasi counter
//  TCNT2 = 0;
  //Inisialisasi DDR yanng terhubung ke IC Shift Reg
  HC595Init();
  //Inisialisasi Pin LED sebagai Output


  //jika nilai Parameter di EEPROM telah terkonfigurasi, maka Baca Nilainya, Bila tidak pakai nilai default
  //        if(EEPROM.read(Param_Configure)==128)
  //        {
  //            Serial.println(F("Baca Param"));
  //            //Ambil nilai jumlah baris dan kolom yang terdapat pada EEPROM, tanpa nilai yang benar, maka display akan kacau
  //            DISP_ROW_CNT  = EEPROM.read(Display_Row);
  ////            DISP_COL_CNT  = EEPROM.read(Display_Column);
  //            //Ambil nilai Scrolling Speed dan Display Mode dari EEPROM
  //            temp=EEPROM.read(Scroll_Speed);
  //            Scr_Speed = temp<<8;
  //             temp=EEPROM.read(Scroll_Speed+1);
  //            Scr_Speed |= temp;
  //             Serial.println(F("Selesai Baca Param"));
  //        }

  //jika Text di EEPROM telah terkonfigurasi, maka Baca Nilainya, Bila tidak pakai nilai default
  //  if (EEPROM.read(Text_Configure) == 128)
  //  {
  //    // Matikan Global Interrupt
  //    cli();
  //    Serial.println(F("Baca Text"));
  //    //Ambil isi teks dari EEPROM
  //    for (a = 0; a < Text_Size; a++)
  //    {
  //      text[a] = EEPROM.read(Display_Text + a);
  //    }
  //    Serial.println(F("Selesai Baca Text"));
  //    // Aktifkan Global Interrupt
  //    sei();
  //  }
  //Ambil panjang dari string 'text'
  length = strlen(text);

  a2 = a3 = 0;
}

/*
  ------------------------------------------------------
  Program Loop yang dijalankan Berulang Selamanya
  ------------------------------------------------------
*/
void loop()
{
  //Program Blink Sederhana Untuk Menunjukan Bahwa Program Aktif

  //  if (disp_mode == Text_Only)
  //  {

  
  cnt++;
  //Program yang menangani scroll text
  if (cnt >= Scr_Speed)
  {
    cnt = 0;

    a2++;
    if (a2 >= 5)
    {
      a2 = 0;
      a3++;
      if (a3 >= length )
      {
        a3 = 0;
      }
    }
  }
  //Kirim 1 baris Data

  chr = a3;
  m = a2;

  for (col = 0; col < DISP_COL_CNT; col++){

//Serial.println (m);
    if (m != 6)
    {
      data = pgm_read_byte( &(smallFont [((text[chr] - ' ') * 6) + m]));
    }

    if ((data & (1 << row)) != 0)
      //kalau nilainya == 1
      digitalWrite(HC595_COL_DS, LOW);
    else
      //kalau nilainya == 0
      digitalWrite(HC595_COL_DS, HIGH);

    HC595_Col_Pulse();

    m++;
    if (m >= 6){
      chr++;
      m = 0;
      if (chr <= 0){
        chr = length;
      }
    }
  }
  //kosongkan row terlebih dahulu sebelum menulis data kolom yang baru, agar tidak timbul artifak pada display
  BlankRow();
  //keluarkan data kolom yang baru
  HC595_Col_Latch();
  //Aktifkan baris yang ditunjukan oleh 'row'
  SelectRow(row);

  row++;
  if (row == (DISP_ROW_CNT))
  {
    //Apabila telah sampai pada baris terakhir, maka
    //Kembali ke baris pertama
    row = 0;
  }
  //  }

//  if (Serial.available() > 0)
//  {
//    SerialReceiveFunct();
//  }
}
/*
  ------------------------------------------------------
  Fungsi - Fungsi yang digunakan di dalam Program
  ------------------------------------------------------
*/
void SerialReceiveFunct()
{
  //  uart_data[uart_counter] = Serial.read();
  //  uart_counter++;
  //
  //  if(uart_mode==Tulis_Text)
  //  {
  //  	Text_Counter++;
  //  	if(Text_Counter>Text_Size || uart_data[0]==Text_Data_End)
  //  	{
  //  		Text_Counter=0;
  //  		uart_mode=Perintah;
  //  		length=strlen(text);
  //                //Serial.println(F("text ditulis"));
  //  	}
  //  	else
  //  	{
  //  		text[Text_Counter-1]=uart_data[0];
  //  	}
  //  	uart_counter=0;
  //  }
  //  else if(uart_mode==Perintah)
  //  {
  //  	if(uart_data[0]==Text_Data)
  //  	{
  //  		if(uart_counter==1)
  //  		{
  //  			delete_text();
  //  		}
  //  		uart_mode=Tulis_Text;
  //  		uart_counter=0;
  //  	}
  //  	else if(uart_data[0]==Display_ON)
  //  	{
  //  		//Nyalakan Kembali timer untuk menyalakan Display, dengan Prescaler = FCPU/64
  //  		TCCR2B|= 1<<CS22;
  //  		uart_counter=0;
  //  	}
  //  	else if(uart_data[0]==Display_OFF)
  //  	{
  //  		//Matikan Timer 2, yang berarti Matikan Display
  //  		TCCR2B&= ~(1<<CS22);
  //  		//kosongkan pilihan row agar display terlihat kosong
  //  		BlankRow();
  //  		uart_counter=0;
  //  	}
  //
  //  	if(uart_counter==3)
  //  	{
  //  		uart_counter=0;
  //  		if(uart_data[0]==Set_Speed)
  //  		{
  //  			Scr_Speed = uart_data[2]<<8;
  //  			Scr_Speed  |= uart_data[1];
  //                        //Serial.println(F("set speed"));
  //  		}
  //  		else if(uart_data[0]==Set_Column)
  //  		{
  //  			DISP_COL_CNT  = uart_data[1];
  //                        //Serial.println(F("set kolom"));
  //  		}
  //  		else if(uart_data[0]==Set_Row)
  //  		{
  //  			DISP_ROW_CNT  = uart_data[1];
  //                        Serial.println(F("set baris"));
  //  		}
  //  		else if(uart_data[0]==Save_Config)
  //  		{
  //                        EEPROM.write(Display_Row, DISP_ROW_CNT);
  //                        EEPROM.write(Display_Column, DISP_COL_CNT);
  //                        temp = Scr_Speed>>8;
  //                        EEPROM.write(Scroll_Speed, temp);
  //                        temp = Scr_Speed;
  //                        EEPROM.write(Scroll_Speed+1, temp);
  //                        EEPROM.write(Param_Configure,128);
  //                        Serial.println(F("Param_Configured"));
  //  		}
  //  		else if(uart_data[0]==Save_Text)
  //  		{
  //  			for(temp=0;temp<Text_Size;temp++)
  //  			{
  //                                EEPROM.write(Display_Text+temp, text[temp]);
  //  			}
  //                        EEPROM.write(Text_Configure,128);
  //                        Serial.println(F("Text_Configured"));
  //  		}
  //  		else if(uart_data[0]==Debug)
  //  		{
  //  			Send_Data=1;
  //  		}
  //  	}
  //  }
}

void delete_text(void)
{
  length = 0;
  for (temp = 0; temp < Text_Size; temp++)
  {
    text[temp] = 0;
  }
}

void HC595Init()
{
  //Ini adalah fungsi untuk menginisialisasi port mikrokontroler yang terhubung dengan Shift Register
  pinMode(HC595_COL_SHCP, OUTPUT);
  pinMode(HC595_COL_STCP, OUTPUT);
  pinMode(HC595_COL_DS, OUTPUT);
  pinMode(HC595_ROW_SHCP, OUTPUT);
  pinMode(HC595_ROW_STCP, OUTPUT);
  pinMode(HC595_ROW_DS, OUTPUT);
}


void HC595_Col_Pulse()
{
  //Ini adalah fungsi untuk memberikan clock pada ic Shift Register bagian kolom
  digitalWrite(HC595_COL_SHCP, HIGH);
  digitalWrite(HC595_COL_SHCP, LOW);
}

void HC595_Col_Latch()
{
  //Ini adalah fungsi untuk men latch (mengeluarkan) nilai pada ic shift reg bagian kolom
  digitalWrite(HC595_COL_STCP, HIGH);
  digitalWrite(HC595_COL_STCP, LOW);
}


void SelectRow(uint8_t rows)
{
  for (a = 0; a < rows; a++)
  {
    digitalWrite(HC595_ROW_DS, HIGH);
    digitalWrite(HC595_ROW_SHCP, HIGH);
    digitalWrite(HC595_ROW_SHCP, LOW);
  }
  digitalWrite(HC595_ROW_DS, LOW);
  digitalWrite(HC595_ROW_SHCP, HIGH);
  digitalWrite(HC595_ROW_SHCP, LOW);
  rows++;
  for (a = rows; a < DISP_ROW_CNT; a++)
  {
    digitalWrite(HC595_ROW_DS, HIGH);
    digitalWrite(HC595_ROW_SHCP, HIGH);
    digitalWrite(HC595_ROW_SHCP, LOW);
  }
  //Keluarkan Pilihan Baris
  digitalWrite(HC595_ROW_STCP, HIGH);
  digitalWrite(HC595_ROW_STCP, LOW);
}

void BlankRow()
{
  for (a = 0; a < DISP_ROW_CNT; a++)
  {
    digitalWrite(HC595_ROW_DS, HIGH);
    digitalWrite(HC595_ROW_SHCP, HIGH);
    digitalWrite(HC595_ROW_SHCP, LOW);
  }
  //Keluarkan Pilihan Baris
  digitalWrite(HC595_ROW_STCP, HIGH);
  digitalWrite(HC595_ROW_STCP, LOW);
}

/*
  ------------------------------------------------------
  Rutin Interrupt / Interrupt Service Routine (ISR)
  ------------------------------------------------------
*/
//ISR(TIMER2_OVF_vect)
//{
//  /*
//    Ini adalah rutin interrupt timer 0
//    Yang berfungsi untuk mengupdate display
//  */
//  //variabel yang berfungsi untuk me reset Variabel uart apabila uart tidak aktif dalam beberapa waktu
//  //uart_timeout++;
//
//
//  //Reset nilai variabel yang dipakai UART apabila waktu timeout terlewati, agar tidak terjadi error apabila komunikasi UART terganggu
//  //if(uart_timeout>=Time_Out)
//  //{
//  //	uart_timeout=0;
//  //	uart_counter=0;
//  //}
//}
