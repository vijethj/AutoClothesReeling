#include <dht.h>
#define dht_apin A2 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
dht DHT;
int buzzer = 9;
const int pinLED = 13;
const int pinLDR = A1;
const int pinDO = 2;
const int pinAO = A0;
int val_analog;
int val_digital;
int state = 0; // 0 is out 1 is in
int en1 = 12;
int in1 = 11;
int in2 = 10;
int en2 = 6;
int in3 = 5;
int in4 = 2;
int smokeA0 = A3;
//int smokeD0 = D3;
int sensorThres = 600;
int ldrThres = 500;
void setup() {
pinMode(smokeA0, INPUT);
//pinMode(smokeD0, OUTPUT);
lcd.begin(); 
lcd.backlight();
Serial.begin(9600);
pinMode(3, INPUT);
pinMode(pinLED, OUTPUT);
pinMode(pinLDR, INPUT);
pinMode(pinDO, INPUT);
pinMode(pinAO, INPUT);
pinMode(en1, OUTPUT);
pinMode(en2, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(buzzer, OUTPUT);
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
Serial.println("DHT11 Humidity & temperature Sensor");
}

void inside() {
digitalWrite (pinLED, HIGH);
analogWrite(en1,125);
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);
analogWrite(en2,125);
digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);

Serial.println("go in"); 
}

void outside() {
digitalWrite (pinLED, LOW);
analogWrite(en1,125);
digitalWrite(in1,HIGH);
digitalWrite(in2,LOW);
analogWrite(en2,125);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);

Serial.println("go out");
}

void off() {
analogWrite(en1,0);
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
analogWrite(en2,0);
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
Serial.println("off");
delay(1000);
}

void loop() {     
//noTone(buzzer);
digitalWrite(buzzer , HIGH);     
DHT.read11(dht_apin);    
Serial.print("Current humidity = ");
Serial.print(DHT.humidity);
Serial.print("%  ");
Serial.print("temperature = ");
Serial.print(DHT.temperature); 
Serial.println("C  ");
delay(2000);
int analogSensor = analogRead(smokeA0);
Serial.print("Pin A3: ");
Serial.println(analogSensor);
int ldrStatus = analogRead(pinLDR);
Serial.print("ldr : ");
Serial.println(ldrStatus);
val_digital=digitalRead(pinDO);
val_analog=analogRead(pinAO);
Serial.println(val_analog);
delay(500);
/*if (ldrStatus <200){
  inside(); delayMicroseconds(1);
  lcd.setCursor(0,1);
  lcd.print("Clothes Going In");
  off(); delay(500);
  lcd.clear();
}*/
if (digitalRead(3) == HIGH)
{
//inside(); delayMicroseconds(1);
lcd.setCursor(0,0);  
lcd.print(DHT.humidity);
lcd.setCursor(0,1);
lcd.print(DHT.temperature);
digitalWrite(buzzer , HIGH); 
//state = 1;
off(); delay(500);
lcd.clear();
}
else if (val_analog < 600 && ldrStatus > ldrThres) {                         //Could Rain
lcd.setCursor(0,0);  
lcd.print("Water Detected");
lcd.setCursor(0,1);
lcd.print("Check the Clothes!");
//tone(buzzer, 100, 100); 
digitalWrite(buzzer , LOW); 
delay(100);        
//noTone(buzzer);     
delay(100); 
//state = 1;
off(); delay(500);
lcd.clear();
}
else if (ldrStatus > ldrThres && analogSensor > sensorThres) {                   //No Rain and No Smoke
//if (digitalRead(pinLED)==HIGH) {
//if (val_digital == HIGH) {
//outside(); delay(50);
lcd.setCursor(0,0);  
lcd.print("No Smoke Or Rain");
lcd.setCursor(0,1);
lcd.print("Have a Nice Day!");
//noTone(buzzer);
digitalWrite(buzzer , HIGH); 
delay(100);
//state = 0;
off(); delay(500);
lcd.clear();
}
//}
//}
else if (ldrStatus <=ldrThres && val_analog < 600 && analogSensor > sensorThres) {               //Raining and no smoke
//inside(); delayMicroseconds(1);
lcd.setCursor(0,0);  
lcd.print("Raining");
lcd.setCursor(0,1);
lcd.print("Bring Clothes In!");
//tone(buzzer, 100, 100); // Send 1KHz sound signal...
digitalWrite(buzzer , LOW); 
delay(100);        // ...for 1 sec
//noTone(buzzer);     // Stop sound...
delay(100); 
//state = 1;
off(); delay(500);
lcd.clear();
}
else if (ldrStatus <=ldrThres && val_analog > 600 && analogSensor > sensorThres) {               //Night time
lcd.setCursor(0,0);  
lcd.print("Dark Outside");
lcd.setCursor(0,1);
lcd.print("Good Night");
//state = 1;
//noTone(buzzer);
digitalWrite(buzzer , HIGH); 
delay(100);
off(); delay(500);
lcd.clear();
}
else if (ldrStatus <=ldrThres && analogSensor < sensorThres) {               //Raining and Smoky
//if (val_digital == LOW) {
//inside(); delayMicroseconds(1);
lcd.setCursor(0,0);  
lcd.print("Raining or Smoky");
lcd.setCursor(0,1);
lcd.print("Bring Clothes In!");
digitalWrite(buzzer , LOW); 
//tone(buzzer, 100, 100); // Send 1KHz sound signal...
delay(100);        // ...for 1 sec
//noTone(buzzer);     // Stop sound...
delay(100); 
//state = 1;
off(); delay(500);
lcd.clear();
//}
}
else if (ldrStatus >ldrThres && val_analog > 600 && analogSensor < sensorThres ) {             //No Rain and Smoky
//inside(); delayMicroseconds(1);
lcd.setCursor(0,0);
lcd.print("Smoke Detected!");
lcd.setCursor(0,1);
lcd.print("Bring Clothes In!");
digitalWrite(buzzer , LOW); 
//tone(buzzer, 100, 100); // Send 1KHz sound signal...
delay(100);        // ...for 1 sec
//noTone(buzzer);     // Stop sound...
delay(100); 
//state = 1;
off(); delay(500);
lcd.clear();
}
delay(100);

}
