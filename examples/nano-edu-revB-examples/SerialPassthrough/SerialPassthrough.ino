#include <SoftwareSerial.h>

SoftwareSerial espSerial(5, 4); // RX, TX



void setup() {
  // Initialize both serial ports:
  Serial.begin(115200); // Communication with the computer
  espSerial.begin(115200); // Communication with the ESP-01
}

void loop() {
  // Read from computer and send to ESP-01
  if (Serial.available()) {
    while (Serial.available()) {
      espSerial.write(Serial.read());
    }
  }

  // Read from ESP-01 and send to computer
  if (espSerial.available()) {
    while (espSerial.available()) {
      Serial.write(espSerial.read());
    }
  }
}
