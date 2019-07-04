#include <Servo.h>

// Used for joystick and servo
int servoPin = 3;
Servo Servo1;

int switchPin = 2;
int X_pin = 0;
int Y_pin = 1;

int movX = 0;
int movY = 0;

int position = 0;
int switchTap = 1;

// Used for stepper motors


// This code is ran once
void setup() {

  // Used for stepper motors
  Servo1.attach(servoPin);
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH);
 // Serial.begin(115200);


  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}






void joystick() {
  Serial.print("Switch: ");
  Serial.print(digitalRead(switchPin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");  

  movX = analogRead(X_pin);

  while (movX < 400) {
    if (position >= 180) {
      position = 180;  
    }
    else {
      position = position + 1;
    }
    Servo1.write(position);
    movX = analogRead(X_pin);
    delay(10);
  }

  while (movX > 600) {
    if (position <= 0) {
      position = 0;  
    }
    else {
      position = position - 1;
    }
    Servo1.write(position);
    movX = analogRead(X_pin);
    delay(10);
  }

  switchTap = digitalRead(switchPin);

  Serial.print(switchTap);
  //delay(1000);

  if (switchTap == 0) {
    position = 90;
    Servo1.write(position);
    delay(1000);
  }
}
}
