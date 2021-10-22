#include <avr/pgmspace.h>
#include <Wire.h>
#include <RTClib.h>
//#include <IRremote.h>
#define TOTMATRIX 5
#define FONT_COLS 8
#define FONT_ROWS 8
//int RECV_PIN = 2;
//int IR_VCC=9;
//int IR_GND=10;

//IRrecv irrecv(RECV_PIN);
//decode_results results;

volatile boolean setupMode=false,setupInterrupted=false;
String setupMsg;

RTC_DS3231 RTC;
char *days[7]={"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};
String datestr;
String zero;
DateTime now;
uint16_t setupYear=2000;
uint8_t setupMonth=1,setupDay=1,setupHour=1,setupMin=0;
int mode=-1; //-1 setup info, 0 year,1 month, 2 day, 3 hour, 4 min

/*
 * IR REMOTE CODES FOR NEC 2FD40BF 2  2FDA05F  5  2FDD827 UP  2FDF807 Down  2FD22DD OK
 */

//connection pin layout matrix from led side
/*
* vcc,gnd,latch1,clock1,data1,lat2,clock2,data2
* arduino pins are
* vcc,gnd,3,4,5,6,7,8
*/

// Define 74HC595 connections.
int data1=2;//dat
int clock1 =4;//clock1
int latch1=3; //latch



int dataPin2 = 7;  //Arduino pin connected to grey Data 14 SER of 74HC595
int clockPin2 = 5; //Arduino pin connected to white Clock 11 SRCLK of 74HC595
int latchPin2 = 6; //Arduino pin connected to yellow Latch 12 RCLK of 74HC595



uint8_t Buffer[8][TOTMATRIX] = {
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};

const uint8_t CharData[][8] PROGMEM ={ 
	{0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	//{0xff,0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},   // 0x20, Space 
	{0x00,0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04},   // 0x21, ! 
	{0x00,0x09, 0x09, 0x12, 0x00, 0x00, 0x00, 0x00},   // 0x22, " 
	{0x00,0x0a, 0x0a, 0x1f, 0x0a, 0x1f, 0x0a, 0x0a},   // 0x23, # 
	{0x00,0x04, 0x0f, 0x14, 0x0e, 0x05, 0x1e, 0x04},   // 0x24, $ 
	{0x00,0x19, 0x19, 0x02, 0x04, 0x08, 0x13, 0x13},   // 0x25, % 
	{0x00,0x04, 0x0a, 0x0a, 0x0a, 0x15, 0x12, 0x0d},   // 0x26, & 
	{0x00,0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00},   // 0x27, ' 
	{0x00,0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02},   // 0x28, ( 
	{0x00,0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08},   // 0x29, ) 
	{0x00,0x04, 0x15, 0x0e, 0x1f, 0x0e, 0x15, 0x04},   // 0x2a, * 
	{0x00,0x00, 0x04, 0x04, 0x1f, 0x04, 0x04, 0x00},   // 0x2b, + 
	{0x00,0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x08},   // 0x2c, , 
	{0x00,0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00},   // 0x2d, - 
	{0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c},   // 0x2e, . 
	{0x00,0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10},   // 0x2f, / 
	{0x00,0x0e, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0e},   // 0x30, 0 
	{0x00,0x04, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x0e},   // 0x31, 1 
	{0x00,0x0e, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1f},   // 0x32, 2 
	{0x00,0x0e, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0e},   // 0x33, 3 
	{0x00,0x02, 0x06, 0x0a, 0x12, 0x1f, 0x02, 0x02},   // 0x34, 4 
	{0x00,0x1f, 0x10, 0x1e, 0x01, 0x01, 0x11, 0x0e},   // 0x35, 5 
	{0x00,0x06, 0x08, 0x10, 0x1e, 0x11, 0x11, 0x0e},   // 0x36, 6 
	{0x00,0x1f, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08},   // 0x37, 7 
	{0x00,0x0e, 0x11, 0x11, 0x0e, 0x11, 0x11, 0x0e},   // 0x38, 8 
	{0x00,0x0e, 0x11, 0x11, 0x0f, 0x01, 0x02, 0x0c},   // 0x39, 9 
	{0x00,0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00},   // 0x3a, : 
	{0x00,0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x04, 0x08},   // 0x3b, ; 
	{0x00,0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02},   // 0x3c, < 
	{0x00,0x00, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x00},   // 0x3d, = 
	{0x00,0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08},   // 0x3e, > 
	{0x00,0x0e, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04},   // 0x3f, ? 

	{0x00,0x0e, 0x11, 0x17, 0x15, 0x17, 0x10, 0x0f},   // 0x40, @ 
	{0x00,0x04, 0x0a, 0x11, 0x11, 0x1f, 0x11, 0x11},   // 0x41, A 
	{0x00,0x1e, 0x11, 0x11, 0x1e, 0x11, 0x11, 0x1e},   // 0x42, B 
	{0x00,0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e},   // 0x43, C 
	{0x00,0x1e, 0x09, 0x09, 0x09, 0x09, 0x09, 0x1e},   // 0x44, D 
	{0x00,0x1f, 0x10, 0x10, 0x1c, 0x10, 0x10, 0x1f},   // 0x45, E 
	{0x00,0x1f, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10},   // 0x46, F 
	{0x00,0x0e, 0x11, 0x10, 0x10, 0x13, 0x11, 0x0f},   // 0x37, G 
	{0x00,0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11},   // 0x48, H 
	{0x00,0x0e, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0e},   // 0x49, I 
	{0x00,0x1f, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0c},   // 0x4a, J 
	{0x00,0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11},   // 0x4b, K 
	{0x00,0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1f},   // 0x4c, L 
	{0x00,0x11, 0x1b, 0x15, 0x11, 0x11, 0x11, 0x11},   // 0x4d, M 
	{0x00,0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11},   // 0x4e, N 
	{0x00,0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e},   // 0x4f, O 
	{0x00,0x1e, 0x11, 0x11, 0x1e, 0x10, 0x10, 0x10},   // 0x50, P 
	{0x00,0x0e, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0d},   // 0x51, Q 
	{0x00,0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11},   // 0x52, R 
	{0x00,0x0e, 0x11, 0x10, 0x0e, 0x01, 0x11, 0x0e},   // 0x53, S 
	{0x00,0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04},   // 0x54, T 
	{0x00,0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e},   // 0x55, U 
	{0x00,0x11, 0x11, 0x11, 0x11, 0x11, 0x0a, 0x04},   // 0x56, V 
	{0x00,0x11, 0x11, 0x11, 0x15, 0x15, 0x1b, 0x11},   // 0x57, W 
	{0x00,0x11, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x11},   // 0x58, X 
	{0x00,0x11, 0x11, 0x0a, 0x04, 0x04, 0x04, 0x04},   // 0x59, Y 
	{0x00,0x1f, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1f},   // 0x5a, Z 
	{0x00,0x0e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e},   // 0x5b, [ 
	{0x00,0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01},   // 0x5c, \ 
	{0x00,0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e},   // 0x5d, ] 
	{0x00,0x04, 0x0a, 0x11, 0x00, 0x00, 0x00, 0x00},   // 0x5e, ^ 
	{0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f}   // 0x5f, _ 
}; 

unsigned  speed;
uint8_t i,j, l, k, row, scroll, temp, shift_step=1;
char  index;

void Send_Data(uint8_t rw){
	uint8_t num;
	digitalWrite(latch1, LOW);  //Hold latchPin LOW for as long as we're transmitting data
	for (num = 0;num <TOTMATRIX; num++) {

		shiftOut(data1, clock1, LSBFIRST, Buffer[rw][num]);   //Transmit data.
		// Apply clock on latch1
		//delayMicroseconds(45);
	}

	digitalWrite(latch1,HIGH);
}

/* CharData is a two dimensional constant array that holds the 8-bit column values of
individual rows for ASCII characters on a 8x8 matrix format.
*/

void setup() {
	Serial.begin(9600);
	pinMode(data1,OUTPUT);
	pinMode(clock1,OUTPUT);
	pinMode(latch1,OUTPUT);

	pinMode(dataPin2,OUTPUT);
	pinMode(clockPin2,OUTPUT);
	pinMode(latchPin2,OUTPUT);
//  pinMode(IR_VCC,OUTPUT);
//  pinMode(IR_GND,OUTPUT);
//  digitalWrite(IR_VCC,HIGH);
//  digitalWrite(IR_GND,LOW);
  
//  irrecv.enableIRIn(); // Start the receiver

	Wire.begin();
	RTC.begin();

//	if (! RTC.isrunning()) {
//		Serial.println(F("RTC is NOT running!"));
//		// following line sets the RTC to the date & time this sketch was compiled
//		//RTC.adjust(DateTime(__DATE__, __TIME__));
//	}

// attachInterrupt(0, enableSetup, CHANGE);

}
//
//void enableSetup(){
//  //setupMode=true;
////  setupInterrupted=true;
//   //detachInterrupt(0);
//   if (irrecv.decode(&results) && mode==-1) {
//      Serial.println(results.value,HEX);
//      if(results.value==0x2FDA05F){
//        setupMode=true;
//        setupInterrupted=true;
//        detachInterrupt(0);
//      }
//      
//      irrecv.resume();
//      
//   }
//              
//}

void showScrollingTime(){
	now = RTC.now();

	String mins=now.minute()>9?String(now.minute()):"0"+String(now.minute());
	String secs=now.second()>9?String(now.second()):"0"+String(now.second());

	datestr=String(now.year())+"/"+String(now.month())+"/"+String(now.day())+" "+String(now.hour())+":"+mins+":"+secs+", "+days[now.dayOfTheWeek()]+"  ";
	//datestr="Sagar  ";



	int len=datestr.length();
	//Serial.println(len,DEC);
	for (k=0; k<len; k++){
		//Serial.println(k);
		for (scroll=0; scroll<(FONT_COLS/shift_step); scroll++) {//8 for 8X8 and here is 7
			//Serial.println(scroll);
			for (row=0; row<FONT_ROWS; row++){
				index = datestr.charAt(k);

				temp = pgm_read_byte(&(CharData[index-32][row]));
				/*for(j=TOTMATRIX-1; j>=0; j--){
				if(j>0) {
				Buffer[row][j] = (Buffer[row][j] << shift_step) | (Buffer[row][j-1] >> (8-shift_step)); //change 8 to 7 if u need thick font spaces
				}
				else
				{
				Buffer[row][j] = (Buffer[row][j] << shift_step)| (temp >> ((8-shift_step)-scroll*shift_step));
				}

				}*/

				Buffer[row][4] = (Buffer[row][4] << shift_step) | (Buffer[row][3] >> (8-shift_step)); //change 8 to 7 if u need thick font spaces
				Buffer[row][3] = (Buffer[row][3] << shift_step) | (Buffer[row][2] >> (8-shift_step));
				Buffer[row][2] = (Buffer[row][2] << shift_step) | (Buffer[row][1] >> (8-shift_step));
				Buffer[row][1] = (Buffer[row][1] << shift_step) | (Buffer[row][0] >> (8-shift_step));
				Buffer[row][0] = (Buffer[row][0] << shift_step)| (temp >> ((8-shift_step)-scroll*shift_step));



			}//row
			printMatrix(5);
		} // scroll
	} // k

}

void showBlinkTime(){

	now = RTC.now();
	String hrs=now.hour()>9?String(now.hour()):"0"+String(now.hour());
	String mins=now.minute()>9?String(now.minute()):"0"+String(now.minute());

	datestr=hrs+":"+mins;
	String datestr1=hrs+" "+mins;
	//datestr="     ";


	for (k=0; k<datestr.length()+4; k++){
		if((k+1)%TOTMATRIX==0){
			//Serial.println(k);
			prepareMessage(datestr);
			printMatrix(500);
			//lets make blink

			prepareMessage(datestr1);
			printMatrix(500);

			prepareMessage(datestr);
			printMatrix(500);

			prepareMessage(datestr1);
			printMatrix(500);

			prepareMessage(datestr);
			printMatrix(500);

			//code for move up goes here
			///........................code.........for move up
			uint8_t d,slide;
			for(slide=0; slide<FONT_ROWS; slide++){ 
				for (row=0; row<FONT_ROWS; row++){

					for(d=0; d<5; d++){

						Buffer[row][d] = Buffer[row+1][d];
						if(row==FONT_ROWS-1){ // if last row, clear it
							Buffer[row][d] =0;

						}

					}




				}//row
				printMatrix(10);
			} 


		}// end if k%TOTMATRIX

	} // k


}


void showMessage(String msg){
  for (k=0; k<msg.length(); k++){
    if((k+1)%TOTMATRIX==0 || k==msg.length()-1){
      
      prepareMessage(msg);
      printMatrix(1);
      
    }// end if k%TOTMATRIX

  } // k
}

void showBlinkMessage(String msg) {
    
    showMessage(msg);
    showMessage("     ");
    showMessage(msg);
}

void prepareMessage(String value){

	//Serial.println(scroll);
	for (row=0; row<FONT_ROWS; row++){
		/*for(j=TOTMATRIX-1; j>=0; j--){

		Buffer[row][j] = pgm_read_byte(&(CharData[datestr[k-j]-32][row]));

		}*/

		Buffer[row][4] = pgm_read_byte(&(CharData[value[k-4]-32][row]))<<2;
		Buffer[row][3] = pgm_read_byte(&(CharData[value[k-3]-32][row]))<<2;
		Buffer[row][2] = pgm_read_byte(&(CharData[value[k-2]-32][row]))<<2;
		Buffer[row][1] = pgm_read_byte(&(CharData[value[k-1]-32][row]))<<2;
		Buffer[row][0] = pgm_read_byte(&(CharData[value[k-0]-32][row]))<<2;

	}//row
}



void printMatrix(uint8_t refresh)
{
	speed=refresh;
	for(l=0; l<speed;l++){
		for (i=0; i<FONT_ROWS; i++) { 

      if(setupInterrupted==true) return; //enter to setupmode immediately;

			uint8_t rowbit;

			rowbit = (1 << i); //~ for  ULN uncomment this

			//rowbit = ~(1 << i); //for proteus uncomment this

			digitalWrite(latchPin2, LOW);  //Hold latchPin LOW for as long as we're transmitting data
			shiftOut(dataPin2, clockPin2, LSBFIRST, rowbit);   //Transmit data. to row shift register IC

			Send_Data(i);   //this function sends output to column shift register IC
			digitalWrite(latchPin2, HIGH);  //Hold latchPin LOW for as long as we're transmitting data

			//Serial.println(i);
			delayMicroseconds(450);
			//Serial.println(m);
		}  // i
	}//l 
}

void loop(){

          
    
          while(setupMode) {
            Serial.println("Setup Mode");
//            setupInterrupted=false;
//            if (irrecv.decode(&results)) {
//              //Serial.println(results.value,HEX);
//              switch(results.value){
//                
//                case 0x2FDD827: // UP  
//                  //Serial.print("Saga");
//                  if(mode==0) {
//                    setupYear+=1;
//                    min(2050,setupYear);
//                    Serial.print(setupYear);
//                  }
//                  else if(mode==1) {
//                    setupMonth+=1;
//                    min(12,setupMonth);
//                  }
//                  else if(mode==2) {
//                    setupDay+=1;
//                    min(31,setupDay);
//                  }
//                  else if(mode==3) {
//                    setupHour+=1;
//                    min(24,setupHour);
//                  }
//                  else if(mode==4) {
//                    setupMin+=1;
//                    min(60,setupMin);
//                  }
//                  
//                break;
//                case 0x2FDF807: //Down
//                
//                  if(mode==0) {
//                    setupYear-=1;
//                    max(2000,setupYear);    
//                  }
//                  else if(mode==1) {
//                    setupMonth-=1;
//                    max(1,setupMonth);
//                  }
//                  else if(mode==2) {
//                    setupDay-=1;
//                    max(1,setupDay);
//                  }
//                  else if(mode==3) {
//                    setupHour-=1;
//                    max(1,setupHour);
//                  }
//                  else if(mode==4) {
//                    setupMin-=1;
//                    max(1,setupMin);
//                  }
//                  //delay(1000);
//                break;
//                case 0x2FD22DD: //OK
//                  mode++;
//                  if(mode>4) {
//                    //save here
//                    RTC.adjust(DateTime(setupYear,setupMonth,setupDay,setupHour,setupMin,0));
//                    setupMode=false;
//                    attachInterrupt(0, enableSetup, CHANGE);
//                    Serial.println("SETUP MODE EXITED");
//                    //interrupts();
//                    
//                    
//                    
//                  }
//                  //delay(1000);
//                break;
//                
//             }
//
//             irrecv.resume(); // Receive the next value
//
//             
//          }

       

          //now show message
          if(mode==-1) {
            showBlinkMessage("SETUP");
          }
          else if(mode==0) {
            showBlinkMessage("Y"+String(setupYear));
            
            //showBlinkTime();
          }
          else if(mode==1) {
            if(setupMonth<=9) 
                zero="0";
            else
                zero="";
                
                
            showBlinkMessage("M= "+zero+String(setupMonth));
          }
          else if(mode==2) {
            if(setupDay<=9) 
                zero="0";
            else
                zero="";
            showBlinkMessage("D= "+zero+String(setupDay));
          }
          else if(mode==3) {
            if(setupHour<=9) 
                zero="0";
            else
                zero="";
            showBlinkMessage("H= "+zero+String(setupHour));
          }
          else if(mode==4) {
            if(setupMin<=9) 
                zero="0";
            else
                zero="";
            showBlinkMessage("MI="+zero+String(setupMin));
          }
          //delay(100);
          
        } 
     
  
  
	digitalWrite(13,HIGH);
	//showMessage();
	//scrollMessage();
  mode=-1;
	showScrollingTime();
	digitalWrite(13,LOW);
	delay(700);
	digitalWrite(13,HIGH);
	showBlinkTime();
	digitalWrite(13,LOW);

  
}
