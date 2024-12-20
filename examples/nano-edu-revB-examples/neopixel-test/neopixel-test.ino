/*
 * Sketch: NeoPixel Test RGB
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
  // Turn on LEDs in reverse order with different colors
  for(int i = NUM_LEDS - 1; i >= 0; i--) {
    if (i % 3 == 0) {
      strip.setPixelColor(i, 55, 0, 0); // Red
    } else if (i % 3 == 1) {
      strip.setPixelColor(i, 0, 55, 0); // Green
    } else {
      strip.setPixelColor(i, 0, 0, 55); // Blue
    }
    strip.show();
    delay(100); // Adjust delay as needed
  }

  // Turn off all LEDs
  strip.clear();
  strip.show();
  delay(1000); // Delay before starting again
}
