/*
 * Sketch: Digital Temperature & Humidity Sensor Test
 * Author: Orkhan Amiraslan (@azerimaker) & Cavid Shamiyev (@CavidShamiyev)
 * Date: April 10, 2024
 * Description: DHT Temperature & Humidity Sensor
 * Libraries: 
 *  - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
 * Circuit: DHT11 / DHT22 sensor connected to pin D11 with 4.7K pull-up resistor
 * Credits: Adafruit
 * Feel free to use and modify for educational purposes.
*/

#include <DHT.h>


#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

const int dhtPin = 11;  // Digital pin connected to the DHT sensor 

DHT dht(dhtPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("SteamtroniX DHTxx test!"));

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

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
  Serial.println(h);
  Serial.print(F("%"));
}

