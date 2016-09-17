/*
 ESP8266 Blink by Michael Ipinyomi
 
 Turns on an LED on for one second, then off for one second, repeatedly.
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1/ D9 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
#include "remap.h"

const int LED_PIN = D9;
// D9 is equivalent to the internal LED pin
// Pins 5,6,7,14 and 15 are not known for now

void setup() {
  pinMode(LED_PIN, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_PIN, HIGH);      // Turn the LED on 
  delay(1000);                      // Wait for a second
  digitalWrite(LED_PIN, LOW);       // Turn the LED off
  delay(1000);  
}
