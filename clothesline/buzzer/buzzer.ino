int buzzer=9;
void setup() {
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(buzzer, HIGH);
  //digitalWrite(buzzer, LOW);
  // put your main code here, to run repeatedly:

}
