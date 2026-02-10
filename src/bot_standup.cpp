#include "quadruped.h"
#include <BluetoothSerial.h>
BluetoothSerial BTSerial;
Leg back_left(8, 10.25, 14, 13, back, left);
Leg back_right(8, 10.25, 19, 18, back, right);
Leg front_left(8, 10.25, 27, 26, front, left);
Leg front_right(8, 10.25, 23, 21, front, right);

Quadruped quadruped(front_right, front_left, back_right, back_left);
void setup()
{

    Serial.begin(115200);
    BTSerial.begin("Quadruped");
    quadruped.init(13, 0, 7);
    back_left.set_offset(-5.00, -5.00);
    back_right.set_offset(11.00, -5.00);
    front_right.set_offset(-13.00, 5.00);
    front_left.set_offset(5.00, -12.00);
    quadruped.moveTo_base_pos();
    delay(3000);
    for (int i = 0; i < 3; i++)
    {
        quadruped.move_vert();
        delay(1000);
    }
}
void loop()
{
    char c;
    while (1)
    {
        if (BTSerial.available())
        {
            c = BTSerial.read();
            if (c == 'a')
            { // back left
                quadruped.move_forward();
                // back_left.calibrate("back left");
            }
            else if (c == 'b')
            { // back right
                quadruped.move_backward();
                // back_right.calibrate("back right");
            }
            else if (c == 'c')
            { // front left
                // front_left.calibrate("front left");
                quadruped.moveTo_base_pos();
            }
            else if (c == 'd')
            { // front right
                // front_right.calibrate("front right");
                quadruped.sit_down();
            }
            else if (c == 'e')
            { // front right
                // front_right.calibrate("front right");
                quadruped.stand_up();
            }
            else if (c == 'n')
            {
                break;
            }
        }
        delay(500);
    }
    quadruped.moveTo_base_pos();
}