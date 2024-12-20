/*
 * Sketch: Sound Sensor Test
 * Author: Orkhan Amiraslan (@azerimaker)
 * Date: March 25, 2024
 * Description: 
 * Libraries: No
 * Circuit: Sound Sensor Module on A2
 * Credits: Seeedstudio Grove Sound Sensor
 * Feel free to use and modify for educational purposes.
 */

const int micPin = A6;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("SteamtroniX - Sound Sensor Test...");
}

void loop()
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(micPin);
    }

    sum >>= 5; // /32 - to find average

    Serial.println(sum);
    delay(10);
}
