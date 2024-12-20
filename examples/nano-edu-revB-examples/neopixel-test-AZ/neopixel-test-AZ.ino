/*
 * Sketch: NeoPixel Test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: Adafruit_NeoPixel.h
 * Circuit: 10x WS2812B LEDs connected in series to pin D13
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS    10
const int neopixelPin = 13;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, neopixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  // Azerbaijan Flag colors
  strip.setPixelColor(0, 0, 0, 100); 
  strip.setPixelColor(1, 0, 0, 100); 
  strip.setPixelColor(2, 0, 0, 100); 
  strip.setPixelColor(3, 100, 0, 0); 
  strip.setPixelColor(4, 100, 0, 0); 
  strip.setPixelColor(5, 100, 0, 0); 
  strip.setPixelColor(6, 100, 0, 0); 
  strip.setPixelColor(7, 0, 100, 0); 
  strip.setPixelColor(8, 0, 100, 0); 
  strip.setPixelColor(9, 0, 100, 0); 
 
  strip.show();
  delay(5000); // Adjust delay as needed

  // Set the whole strip to blue
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0); // off
  }
  strip.show();
  delay(1000); // Adjust delay as needed
}
