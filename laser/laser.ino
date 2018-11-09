int Laser = 13;
int voltage = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(Laser, OUTPUT);
  digitalWrite(Laser, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Laser, HIGH);
  voltage = analogRead(A0);
  float voltage1 = voltage * (5.0 / 1023.0);
  Serial.print("laser is on, the voltage is: ");
  Serial.print(voltage1);
  Serial.println();
  delay(50);
  digitalWrite(Laser, LOW);
  voltage = analogRead(A0);
  float voltage2 = voltage * (5.0 / 1023.0);
  Serial.print("the laser is off, the voltage is: ");
  Serial.println(voltage2);
  Serial.println();
  delay(50);

}
