#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
const int pinLED = 13;
const int pinLDR = A1;
const int pinDO = 8;
const int pinAO = A0;
int val_analog;
int val_digital;
int enA = 6;
int in1 = 2;
int in2 = 12;
int enB = 5;
int in3 = 11;
int in4 = 10;
int smokeA0 = A5;

int sensorThres = 400;

void setup() {
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  lcd.begin(); 
lcd.backlight();
pinMode(pinLED, OUTPUT);
pinMode(pinLDR, INPUT);
pinMode(pinDO, INPUT);
pinMode(pinAO, INPUT);
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}
void inside() {
digitalWrite (pinLED, HIGH);
analogWrite(enA,125);
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
analogWrite(enB,125);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);

Serial.println("go in"); 
}

void outside() {
digitalWrite (pinLED, LOW);
analogWrite(enA,125);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
  analogWrite(enB,125);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
Serial.println("go out");
}
void off() {
analogWrite(enA,0);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
analogWrite(enB,0);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
Serial.println("off");
delay(3000);
}
void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    inside(); delayMicroseconds(1);
    lcd.setCursor(0,0);  
    lcd.print("Smoke Detected");
    lcd.setCursor(0,1);
    lcd.print("Clothes Going In");
    off(); delay(500);
    lcd.clear();
  }
  else
  {
    if (ldr
    outside(); delayMicroseconds(1);
    lcd.setCursor(0,0);  
    lcd.print("No Smoke");
    lcd.setCursor(0,1);
    lcd.print("Clothes Are Out");
    off(); delay(500);
    lcd.clear();
  }
  delay(100);
}
