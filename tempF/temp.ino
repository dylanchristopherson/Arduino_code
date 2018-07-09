#include <Adafruit_CircuitPlayground.h>

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float=temperatureF();

  Serial.println("The temperature is: ");
  Serial.println(float);
}
