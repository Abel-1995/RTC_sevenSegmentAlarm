#include <Wire.h>
#include<EEPROM.h>
#include<RTClib.h>
#include<LiquidCrystal.h>
#define buzzer 9
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;

int next = 8;
int INC = 10;
int setButton = 11;
// int temp = 0, val = 1, temp;

int HOUR, MINUT, SECOND;

void setup(){
  Wire.begin();
  RTC.begin();
  lcd.begin(16, 2);
  pinMode(INC, INPUT);
  pinMode(next, INPUT);
  pinMode(setButton, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(next, HIGH);
  pinMode(setButton, HIGH);
  digitalWrite(next, HIGH);
  digitalWrite(setButton, HIGH);
  digitalWrite(INC, HIGH); 

    lcd.setCursor(0,0);
    lcd.print("Real Time Clock");
    delay(2000);

    if(!RTC.isrunning())
{
//RTC.adjust(DateTime(_DATE_,_TIME_));
}
}

void loop(){
  int temp = 0, val = 1, temp4;
  DateTime now = RTC.now();
  if(digitalRead(setButton) == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Set Alarm ");
    delay(1000);
    here();
    Time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Alarm time");
    lcd.setCursor(0,1);
    lcd.print("updated ");
    delay(1500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time:");
  lcd.setCursor(6,0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);
  lcd.setCursor(0,1);
  lcd.print("Date:");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  check();
  delay(200);
}

void here(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void Time(){
  int Temp = 1, minuts = 0, hours = 0, seconds = 0;
    while(temp == 1)
    {
      if(digitalRead(INC) == 0){
        HOUR++;
        if(HOUR == 24){
          HOUR = 0;
        }
        while(digitalRead(INC) == 0);
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("set Alarm Time");
      lcd.setCursor(0,1);
      lcd.print(HOUR);
      lcd.print(",");
      lcd.print(MINUT);
      lcd.print(":");
      lcd.print(SECOND);
      delay(100);
      if(digitalRead(next) == 0)
      {
        hours1 = HOUR;
        EEPROM.write(add++, hours1);
        temp = 2;
        while(digitalRead(next) == 0);
      }
    }
    while(temp == 2){
      if(digitalRead(INC) == 0){
        MINUT++;
        if(MINUT == 60){
          MINUT = 0;
        }
        while(digitalRead(INC) == 0);
      }
      //lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(HOUR);
      lcd.print(":");
      lcd.print(MINUT);
      lcd.print(":");
      lcd.print(SECOND);
      delay(100);
      if(digitalRead(next) == 0){
        minut = MINUT;
        EEPROM.write(add++, minut);
        temp = 0;
        while(digitalRead(next) == 0);
      }
    }
     delay(1000);
}

void check()
{
  int tem[17];
  for(int i=11; i<17; i++)
  {
    tem[i] = EEPROM.read(i);
  }
  if(HOUR == tem[11] && MINUT == tem[12])
  {
    beep();
    beep();
    beep();
    beep();
    lcd.clear();
    lcd.print("Wake Up......");
    lcd.setCursor(0,1);
    lcd.print("Wake Up......");
    beep();
    beep();
    beep();
    beep();
  }
}
void beep(){
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(250);
}

      
  
