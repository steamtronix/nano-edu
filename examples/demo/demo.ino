/*
 * Sketch: SteamtroniX Demo Code
 * Author: @azerimaker
 * Date: April 11, 2024
 * Description: 
 * Libraries: 
    - Adafruit_GFX.h
    - Adafruit_SH110X.h
 * Circuit:
 * Credits: Adafruit
 * Feel free to use and modify for educational purposes.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Adafruit_NeoPixel.h>
#include "DHT_Async.h"


#define I2C_ADDRESS 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define I2C_ADDRESS 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 
#define NUM_LEDS    10
#define LED_BRIGHTNESS 30

//#define SH110X_NO_SPLASH FALSE

// Constants
const int sliderPin = A0;
const int ldrPin = A1; 
const int soundPin = A2;
const int gasPin = A3;

const int greenButtonPin = 2;
const int redButtonPin = 3;

const int buzzerPin = 6; // PWM
const int motorA1Pin = 9; // PWM
const int motorA2Pin = 7; 
const int motorB1Pin = 10; // PWM 
const int motorB2Pin = 8;

const int dhtPin = 11;  // Digital pin connected to the DHT sensor 
const int relayPin = 12;
const int neopixelPin = 13;
const long interval = 4000;  // interval at which to blink (milliseconds)




// Variables
unsigned long previousMillis = 0; 
int relayState = LOW;
bool motorRunning = false;
float humidity = 50;
float temperature = 22;

DHT_Async dht_sensor(dhtPin, DHT_SENSOR_TYPE);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, neopixelPin, NEO_GRB + NEO_KHZ800);


void setup(){
  Serial.begin(9600);

  delay(250); // wait for the OLED to power up
  Serial.println("SteamtroniX Demo");

  pinMode(relayPin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(motorB2Pin, OUTPUT);

  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP);

  digitalWrite(relayPin, LOW); // disable relay
  digitalWrite(motorA2Pin, LOW); // stop motorA
//  digitalWrite(motorB2Pin, LOW); // stop motorB


  display.begin(I2C_ADDRESS, true);  
  display.display();

  delay(2000);

  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  
  display.setCursor(30, 10);
  display.println("DON'T");

  display.setCursor(25, 30);
  display.print("PANIC!");

  display.display();
  delay(3000);

  // invert the display
  //display.invertDisplay(true);
  //delay(1000);
  //display.invertDisplay(false);

  display.clearDisplay();
  display.setTextSize(1);

  strip.begin();
  strip.setPixelColor(0, 0, 0, LED_BRIGHTNESS); 
  strip.setPixelColor(1, 0, 0, LED_BRIGHTNESS); 
  strip.setPixelColor(2, 0, 0, LED_BRIGHTNESS); 
  strip.setPixelColor(3, LED_BRIGHTNESS, 0, 0); 
  strip.setPixelColor(4, LED_BRIGHTNESS, 0, 0); 
  strip.setPixelColor(5, LED_BRIGHTNESS, 0, 0); 
  strip.setPixelColor(6, LED_BRIGHTNESS, 0, 0); 
  strip.setPixelColor(7, 0, LED_BRIGHTNESS, 0); 
  strip.setPixelColor(8, 0, LED_BRIGHTNESS, 0); 
  strip.setPixelColor(9, 0, LED_BRIGHTNESS, 0); 
  strip.show();

}


void loop() {
  int sliderValue = analogRead(sliderPin);// Read potentiometer value
  int ldrValue = analogRead(ldrPin);      // Read analog value from LDR
  int soundValue = analogRead(soundPin);  // Read analog value from microphone
  int gasValue = analogRead(gasPin);      // Read analog value from MQ7

  int motorSpeed = map(sliderValue, 0, 1023, 0, 255);

  if (digitalRead(greenButtonPin) == LOW) {
      motorRunning = true;
      relayState = true;
      startChime();
  }
  if (digitalRead(redButtonPin) == LOW) {
      motorRunning = false;
      relayState = false;
      stopChime(); 
  }

  if (motorRunning) {
      analogWrite(motorA1Pin, motorSpeed);
      digitalWrite(motorA2Pin, LOW);  
  } else {
      analogWrite(motorA1Pin, 0);
      digitalWrite(motorA2Pin, LOW);
  }

  digitalWrite(relayPin, relayState);



  static unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    /*
    if (dht_sensor.measure(temperature, humidity)) {
      Serial.print("T = "); Serial.print(temperature, 1);
      Serial.print(" deg. C, H = "); Serial.print(humidity, 1);  Serial.println("%");
      return (true);
    }else{
      return (false);
    }
    */
  }

  display.setCursor(0, 0);
  display.print(F("Light: ")); display.println(ldrValue); // Print LDR value to OLED display
  display.print(F("Sound: ")); display.println(soundValue); 
  display.print(F("Gas: ")); display.println(gasValue); 
  display.print(F("Slider: ")); display.println(sliderValue); 
  display.print(F("Temperature: ")); display.print(temperature); display.println(F(" C")); 
  display.print(F("R. Humidity: ")); display.print(humidity); display.println(F(" %")); 


  display.display();
  display.clearDisplay();

}


void startChime() {
  tone(buzzerPin, 1000, 200); 
  delay(250);
}

void stopChime() {
  tone(buzzerPin, 200, 200); 
  delay(250);
}

