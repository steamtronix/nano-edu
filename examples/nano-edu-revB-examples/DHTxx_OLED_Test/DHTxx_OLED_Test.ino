/*
 * Sketch: Digital Temperature & Humidity Sensor Test
 * Author: Orkhan Amiraslan (@azerimaker) & Cavid Shamiyev (@CavidShamiyev)
 * Date: April 10, 2024
 * Description: DHT Temperature & Humidity Sensor
 * Libraries: 
 *  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
 *  - GFX Library: Adafruit_GFX
 *  - SSD1306 Library: Adafruit_SSD1306
 * Circuit: DHT11 / DHT22 sensor connected to pin D11 with 4.7K pull-up resistor
 * Credits: Adafruit
 * Feel free to use and modify for educational purposes.
*/

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

const int dhtPin = 11;  // Digital pin connected to the DHT sensor 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(dhtPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("SteamtroniX DHTxx OLED test!"));

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();


  
  display.setTextSize(1);     
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(30, 10);
  display.println(F("STEAMTRONIX")); 

  display.setCursor(40, 20);
  display.println(F("NANO-EDU")); 

  display.setCursor(20, 35);
  display.println(F("DHTxx OLED TEST"));

  display.display();
  delay(2000);

  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println(F("%"));

  display.clearDisplay();
  display.setCursor(0, 10);
  display.print(F("Temperature: "));
  display.print(t);
  display.println(F(" C "));
  display.setCursor(0, 20);
  display.print(F("Humidity: "));
  display.print(h);
  display.println(F("%"));

  display.display();

  delay(2000);

}

