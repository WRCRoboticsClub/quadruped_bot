#ifndef QUADRUPED_H
#define QUADRUPED_H
// #pragma once
#include <ESP32Servo.h>

enum Side
{
    left = 0,
    right = 1
};
enum Front_back
{
    front = 0,
    back = 1
};
class Leg
{
private:
    const double Humerus;
    const double Radius;
    double height;
    double length;
    double hip_angle;
    double knee_angle;
    double hip_offset = 0;
    double knee_offset = 0;
    int hip_Pin;
    int knee_Pin;
    double step_size;  // distance covered by leg in 1 footstep
    int side;
    int longitudinal;

public:
    Servo servohip;
    Servo servoknee;
    int pos;
    Leg(double Humerus, double Radius, int hip_pin, int knee_pin,int longitudinal, int side);
    void set_offset(double hip_offset, double knee_offset);
    void get_angles(double height, double length);
    void calibrate(String name);
    void move_vertical();
    void move_horizontal();
    void init( double Height, double length, double step_size);
    void moveTo_base_pos();
    void move_leg();
    double get_hip_offset();
    double get_knee_offset();
    double get_hip_angle();
    double get_knee_angle();
    void move_arc();
    void crawl_forward();
    void move_angles(double hipangle, double kneeangle);
    void print_angles(double length, double height);
};

class Quadruped
{
private:
    Leg &Front_Right;
    Leg &Front_Left;
    Leg &Back_Right;
    Leg &Back_Left;
    double height;
    double length;
    double step_size; // distance covered by bot in 1 footstep
    int initial_position = -1;

public:
    Quadruped(Leg &fr, Leg &fl, Leg &br, Leg &bl)
        : Front_Right(fr),
          Front_Left(fl),
          Back_Right(br),
          Back_Left(bl)
    {
    }
    void init(double height, double length, double step_size);
    void move_bot();
    void move_forward();
    void move_backward();
    void sit_down();
    void stand_up();
    void say_hi();
    void shake_hand();
    void moveTo_base_pos();
    void move_vert();
    void calibrate();
};
#endif