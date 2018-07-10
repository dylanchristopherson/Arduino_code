#include <Adafruit_CircuitPlayground.h>

float temp;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  temp=CircuitPlayground.temperatureF();

  Serial.println("The temperature is: ");
  Serial.println(temp);
}
