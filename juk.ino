#include "leg.h"



Leg leg_l1(Leg::Left,  0,  1,  2);    Leg leg_r1(Leg::Right,  3,  4, 5);
Leg leg_l2(Leg::Left, 17, 16, 15);    Leg leg_r2(Leg::Right, 14, 13, 12);
Leg leg_l3(Leg::Left,  6,  7,  8);    Leg leg_r3(Leg::Right,  9, 10, 11);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 300; ++i)
  {
    double d = i;
    double alpha = d / 300.0 * 2*PI;
    //leg_l1.moveTo(Vector4(70 + 30 * cos(alpha), 30 * sin(alpha), 50.0));

    // Колебания по вертикали
//    leg_l1.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//    leg_l2.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//    leg_l3.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//
//    leg_r1.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
//    leg_r2.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
//    leg_r3.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));


    // Колебания по всем осям

    double h = 80.0 + 20* sin(alpha);
    double dy = 15 * cos(2*alpha);
    double dy_left = 60 + dy;
    double dy_right = -60 + dy;
    double step_ = 20 * cos(alpha);
    

    leg_l1.moveTo(Vector4(dy_left, step_, h));
    leg_l2.moveTo(Vector4(dy_left, step_, h));
    leg_l3.moveTo(Vector4(dy_left, step_, h));

    leg_r1.moveTo(Vector4(dy_right, step_, h));
    leg_r2.moveTo(Vector4(dy_right, step_, h));
    leg_r3.moveTo(Vector4(dy_right, step_, h));


    //leg_r1.setServoAngles(90, 90, 90);
    
    //delayMicroseconds(1);
  }
}
