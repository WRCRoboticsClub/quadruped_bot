#include "quadruped.h"

Leg back_left(8, 10.25, 14, 13, left,back);
Leg back_right(8, 10.25, 19, 18, right,back);
Leg front_left(8, 10.25, 27, 26, left,front);
Leg front_right(8, 10.25, 23, 21, right,front);

Quadruped quadruped(front_right, front_left, back_right, back_left);
int loop_once = 1;
void setup()
{

    Serial.begin(115200);
    quadruped.init(15,-3, 7);
    back_left.set_offset(-10.00, 10.00);
    back_right.set_offset(3.00, -12.00);
    front_right.set_offset(6.00,-10.00);
    front_left.set_offset(-6.00,2.00);
    quadruped.moveTo_base_pos();
    delay(1000);
}
void loop()
{ // note down the offsets and pass them to leg.calibrate(); after leg.init();
   char c;
     if (Serial.available())
    {
         c = Serial.read();
        if (c == 'a'){
       back_left.move_vertical();
        }
    }
    c='o';
    // while (loop_once == 1)
    // {
    //     // back_right.calibrate("back_right");
    //     // delay(500);
    //     // back_left.calibrate("back_left");
    //     // delay(500);
    //     front_right.calibrate("front_right");
    //     delay(500);
    //     front_left.calibrate("front_left");
    //     delay(500);
    //     // quadruped.move_vert();
    //     // delay(2000);
    //     // front_left.move_vertical();
    //     // delay(1000);
    //     // front_right.move_vertical();
    //     // delay(1000);
    //     // back_right.move_vertical();
    //     // delay(1000);
    //     // back_left.move_vertical();
    //     // delay(1000);
    //     // quadruped.move_vert();

    //     loop_once++;
    // }
}
