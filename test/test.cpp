#include <ESP32Servo.h>
Servo servo;
void setup()
{
    Serial.begin(115200);
servo.attach(23);
    

}
void loop()
{
    Serial.println("moving to 180");
   servo.write(180);
   delay(3000);
    Serial.println("moving to 0");
    servo.write(0);
   delay(3000);
}


