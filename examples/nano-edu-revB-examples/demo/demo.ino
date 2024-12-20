/*
 * Sketch: SteamtroniX Nano revB Demo Code
 * Author: @azerimaker
 * Date: October 7, 2024
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
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>



#define DHTTYPE DHT11 //DHT11
// NeoPixel
#define NUM_LEDS    10
#define LED_BRIGHTNESS 30
// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 


// Constants
const int sliderPin = A0;
const int ldrPin = A3; 
const int soundPin = A6;

const int greenButtonPin = 2;
const int redButtonPin = 3;

const int buzzerPin = 6; // PWM
const int motorA1_PWM_Pin = 9; // PWM
const int motorA2_Pin = 7; 
const int motorB1_PWM_Pin = 10; // PWM 
const int motorB2_Pin = 8;

const int dhtPin = 11;  // Digital pin connected to the DHT sensor 
const int relayPin = 12;
const int neopixelPin = 13;
const long interval = 2000;  // interval to read DHTxx sensor


// Variables
int relayState = LOW;
bool motor_A_Running = false;
bool motor_B_Running = false;
unsigned long previousMillis = 0; 
float temperature = 0;
float humidity = 0;

DHT dht(dhtPin, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, neopixelPin, NEO_GRB + NEO_KHZ800);


void setup(){
  Serial.begin(115200);

  delay(250); // wait for the OLED to power up
  Serial.println("SteamtroniX Nano-Edu RevB Demo");

  pinMode(relayPin, OUTPUT);
  pinMode(motorA2_Pin, OUTPUT);
  pinMode(motorB2_Pin, OUTPUT);

  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP);

  digitalWrite(relayPin, LOW); // disable relay
  digitalWrite(motorA2_Pin, LOW); // stop motorA
//  digitalWrite(motorB2_Pin, LOW); // stop motorB


  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();

  delay(3000);

  display.clearDisplay();
  
  display.setTextSize(1);     
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(30, 10);
  display.println(F("STEAMTRONIX")); 

  display.setCursor(25, 20);
  display.println(F("NANO-EDU DEMO")); 

  display.display();

  dht.begin();

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

  delay(2000);

}


void loop() {
  
  int sliderValue = analogRead(sliderPin);// Read potentiometer value
  int ldrValue = analogRead(ldrPin);      // Read analog value from LDR
  int soundValue = analogRead(soundPin);  // Read analog value from microphone

  int numLedsLit = sliderValue/100;

   for (int i = NUM_LEDS; i > 0; i--) {
    if (i <= numLedsLit) {
      strip.setPixelColor(NUM_LEDS - i, 55, 0, 0); // Red, with reversed index
    } else {
      strip.setPixelColor(NUM_LEDS - i, 0, 0, 0); // Turn off LED
    }
  }
  strip.show();


  int motorSpeed = map(sliderValue, 0, 1023, 0, 255);

  if ((digitalRead(greenButtonPin) == LOW) && (digitalRead(redButtonPin) == HIGH)) {
      motor_A_Running = true;
      motor_B_Running = false;
      relayState = true;
      startChime();
  } else if ((digitalRead(greenButtonPin) == HIGH) && (digitalRead(redButtonPin) == LOW)) {
      motor_A_Running = false;
      motor_B_Running = true;
      relayState = false;
      stopChime(); 
  } else if ((digitalRead(greenButtonPin) == LOW) && (digitalRead(redButtonPin) == LOW)){
      motor_A_Running = false;
      motor_B_Running = false;
      relayState = false;
      fullStopChime(); 
  }

  if (motor_A_Running) {
      analogWrite(motorA1_PWM_Pin, motorSpeed);
      digitalWrite(motorA2_Pin, LOW);  
      analogWrite(motorB1_PWM_Pin, 0);
      digitalWrite(motorB2_Pin, LOW);
  } else if(motor_B_Running) {
      analogWrite(motorA1_PWM_Pin, 0);
      digitalWrite(motorA2_Pin, LOW);
      analogWrite(motorB1_PWM_Pin, motorSpeed);
      digitalWrite(motorB2_Pin, LOW);  
  } else{
      analogWrite(motorA1_PWM_Pin, 0);
      digitalWrite(motorA2_Pin, LOW);
      analogWrite(motorB1_PWM_Pin, 0);
      digitalWrite(motorB2_Pin, LOW);  
  }

  digitalWrite(relayPin, relayState);


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("Light: ")); display.println(ldrValue); // Print LDR value to OLED display
  display.print(F("Sound: ")); display.println(soundValue); 
  display.print(F("Slider: ")); display.println(sliderValue); 
  display.print(F("Temperature: ")); display.print(temperature); display.println(F(" C")); 
  display.print(F("Humidity: ")); display.print(humidity); display.println(F(" %")); 

  display.display();

}


void startChime() {
  tone(buzzerPin, 1000, 100); 
  delay(200);
}

void stopChime() {
  tone(buzzerPin, 500, 100); 
  delay(200);
}

void fullStopChime() {
  tone(buzzerPin, 200, 100); 
  delay(200);
}

