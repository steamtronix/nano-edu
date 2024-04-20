/*
 * Sketch: Relay Test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: No
 * Circuit: Relay connected to D12
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

const int relayPin = 12;

void setup() {
pinMode(relayPin, OUTPUT);
}

void loop() {
digitalWrite(relayPin,HIGH);
delay(2000);
digitalWrite(relayPin,LOW);
delay(2000);
}
