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


float height = 18;
float pos = 6.5;

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
        leg->knee_angle = mapAngle(floor((180 / M_PI) * (acos((pow(leg->Radius, 2) - pow(height, 2) + pow(leg->Humerus, 2)) / (2 * leg->Radius * leg->Humerus)))), 0, 180, 180, 0);
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

    hip1Servo.write(180);
    knee1Servo.write(0);
    hip2Servo.write(0);
    knee2Servo.write(180);

    delay(100); // small delay to allow servo to reach initial position
    Serial.begin(9600);
}


void loop()
{
    // if (Serial.available())
    // {
    //     char c = Serial.read();

    //     if (c == 'a') // raise leg
    //     {
    //         pos = pos >= height ? height : pos + 0.5;
    //         calc_angles(&leg1, pos);
    //         calc_angles(&leg2,pos);
    //         hip1Servo.write(leg1.hip_angle);
    //         knee1Servo.write(leg1.knee_angle);
    //         hip2Servo.write(leg2.hip_angle);
    //         knee2Servo.write(leg2.knee_angle);
    //         Serial.println("Hip1: " + String(leg1.hip_angle) + " Knee1: " + String(leg1.knee_angle) + "height :" + String(pos) + "Hip2: " + String(leg2.hip_angle) + " Knee1: " + String(leg1.knee_angle));
    //     }
    //     else if (c == 's') // lower leg
    //     {
    //         pos = pos <= 0 ? 0 : pos - 0.5;
    //         calc_angles(&leg1, pos);
    //         hip1Servo.write(leg1.hip_angle);
    //         knee1Servo.write(leg1.knee_angle);
    //         Serial.println("Hip1: " + String(leg1.hip_angle) + " Knee1: " + String(leg1.knee_angle) + "height :" + String(pos) + "Hip2: " + String(leg2.hip_angle) + " Knee1: " + String(leg1.knee_angle));
    //     }
    // }
}