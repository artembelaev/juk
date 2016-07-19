#include "leg.h"
#include <math.h>

/// Вычисление положения ноги 
Vector4 stepLeg(
    double t,               // Текущее время (мсек) 
    double t0,              // Время начала движения (мсек)
    double period,          // Период шага (мсек)
    double phase,           // Задержка по фазе (безразмерное в диапазоне [0, 1])
    const Vector4 & point0, // Координаты базовой точки ноги - середина основания треугольнияка (мм)
    double azimuth,         // Направление движения робота относительно оси oy по оси oz (градусы)
    double step_l,          // Длина шага - длина основания треугольника (мм)
    double step_h)          // Высота шага - высота треугольника над базовой точкой (мм) 
{
    t -= t0;              // время с начала движения
    t += phase * period;  // с учетом фазы
    t = fmod(t, period);  // время с начала текущего периода
    
    double azimuth_rad = azimuth*PI/180.0;
    
    Vector4 delta01(sin(azimuth_rad)*step_l/2, cos(azimuth_rad)*step_l/2, 0); // смещение первой точки относительно базовой

    double t1 = period / 4;
    double t2 = period / 2;
    double t3 = period / 4 * 3;
    
    Vector4 point1 = point0 - delta01;
    Vector4 point2(point0.x(), point0.y(), point0.z() - step_h);
    Vector4 point3 = point0 + delta01;
    
    if (t <= t1) return mapVector(t, 0, t1, point0, point1);
    else if (t > t1 && t <= t2) return mapVector(t, t1, t2, point1, point2);
    else if (t > t2 && t < t3) return mapVector(t, t2, t3, point2, point3);
    else return mapVector(t, t3, period, point3, point0);
}

Leg leg_l1(Leg::Left,   0,  1,  2, 0, 0, 0, - 3.5, -6.0, -2.5);    
Leg leg_l2(Leg::Left,  17, 16, 15, 0, 0, 0, - 8.0, +6.0, +7.5);    
Leg leg_l3(Leg::Left,   6,  7,  8, 0, 0, 0, -10.0, -7.0, -5.0);    
Leg leg_r1(Leg::Right,  3,  4,  5, 0, 0, 0, + 4.0, -4.0, +2.0);
Leg leg_r2(Leg::Right, 14, 13, 12, 0, 0, 0, + 5.5, +5.0, -8.0);
Leg leg_r3(Leg::Right,  9, 10, 11, 0, 0, 0, - 7.5, -5.0, -5.0);

#define LEG_COUNT 6

/// Массив ног 
/**
    Порядок: сначала левые, потом правые
*/
Leg * legs[LEG_COUNT]; 

unsigned long t_start = 0;

void setupLegs()
{
    legs[0] = &leg_l1;
    legs[1] = &leg_l2;
    legs[2] = &leg_l3;
    legs[3] = &leg_r1;
    legs[4] = &leg_r2;
    legs[5] = &leg_r3;    
}

void allLegsSet90()
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        Leg * leg = legs[i];   
        leg->setServoAngles(90, 90, 90);
    }
}

void setup() 
{
    Serial.begin(9600);

    setupLegs();
        
    t_start = millis();

   // allLegsSet90();
}


void stepAllLegs(double azimuth)
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        unsigned long t = millis();    
        double phase = (i%2 == 0) ? 0.0 : 0.5; // смещение по фазе для правых ног
        int sign = (i < 3) ? 1 : -1;
        Leg * leg = legs[i];
        
        leg->moveTo(stepLeg(t, t_start, 1200.0, phase, Vector4(60*sign, 5, 75), azimuth, 50, 35));
    }
}

void loop() 
{
    stepAllLegs(double(millis())/22000.0 * 360);
  
//  for (int i = 0; i < 300; ++i)
//  {
//    double d = i;
//    double alpha = d / 300.0 * 2*PI;
//
//    // Движение ноги по кругу
//    //leg_l1.moveTo(Vector4(70 + 30 * cos(alpha), 30 * sin(alpha), 50.0));
//    
////    // Колебания по продольной оси
////    leg_l1.moveTo(Vector4(35, 30*sin(alpha), 70));
////    leg_l2.moveTo(Vector4(35, 30*sin(alpha), 70));
////    leg_l3.moveTo(Vector4(35, 30*sin(alpha), 70));
////
////    leg_r1.moveTo(Vector4(-35, 30*sin(alpha), 70));
////    leg_r2.moveTo(Vector4(-35, 30*sin(alpha), 70));
////    leg_r3.moveTo(Vector4(-35, 30*sin(alpha), 70));
//
//    // Колебания по вертикали
////    leg_l1.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
////    leg_l2.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
////    leg_l3.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
////
////    leg_r1.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
////    leg_r2.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
////    leg_r3.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
//
//
//    // Колебания по всем осям
//
////    double h = 80.0 + 20* sin(alpha);
////    double dy = 15 * cos(2*alpha);
////    double dy_left = 60 + dy;
////    double dy_right = -60 + dy;
////    double step_ = 20 * cos(alpha);
////    
////
////    leg_l1.moveTo(Vector4(dy_left, step_, h));
////    leg_l2.moveTo(Vector4(dy_left, step_, h));
////    leg_l3.moveTo(Vector4(dy_left, step_, h));
////
////    leg_r1.moveTo(Vector4(dy_right, step_, h));
////    leg_r2.moveTo(Vector4(dy_right, step_, h));
////    leg_r3.moveTo(Vector4(dy_right, step_, h));
//
//
//    //leg_r1.setServoAngles(90, 90, 90);
//    
//    //delayMicroseconds(1);
//  }
}
