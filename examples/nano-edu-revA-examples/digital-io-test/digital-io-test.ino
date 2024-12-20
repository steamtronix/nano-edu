void setup() {
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT); // bütün pinləri çıxış kimi təyin edirik
  }
}

void loop() {
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, HIGH); // Turn on the pin
    delay(250); // Delay for 500 milliseconds
    digitalWrite(i, LOW); // Turn off the pin
    delay(250); // Delay for 500 milliseconds
  }
}
