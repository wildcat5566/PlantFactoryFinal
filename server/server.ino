#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Timer.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

Timer readSensorTimer;
Timer commTimer;
Timer controlTimer;

long timer = 0;
int count = 0;

float rhLast = 0;
float temLast = 0;
int co2Last = 0;

double rh, rhNow, tem, temNow;
int co2, co2Now;

//global vars for samplint & recording
int rhTarget = 0;
int temTarget = 0;
int co2Target = 0;
int lightTarget = 0;

//global vars for control
int light1 = 2;
int light2 = 3;
int light3 = 4;
int CO2 = 5;
int heatpump = 6;
int compressor = 7;
int humidifier = 8;
int fan = 9;
int heater = 10;
int waterpump = 11;

int co2Switch = 30;
int hpSwitch = 32;
int huSwitch = 34;
int heSwitch = 36;

int heaterOpen = 0;
int heatpumpOpen = 0;
int humidifierOpen = 0;
int co2Open = 0;

void setup() {
  Serial3.begin(28800);
  Serial.begin(9600);
  
  readSensorTimer.every(50, readSensor);
  controlTimer.every(50, control);
  commTimer.every(60000, PythonComm);
  
  lcd.begin(16, 2);
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Baby sad but");
  lcd.setCursor(0,1);
  lcd.print("Baby don't say");
  delay(3000);
  lcd.clear();
  
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(CO2, OUTPUT);
  pinMode(heatpump, OUTPUT);
  pinMode(compressor, OUTPUT);
  pinMode(humidifier, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(waterpump, OUTPUT);

  pinMode(heSwitch, INPUT);
  pinMode(hpSwitch, INPUT);
  pinMode(huSwitch, INPUT);
  pinMode(co2Switch, INPUT);

  digitalWrite(light1 , LOW);
  digitalWrite(light2 , LOW);
  digitalWrite(light3 , LOW);
  digitalWrite(CO2 , LOW);
  digitalWrite(heatpump , LOW);
  digitalWrite(compressor , HIGH);
  digitalWrite(humidifier , LOW);
  digitalWrite(fan , HIGH);
  digitalWrite(heater, LOW);
  digitalWrite(waterpump, HIGH);


}

void loop() {
  readSensorTimer.update();
  commTimer.update();
  controlTimer.update();
}
