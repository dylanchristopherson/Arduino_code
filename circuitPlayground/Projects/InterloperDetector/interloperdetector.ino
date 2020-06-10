// Adafruit Circuit Playground 
// Digital IR Motion Sensor Demo - a.k.a. Interloper Detector
// 2017-10-15 Derek Jacobs! 

// The DFRobot digital IR motion sensor outputs a digital signal when movement is detected.
// If you're using the DKC3 provided kit:
// Connect the red clip to the 3.3v pad
// Connect the black clip to a ground (GND) pad
// Connect the green clip to a digital pad. We assume #3 by default, so change it below if you use another one.

// Power it up and wait 1-2 seconds for the sensor to get a snapshot of the still room. 
// It works by averaging the IR image over time and looking for abrupt changes.

#include <Adafruit_CircuitPlayground.h>

/* ******************* */

// Where is the sensor output connected?
const int padNumber = 3;

// How much blinding interloper brightness do we want to start with? range is one byte (0-255). 
// 255 is not quite like staring into the sun, but close. We'll ramp up to 255 the longer the alarm sounds.
const int brightnessDefault = 10; 
int brightnessCurrent = brightnessDefault;

// toggle red LED #13 after this many main loops.
const int frequency = 10; 

/* ****************** */

bool pitchHigh = false;
bool lightsHigh = false; 

// blink the red #13 LED to indicate we're alive
void heartbeat()
{
  static int counter = 0;
  static int lighton = false;

  if (++counter >= frequency)
  {
    counter = 0;
    lighton = !lighton;
    CircuitPlayground.redLED(lighton);
  }
}

/* ******************* */

void setup() {
  // Initialize Circuit Playground and turn on serial output for monitor/debugging
  CircuitPlayground.begin(brightnessCurrent); // make the pixels super bright for maximum interloper blinding potential
  Serial.begin(115200);

  // Beep once to indicate we're loaded.
  CircuitPlayground.playTone(2000, 200, false);
}

void loop() {
  // proof of life to place fear into the heart of interlopers
  heartbeat();
  
  // Read the sensor and check for interlopers
  bool motion = (digitalRead(padNumber) == HIGH);
  Serial.println(motion); // view this in realtime with Arduino IDE using Tools -> Serial Monitor, or graph it with Tools -> Serial Plotter.

  CircuitPlayground.clearPixels();
  if (motion) // INTERLOPER DETECTED!!1!
  {
    pitchHigh = !pitchHigh;
    lightsHigh = !lightsHigh;

    // gradually blind the interloper
    brightnessCurrent += 5;
    if (brightnessCurrent > 255) brightnessCurrent = 255;
    CircuitPlayground.setBrightness(brightnessCurrent);

    // scare the interloper with blinking lights
    for (int p = 0; p<10; p++)
    {
      bool red = (lightsHigh && p % 2 == 0) || (!lightsHigh && p % 2 != 0);
      if (red) CircuitPlayground.setPixelColor(p, CircuitPlayground.colorWheel(0)); // RED
      else CircuitPlayground.setPixelColor(p, 0xFFFFFF); // WHITE
    }

    // scare the interloper by sounding the alarm
    int pitch = 2000 + (2000 * pitchHigh); // kind of hacky to multiply something by a 'false' boolean to zero it... welcome to technical debt
    CircuitPlayground.playTone(pitch, 90, false);

    // tazering the interloper is not implemented and left as an exercise for the user
  }
  else // interloper ran away probably
  {
    brightnessCurrent = brightnessDefault;
  }
    
  delay(100); // milliseconds to wait for the interloper to run away
}
