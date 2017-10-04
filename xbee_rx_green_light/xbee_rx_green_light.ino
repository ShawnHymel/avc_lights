/**
 *  XBee Receiver Green Light
 *  Author: Shawn Hymel
 *  Date: October 4, 2017
 *  
 *  Receives string "GO" on XBee and flashes green light.
 *  
 * This code is beerware; if you see me (or any other SparkFun 
 * employee) at the local, and you've found our code helpful, 
 * please buy us a round! 
 * Distributed as-is; no warranty is given.
 */

#include <SoftwareSerial.h>
#include "FastLED.h"

// Number of LEDs
#define NUM_LEDS    20
#define WAIT        2000    // ms
#define BRIGHTNESS  100     // %

// Define our clock and data lines
#define DATA_PIN    11
#define CLOCK_PIN   13

// Create the LED array
CRGB leds[NUM_LEDS];

// Software serial object for XBee comms
SoftwareSerial XBee(2, 3);  // Rx, Tx

void setup() {

  // Pour a bowl of Serial
  XBee.begin(9600);

  // Init LEDs
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  
  //Set global brightness
  FastLED.setBrightness(BRIGHTNESS);

  // Make sure LEDs start off
  turnOff();
}

void loop() { 

  // Wait for the 'O' character to appear
  String str = XBee.readStringUntil('O');

  // If we get the GO signal, flash light
  if ( str == "G" ) {
    flashGreen();
  }
}

void turnOff() {
  for ( int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void flashGreen() {

  // Show green
  for ( int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB::White;
  }
  FastLED.show();
  delay(WAIT);

  // Turn off LEDs
  turnOff();
}

