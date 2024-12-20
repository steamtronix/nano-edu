/*
 * Sketch: Servo Test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: No
 * Circuit: Servo motor connected to D16, shared with Buzzer
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */


#include <Servo.h>

const int servoPin = 6;

Servo myservo;  

int pos = 0;    

void setup() {
  myservo.attach(servoPin);  
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
