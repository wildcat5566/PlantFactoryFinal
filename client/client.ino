#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Timer.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Timer readSensorTimer;
Timer commTimer;

float rh = 0;
float tem = 0;
int co2 = 0; //處理後有實際作用的讀值

float rhNow = 0; 
float temNow = 0; 
int co2Now = 0;//未處理讀值；若亂跳則維持上一讀值

float rhLast, temLast;
int co2Last;


float rhDelta, temDelta;
int co2Delta;

float rhTarget = 0;
float temTarget = 0;
int co2Target = 0;//store targets from python
int lightTarget = 0;

long timer = 0;
long sample = 0;
int count = 0;

float rhRecord = 0;
float temRecord = 0;
int co2Record = 0;

int hpTime = 0, huTime = 0, heTime = 0;
int heatpumpAccess = 0, humidifierAccess = 0, heaterAccess = 0;

//*****
//double temDeltaMax = 0.1;
//double temDeltaMin = -0.4;
//*****

const int co2Led1 = 22;
const int co2Led0 = 23;
const int rhLed1 = 24;
const int rhLed0 = 25;
const int temLed1 = 26;
const int temLed0 = 27;

const int co2valveLed = 30;
const int heatpumpLed = 32;
const int humidifierLed = 34;
const int heaterLed = 36;

int light1 = 2;
int light2 = 3;
int light3 = 4;
int CO2 = 5;
int heatpump = 6;
int compressor = 7;
int humidifier = 8;
int fan = 9;
int heater = 10;

int heaterOpen = 0;
int heatpumpOpen = 0;
int humidifierOpen = 0;
int co2Open = 0;

void setup() {
  Serial3.begin(28800);
  Serial.begin(9600);
  
  readSensorTimer.every(50, readSensor);
  commTimer.every(60000, PythonComm);

  //Serial.println("0");

  pinMode(co2Led1, OUTPUT);
  pinMode(co2Led0, OUTPUT);
  pinMode(rhLed1, OUTPUT);
  pinMode(rhLed0, OUTPUT);
  pinMode(temLed1, OUTPUT);
  pinMode(temLed0, OUTPUT);

  pinMode(co2valveLed, OUTPUT);
  pinMode(heatpumpLed, OUTPUT);
  pinMode(humidifierLed, OUTPUT);
  pinMode(heaterLed, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Glass Heart");
  lcd.setCursor(0,1);
  lcd.print("Break Everywhere");
  delay(3000);
  lcd.clear();
  
  //rhTarget = 80.00;
  //temTarget = 20.00;
  //co2Target = 800;

  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(CO2, OUTPUT);
  pinMode(heatpump, OUTPUT);
  pinMode(compressor, OUTPUT);
  pinMode(humidifier, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);

  digitalWrite(light1 , LOW);
  digitalWrite(light2 , LOW);
  digitalWrite(light3 , LOW);
  digitalWrite(CO2 , LOW);
  digitalWrite(heatpump , LOW);
  digitalWrite(compressor , HIGH);
  digitalWrite(humidifier , LOW);
  digitalWrite(fan , HIGH);
  digitalWrite(heater, LOW);
}

void loop() {
  readSensorTimer.update();
  commTimer.update();
  //Leds(); 跟control直接綁在一起
/*
  if (Serial.available() > 0 && Serial3.available() >= 15){
   if(rhDelta > 0){
    digitalWrite(rhLed1,HIGH);
    digitalWrite(rhLed0,LOW);
  }
  else if(rhDelta<0){
    digitalWrite(rhLed1,LOW);
    digitalWrite(rhLed0,HIGH);
  }
  
  //
  if(temDelta>0){
    digitalWrite(temLed1,HIGH);
    digitalWrite(temLed0,LOW);
  }
  else if(temDelta<0){
    digitalWrite(temLed1,LOW);
    digitalWrite(temLed0,HIGH);
  }
 
  //
  if(co2Delta>0){
    digitalWrite(co2Led1,HIGH);
    digitalWrite(co2Led0,LOW);
  }
  else if(co2Delta<0){
    digitalWrite(co2Led1,LOW);
    digitalWrite(co2Led0,HIGH);
  }
 }
*/

}
