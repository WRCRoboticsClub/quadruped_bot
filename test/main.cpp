// #include <Arduino.h>
// #include <ESP32Servo.h>
// #include <math.h>

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif

// // Servo pins
// #define HIP_SERVO_PIN 13
// #define KNEE_SERVO_PIN 14

// Servo hipServo;
// Servo kneeServo;

// // Leg structure
// typedef struct
// {
//     double Humerus;
//     double Radius;
//     double hip_angle;
//     int knee_angle;
// } Leg;

// Leg leg;

// // Forward mapping helper (optional)
// int mapAngle(int x, int in_min, int in_max, int out_min, int out_max)
// {
//     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

// // IK calculation for straight leg
// void calc_angles(Leg *leg, double height)
// {
//     // Hip angle calculation
//     leg->hip_angle = mapAngle(
//         90 - floor((180 / M_PI) * acos((pow(leg->Humerus, 2) + pow(height, 2) - pow(leg->Radius, 2)) / (2 * height * leg->Humerus))),
//         0, 180, 180, 0);

//     // Knee angle calculation
//     leg->knee_angle = floor((180 / M_PI) * acos((pow(leg->Radius, 2) - pow(height, 2) + pow(leg->Humerus, 2)) / (2 * leg->Radius * leg->Humerus)));
// }

// void setup()
// {
//     hipServo.attach(HIP_SERVO_PIN);
//     kneeServo.attach(KNEE_SERVO_PIN);

//     // Initialize leg dimensions
//     leg.Humerus = 8.0;
//     leg.Radius = 10.25;

//     // Starting position
//     hipServo.write(180);
//     kneeServo.write(31);

//     delay(100); // small delay to allow servo to reach initial position
// }

// void loop()
// {
//     // Smooth continuous walking motion
//     double pos=15; // height of foot from ground
//     const double stepLength = 5.0; // arbitrary forward distance
//     const int frames = 50; // smooth frames per step

//     // Forward arc
//     for (int i = 0; i <= frames; i++)
//     {
//         double t = (double)i / frames;
//         pos = sin(M_PI * t) * 11.5 + 6.5; // smooth foot arc from 6.5 to ~18

//         calc_angles(&leg, pos);

//         hipServo.write(leg.hip_angle);
//         kneeServo.write(leg.knee_angle);

//         delay(70); // smooth motion speed
//     }

//     // Backward motion (foot returns)
//     for (int i = 0; i <= frames; i++)
//     {
//         double t = (double)i / frames;
//         pos = sin(M_PI * (1 - t)) * 11.5 + 6.5; // return arc

//         calc_angles(&leg, pos);

//         hipServo.write(leg.hip_angle);
//         kneeServo.write(leg.knee_angle);

//         delay(100);
//     }
// }
#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Servo pins
#define HIP1_SERVO_PIN 13
#define KNEE1_SERVO_PIN 14
#define HIP2_SERVO_PIN 27
#define KNEE2_SERVO_PIN 26

Servo hip1Servo;
Servo knee1Servo;
Servo hip2Servo;
Servo knee2Servo;

// Leg structure
typedef struct
{
    double Humerus;
    double Radius;
    double hip_angle;
    int knee_angle;
    int side;
} Leg;

Leg leg1;
Leg leg2;

// Forward mapping helper (optional)
int mapAngle(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// IK calculation for straight leg
void calc_angles(Leg *leg, double height)
{
    if (leg->side == 0)
    {
        leg->hip_angle = mapAngle(90 - floor((180 / M_PI) * acos((pow(leg->Humerus, 2) + pow(height, 2) - pow(leg->Radius, 2)) / (2 * height * leg->Humerus))),0, 180, 180, 0);
        leg->knee_angle = floor((180 / M_PI) * acos((pow(leg->Radius, 2) - pow(height, 2) + pow(leg->Humerus, 2)) / (2 * leg->Radius * leg->Humerus)));
    }
    else if (leg->side == 1)
    {

        leg->hip_angle = 90 - floor((180 / M_PI) * (acos((pow(leg->Humerus, 2) + pow(height, 2) - pow(leg->Radius, 2)) / (2 * height * leg->Humerus))));
        leg->knee_angle = map(floor((180 / M_PI) * (acos((pow(leg->Radius, 2) - pow(height, 2) + pow(leg->Humerus, 2)) / (2 * leg->Radius * leg->Humerus)))), 0, 180, 180, 0);
    }
}

void setup()
{
    // Attach servos
    hip1Servo.attach(HIP1_SERVO_PIN);
    knee1Servo.attach(KNEE1_SERVO_PIN);
    hip2Servo.attach(HIP2_SERVO_PIN);
    knee2Servo.attach(KNEE2_SERVO_PIN);

    // Initialize leg dimensions
    leg1.Humerus = 8.0;
    leg1.Radius = 10.25;
    leg1.side = 0;
    leg2.Humerus = 8.0;
    leg2.Radius = 10.25;
    leg2.side = 1;

    // Starting position
    hip1Servo.write(158);
    knee1Servo.write(65);
    hip2Servo.write(11);
    knee2Servo.write(115);

    delay(100); // small delay to allow servo to reach initial position
    Serial.begin(9600);
}

void loop()
{
    const int frames = 40; // smooth frames per step
    double pos;            // foot height

    // Forward arc
    for (int i = 0; i <= frames; i++)
    {
        double t = (double)i / frames;
        pos = sin(M_PI * t) * 11.5 + 6.5; // smooth foot arc
        Serial.println(pos);

        // Calculate angles for both legs
        calc_angles(&leg1, pos);
        calc_angles(&leg2, pos);

        // Write to servos
        hip1Servo.write(leg1.hip_angle);
        knee1Servo.write(leg1.knee_angle);
        hip2Servo.write(leg2.hip_angle);
        knee2Servo.write(leg2.knee_angle);

        delay(100); // smooth motion
    }

    // Backward arc
    // for (int i = 0; i <= frames; i++)
    // {
    //     double t = (double)i / frames;
    //     pos = sin(M_PI * (1 - t)) * 11.5 + 10; // return arc
    //     Serial.println(pos);
    //     calc_angles(&leg1, pos);
    //     calc_angles(&leg2, pos);

    //     hip1Servo.write(leg1.hip_angle);
    //     knee1Servo.write(leg1.knee_angle);
    //     hip2Servo.write(leg2.hip_angle);
    //     knee2Servo.write(leg2.knee_angle);

    //     delay(100);
    // }
}
