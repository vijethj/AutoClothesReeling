int en1 = 6;
int in1 = 5;
int in2 = 2;
void setup() {
pinMode(en1, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
  // put your setup code here, to run once:
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
}
void inside() {
analogWrite(en1,125);
digitalWrite(in1,LOW);
digitalWrite(in2,HIGH);

Serial.println("go in"); 
}

void loop() { 
inside(); delay(50);
  // put your main code here, to run repeatedly:

}
