/*
 * Sketch: Gas Sensor Test
 * Author: @azerimaker
 * Date: March 25, 2024
 * Description: 
 * Libraries: No
 * Circuit: MQ7 Gas Sensor Module on pin A3
 * Credits: 
 * Feel free to use and modify for educational purposes.
 */

const int gasSensorPin = A3;

void setup()
{
    Serial.begin(115200);
    Serial.println("SteamtroniX - Gas Sensor Test...");
}

void loop()
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(gasSensorPin);
    }

    sum >>= 5; // /32 - to find average

    Serial.println(sum);
    delay(20);
}
