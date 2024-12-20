/*
 * Sketch: Motor Driver + Servo Test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: Servo.h
 * Circuit: Dual L9110 motor driver module and a Servo Motor connected to Buzzer Module
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */


#include <Servo.h>

#define SERVO_DELAY 10
// Motor A pins
#define MOTOR_A_IN1 9
#define MOTOR_A_IN2 7

// Motor B pins
#define MOTOR_B_IN1 10
#define MOTOR_B_IN2 8

Servo myservo; 

int pos = 0;    // variable to store the servo position


void setup() {
  // Set motor pins as outputs
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object


  // Initially stop both motors
  stopMotors();
}

void loop() {
  // Move Motor A forward
  moveMotorForward(MOTOR_A_IN1, MOTOR_A_IN2);

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(SERVO_DELAY);                       // waits 15 ms for the servo to reach the position
  }
  delay(2000);

  // Move Motor A backward
  moveMotorBackward(MOTOR_A_IN1, MOTOR_A_IN2);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(SERVO_DELAY);                       // waits 15 ms for the servo to reach the position
  }
  delay(2000);

  // Move Motor B forward
  moveMotorForward(MOTOR_B_IN1, MOTOR_B_IN2);
  delay(2000);

  // Move Motor B backward
  moveMotorBackward(MOTOR_B_IN1, MOTOR_B_IN2);
  delay(2000);
}

void moveMotorForward(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void moveMotorBackward(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void stopMotors() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);
}
