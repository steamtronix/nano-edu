#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

#define BUTTON_PRESSED LOW

SoftwareSerial softSerial(/*rx =*/A1, /*tx =*/A2);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

unsigned long previousMillis = 0;
const long interval = 100;
const int sw1 = 2;
const int sw2 = 3;

bool sw1_state = HIGH; // default state
bool sw2_state = HIGH;

void setup()
{ 

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);

  softSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("STEAMtronix DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  
  if (!myDFPlayer.begin(softSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

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

  display.setCursor(10, 35);
  display.println(F("DFPlayer Mini Demo"));

  display.display();
  delay(1000);

  
  myDFPlayer.volume(20);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
}

void loop()
{
  unsigned long timer = millis();


  if (timer - previousMillis >= interval) {
    previousMillis = timer;

    int sliderValue = analogRead(A0);
    sw1_state = digitalRead(sw1);
    sw2_state = digitalRead(sw2);

    int sliderVolume = map(sliderValue, 0, 1023, 0, 30);
    myDFPlayer.volume(sliderVolume); 
    Serial.print(F("Slider volume: "));
    Serial.print(sliderVolume);
    Serial.print(F(" Buttons: "));
    Serial.print(sw1_state);
    Serial.print(F(", "));
    Serial.println(sw2_state);
  }

  if(sw1_state == BUTTON_PRESSED) {
    myDFPlayer.next();
    sw1_state = HIGH; // reset
    Serial.println(F("Next!"));
  }
  if(sw2_state == BUTTON_PRESSED) {
    myDFPlayer.previous();
    sw2_state = HIGH; // reset
    Serial.println(F("Previous!"));
  }



  
  /*
  
  if (millis() - timer > 30000) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3 every 3 second.
  }
  
  */

  if (myDFPlayer.available()) {
   // printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
