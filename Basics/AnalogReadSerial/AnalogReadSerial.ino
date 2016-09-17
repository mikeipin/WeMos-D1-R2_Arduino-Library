/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */

#include "remap.h"

const int Sensor_PIN = 0; // Only 1 alanog output can be used on the board, pin 0

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
   pinMode(Sensor_PIN, INPUT); 
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(Sensor_PIN);
  
  // Map to 1023, the wifi board sets 5V to 1024, which is wrong for most uses
  sensorValue = map(sensorValue, 0, 1024, 0, 1023);
  
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
