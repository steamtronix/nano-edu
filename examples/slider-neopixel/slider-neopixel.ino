/*
 * Sketch: Slider with NeoPixel test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: Adafruit_NeoPixel.h
 * Circuit: Neopixel connected to D13, Slider to A0
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS    10

const int neopixelPin = 13;
const int sliderPin = A0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, neopixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200); // Initialize serial communication
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  int sensorValue = analogRead(sliderPin); // Read potentiometer value
  Serial.print("Analog Read: ");
  Serial.println(sensorValue); // Print analog read value

  
  //int numLedsLit = map(sensorValue, 0, 1023, 0, NUM_LEDS-1); // Map potentiometer value to number of LEDs to light
  int numLedsLit = sensorValue/100;
  Serial.print("Num LEDs Lit: ");
  Serial.println(numLedsLit); // Print numLedsLit value

  // Turn on LEDs based on potentiometer value, starting from LED 10 and going down to LED 1
  for (int i = NUM_LEDS; i > 0; i--) {
    if (i <= numLedsLit) {
      strip.setPixelColor(NUM_LEDS - i, 55, 0, 0); // Red, with reversed index
    } else {
      strip.setPixelColor(NUM_LEDS - i, 0, 0, 0); // Turn off LED
    }
  }
  strip.show();
}
