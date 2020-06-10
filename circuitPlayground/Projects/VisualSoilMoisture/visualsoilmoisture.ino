// Adafruit Circuit Playground Moisture Sensor Demo
// 2017-10-14 Derek Jacobs!

// The DFRobot soil moisture sensor outputs an analog signal. This program will illuminate a number of neopixels based on that signal.
// If you're using the DKC3 provided kit:
// Connect the red clip to the 3.3v pad
// Connect the black clip to a ground (GND) pad
// Connect the green clip to an analog pad. We assume #10 by default, so change it below if you use another one.

// the sensor's stock description of ranges is as follows:
// 0  ~300     dry soil
// 300~700     humid soil
// 700~950     in water

// We will attempt to self-calibrate to the sensor. After startup, dip the sensor in a cup of water to determine the "maximum" moisture. 
// Different water sources will give different 'maximum' results - tap water is generally more conductive than pure distilled water, for example.

#include <Adafruit_CircuitPlayground.h>

/* ******************* */

// Where is the sensor analog output connected?
const int padNumber = 10;

// use one color for all active pixels, or rainbow them using individual color for each?
const bool rainbow = false;

// we have two options to shut off the excess neopixels (when moisture level drops)
// 1. use CircuitPlayground.clearPixels(); then turn back on the ones we want. 
//        In testing, this seems to cause a faint flicker in the neopixels.
// 2. iterate through all the neopixels each time, and shut off the ones above the level.
//        No flicker, but additional setPixelColor calls to shut them off.
const int option = 2;

// toggle red LED #13 after this many main loops.
const int frequency = 10; 

// color settings, in separated RGB 0-255 format.
// could have done this in a 1-dimensional array using 0xABCDEF format, 
// or using the CircuitPlayground.colorWheel() function.
const int colorsetting[10][3] = {
 {255,0,0},   // light 1 will be red
 {255,127,0}, // 2
 {255,255,0}, // 3 yellow
 {127,255,0}, // 4 
 {0,255,0},   // 5 green
 {0,255,127}, // 6
 {0,255,255}, // 7 bluegreen
 {0,127,255}, // 8
 {0,0,255},   // 9 blue
 {0,0,255}    // 10 also blue
};

/* ****************** */

// Guess a sane default floor and ceiling value. The program will adjust these as it runs.
int minvalue = 0;
int maxvalue = 500;

// enumeration for cleaner access into colorsetting matrix.
enum color { 
  red = 0,
  green, 
  blue};

/* ******************* */

// calculate a moisture level from 0-10 based on the analog sensor value
int moistureLevel(int sensorvalue)
{
  int value = 0;
  // map() is an option to convert a raw analog reading into a value from 0-10 but the reading seems to only ever reach 10 when sensorvalue == maxvalue.
  // value = map(sensorvalue, minvalue, maxvalue, 0, 10); 

  // Doing our own calculation allows for arguably better rounding.
  value = round((sensorvalue - minvalue) * 10.0 / (maxvalue - minvalue));
  
  return value;
}

// Turn on a number of the neopixels
void setPixels(int pixels)
{  
  int pixelnum = 0;
  
  // option #1: shut everything off in advance
  if (1 == option) CircuitPlayground.clearPixels(); 

  for (pixelnum; pixelnum < pixels; pixelnum++)
  {
    int color = (rainbow ? pixelnum : pixels-1);
    CircuitPlayground.setPixelColor(
      pixelnum, 
      colorsetting[color][red], 
      colorsetting[color][green], 
      colorsetting[color][blue]); 
  }
  
  // option #2: loop through the remaining pixels and shut them off
  if (2 == option)
    for (pixelnum; pixelnum < 10; pixelnum++)
    {
      CircuitPlayground.setPixelColor(pixelnum, 0);
    }
}

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
  CircuitPlayground.begin();
  Serial.begin(115200);

  // Beep once to indicate we're loaded.
  CircuitPlayground.playTone(2000, 200, false);
}

void loop() {
  // proof of life
  heartbeat();
  
  // Get sensor value
  int reading = analogRead(padNumber);
  Serial.println(reading); // view this in realtime with Arduino IDE using Tools -> Serial Monitor, or graph it with Tools -> Serial Plotter.

  // recalibrate
  if (reading < minvalue) minvalue = reading;
  if (reading > maxvalue) maxvalue = reading;

  // Convert analog reading to a 0-10 value
  int level = moistureLevel(reading);
  //Serial.println(level); // debug print the level
  
  // set the pixels based on the moisture level
  setPixels(level);
    
  delay(100); // milliseconds 
}
