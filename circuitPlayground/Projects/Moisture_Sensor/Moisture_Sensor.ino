#include <Adafruit_CircuitPlayground.h>

uint16_t value;

void setup() {
  Serial.begin(115200);
  Serial.println("Circuit Playground test!");
  CircuitPlayground.begin();
}

void loop() {
  // Moisture sensor reading from input 10
  value = analogRead(10);
  Serial.println(value);
  delay(100);
}
