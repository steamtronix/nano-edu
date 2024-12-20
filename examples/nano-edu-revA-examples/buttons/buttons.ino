/*
 * Sketch: LDR Sensor Test
 * Author: Orkhan Amiraslan (@azerimaker)
 * Date: April 10, 2024
 * Description: 
 * Libraries: No
 * Circuit: push buttons with pull-up circuits on D2, D3
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

#define BUTTON_PRESSED 0
#define BUTTON_NOT_PRESSED 1

const int greenButton = 2;
const int redButton = 3;
bool greenButtonState = true; // default state
bool redButtonState = true;   // default state


void setup() {
  Serial.begin(115200);
  pinMode(greenButton, INPUT);
  pinMode(redButton, INPUT);
}

void loop() {
  greenButtonState = digitalRead(greenButton);
  redButtonState = digitalRead(redButton);

  if(greenButtonState == BUTTON_PRESSED && redButtonState == BUTTON_NOT_PRESSED)
  {
    Serial.println("Button_1 pressed");
  }else if(greenButtonState == BUTTON_NOT_PRESSED && redButtonState == BUTTON_PRESSED)
  {
    Serial.println("Button_2 pressed");
  }else if(greenButtonState == BUTTON_PRESSED && redButtonState == BUTTON_PRESSED)
  {
    Serial.println("Both buttons pressed");
  }else
  {
    Serial.println("No Button");
  }

  delay(20);
}
