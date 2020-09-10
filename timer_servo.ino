#include <Wire.h>
#include<Servo.h>
#include "RTClib.h"
int minute;
int hour;


Servo servo1,servo2;
RTC_DS1307 rtc;
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (rs, e, d4, d5, d6, d7)

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup () 
{
  int now();
  
  Serial.begin(9600);
  //lcd.begin(16, 2);
  
  if (! rtc.begin()) 
  {
    Serial.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.print("RTC is NOT running!");
  }
  
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    rtc.adjust(DateTime(2018, 6, 15, 13, 10, 0));// to set the time manualy 
  
}

void loop () 
{
    DateTime now = rtc.now();
    
    //lcd.setCursor(0, 1);
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.print(now.second());
    Serial.print("   ");

    //lcd.setCursor(0, 0);
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(" ,");
    Serial.print(now.day());
    Serial.print('/');
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.year());
    Serial.print("\n");

    servo1.attach(5);
    servo2.attach(6);

   // int timet_t=now(); 
    int x,y,z,a,b,p,q,r;

    y=now.minute();
    x=now.hour();
    z=((now.hour()*60)+now.minute());
    p=1110;
    q=270;
    a=map(z,270,1110,0,120);
    b=map(z,270,1110,120,0);
    Serial.print("a=");
    Serial.print(a);
    Serial.print("\nb=");
    Serial.print(b);
    servo1.write(a);
    servo2.write(b);
    delay(500);
    servo1.detach();
    servo2.detach();
   
    if(z==p){
      //delay(10000);
      q=map(q,270,1110,180,0);
      r=q;
      r=map(r,270,1110,0,180);
      servo1.write(q);
      servo2.write(r);
    }
    delay(59500);
}

