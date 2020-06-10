#include <Adafruit_CircuitPlayground.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Circuit Playground test!");

  CircuitPlayground.begin();
}

void loop() {
    // Circuit Playground Sound Sensor
    int soundLevel = CircuitPlayground.soundSensor();
    Serial.print("Sound sensor: ");
    Serial.println(soundLevel);
    delay(10);

    CircuitPlayground.clearPixels();

    if(0 < soundLevel)
        CircuitPlayground.setPixelColor(0, CircuitPlayground.colorWheel(60));
    if(350 < soundLevel)
        CircuitPlayground.setPixelColor(1, CircuitPlayground.colorWheel(53));
    if(375 < soundLevel)
        CircuitPlayground.setPixelColor(2, CircuitPlayground.colorWheel(46));
    if(400 < soundLevel)
        CircuitPlayground.setPixelColor(3, CircuitPlayground.colorWheel(39));
    if(425 < soundLevel)
        CircuitPlayground.setPixelColor(4, CircuitPlayground.colorWheel(32));
    if(450 < soundLevel)
        CircuitPlayground.setPixelColor(5, CircuitPlayground.colorWheel(26));
    if(475 < soundLevel)
        CircuitPlayground.setPixelColor(6, CircuitPlayground.colorWheel(19));
    if(500 < soundLevel)
        CircuitPlayground.setPixelColor(7, CircuitPlayground.colorWheel(13));
    if(525 < soundLevel)
        CircuitPlayground.setPixelColor(8, CircuitPlayground.colorWheel(6));
    if(550 < soundLevel)
        CircuitPlayground.setPixelColor(9, CircuitPlayground.colorWheel(0));
}
