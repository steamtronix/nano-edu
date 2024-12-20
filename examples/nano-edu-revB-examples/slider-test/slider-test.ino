#define slider_pot A0
int value;
void setup() {
Serial.begin(9600);
}

void loop() {
value = analogRead(slider_pot);
Serial.println(value);
delay(300);
}
