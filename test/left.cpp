#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float height = 18;
float pos = 10;

typedef struct
{
    double Humerus;
    double Radius;
    double hip_angle;
    int knee_angle;
} Leg;

Leg leg[4];
Servo hip1, knee1;

int map_int(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void calc_angles(Leg *leg, double height)
{
    leg->hip_angle = 90 - floor((180 / M_PI) * (acos((pow(leg->Humerus, 2) + pow(height, 2) - pow(leg->Radius, 2)) / (2 * height * leg->Humerus))));
    leg->knee_angle =  map(floor((180 / M_PI) * (acos((pow(leg->Radius, 2) - pow(height, 2) + pow(leg->Humerus, 2)) / (2 * leg->Radius * leg->Humerus)))),0,180,180,0);
}

void setup()
{
    Serial.begin(9600);


    hip1.attach(27);   // Hip on GPIO 13
    knee1.attach(26);  // Knee on GPIO 14

    for (int i = 0; i < 4; i++)
    {
        leg[i].Humerus = 8;
        leg[i].Radius = 10.25;
    }

    hip1.write(0);///158
    knee1.write(180);//65

    Serial.println("Hip (13) & Knee (14) Servo Ready");
}

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();

        if (c == 'a') // raise leg
        {
            pos = pos >= height ? height : pos + 0.5;
            calc_angles(&leg[0], pos);
            hip1.write(leg[0].hip_angle);
            knee1.write(leg[0].knee_angle);
            Serial.println("Hip: " + String(leg[0].hip_angle) + " Knee: " + String(leg[0].knee_angle) + "height :" + String(pos));
        }
        else if (c == 's') // lower leg
        {
            pos = pos <= 10 ? 10 : pos - 0.5;
            calc_angles(&leg[0], pos);
            hip1.write(leg[0].hip_angle);
            knee1.write(leg[0].knee_angle);
            Serial.println("Hip: " + String(leg[0].hip_angle) + " Knee: " + String(leg[0].knee_angle) + "height" + String(pos));
        }
    }
}

