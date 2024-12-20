/*
 * Sketch: LDR Sensor Test
 * Author: Orkhan Amiraslan (@azerimaker)
 * Date: March 25, 2024
 * Description: 
 * Libraries: No
 * Circuit: LDR Sensor Module on A1
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

const int ldrPin = A3;


void setup() {
  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  int ldrValue = analogRead(ldrPin); // Read analog value from LDR
  Serial.println(ldrValue); // Print LDR value to serial monitor
  delay(50); // Delay for stability
}
