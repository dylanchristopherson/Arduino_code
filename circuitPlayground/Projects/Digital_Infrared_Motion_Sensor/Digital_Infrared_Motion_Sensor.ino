#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Circuit Playground test!");

  CircuitPlayground.begin();

  pinMode(3, INPUT);
}

void loop() {
    // Digital Infrared Motion Sensor For Arduino.
    int reading = digitalRead(3);

    // Prints out reading to Serial Monitor
    Serial.println(reading);

    // LED Display turns on if the reading is true and turns off it is false
    if(reading == 1) {
      CircuitPlayground.setPixelColor(0, CircuitPlayground.colorWheel(200));
    }
    else
    {
      CircuitPlayground.clearPixels();
    }
    
    delay(100);
}
