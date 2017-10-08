/**
 * XBee Transmitter Button
 * Author: Shawn Hymel
 * Date: October 8, 2017
 * 
 * Transmits string "GO" over XBee with button push.
 * 
 * This code is beerware; if you see me (or any other SparkFun 
 * employee) at the local, and you've found our code helpful, 
 * please buy us a round! 
 * Distributed as-is; no warranty is given.
 */

#include <avr/sleep.h>
#include <avr/power.h>
#include <SoftwareSerial.h>
#include "Qduino.h"
#include "Wire.h"

// Constants
const int bootloader_wait = 6000;  // ms
const int flash_wait = 2000;       // ms
const int debounce = 10;           // ms

// Pins
const int btn_pin = 2;

// Globals
qduino q;
int g = 1;
bool flag = false;

// Software serial object for XBee comms
SoftwareSerial XBee(A0, A1);  // Rx, Tx

void setup() {

  // Init qduino library
  q.setup();
  q.ledOff();

  // Wait to allow for reprogramming
  unsigned long timestamp = millis();
  while ( millis() < timestamp + bootloader_wait ) {
    q.setRGB(200, 0, 0);
    delay(250);
    q.ledOff();
    delay(250);
  }

  // Pour a bowl of Serial
  XBee.begin(9600);

  // Set up button pin as external interrupt
  pinMode(btn_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btn_pin), go, FALLING);
}

void loop() {

  // Go to sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();

  // On button push, program continues here
  sleep_disable();

  // Check for button bounce and send "GO" signal
  if ( flag ) {
    delay(debounce);
    if ( digitalRead(btn_pin) == LOW ) {
      XBee.print("GO");
      q.setRGB(0, 200, 0);
      delay(2000);
      q.ledOff();
    }
    flag = false;
  }
}

void go() {
  flag = true;
}
