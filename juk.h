#ifndef __JUK_H
#define __JUK_H

#include "leg.h"
#include <math.h>
#include "adv_math.h"

/// Вычисление положения ноги при перемещении прямо
Vector4 stepLeg(
    double t,               // Текущее время (мс) 
    double t0,              // Время начала движения (мс)
    double phase,           // Задержка по фазе (безразмерное в диапазоне [0, 1])
    const Vector4 & point0, // Координаты базовой точки ноги - середина основания треугольнияка (мм)
    const Vector4 & v,      // Скорость перемещения жука (мм/с)
    double step_l,          // Длина шага - длина основания треугольника (мм)
    double step_h)          // Высота шага - высота треугольника над базовой точкой (мм) 
{
    double v_abs = v.length();
    double period =  2 * step_l  / v_abs * 1000; // Период шага (мc)
    t -= t0;              // время с начала движения
    t += phase * period;  // с учетом фазы
    t = fmod(t, period);  // время с начала текущего периода 
    
    Vector4 delta01 = v  / v_abs * step_l / 2;

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

/// Вычисление положения ноги при повороте вокруг оси oZ
Vector4 turnLeg(
    double t,               // Текущее время (мс) 
    double t0,              // Время начала движения (м)
    double phase,           // Задержка по фазе (безразмерное в диапазоне [0, 1])
    const Vector4 & point0, // Координаты базовой точки ноги - середина основания треугольнияка (мм)
    double w,               // Угловая скорость поворота жука по оси oZ (г/с)
    double ampl,            // Амплитуда поворота кончика ноги (мм)
    double step_h)          // Высота шага - высота треугольника над базовой точкой (мм) 
{
    double period =  4000 * ampl / fabs(w); // Период шага (мc)

    t -= t0;              // время с начала движения
    t += phase * period;  // с учетом фазы
    t = fmod(t, period);  // время с начала текущего периода 

    double t1 = period / 4;
    double t2 = period / 2;
    double t3 = period / 4 * 3;

    if (w < 0) ampl *= -1;
    
    double h = 0;
    double alpha = 0;
    if (t <= t1)
    {
        alpha = mapDouble(t, 0, t2, 0, -ampl);
    }
    else if (t > t1 && t <= t2) 
    {
        alpha = mapDouble(t, t1, t2, -ampl, 0);
        h = mapDouble(t, t1, t2, 0, step_h);
    }
    else if (t > t2 && t < t3) 
    {
        alpha = mapDouble(t, t2, t3, 0, ampl);
        h = mapDouble(t, t2, t3, step_h, 0);
    }
    else 
    {
        alpha = mapDouble(t, t3, period, ampl, 0);
    }
    return rotateZ(point0, alpha) - Vector4(0, 0, h);
    
}

Leg leg_l1(Leg::Left,   0,  1,  2, Vector4( 35, 90), - 3.5, -6.0, -4);    
Leg leg_l2(Leg::Left,   3,  4,  5, Vector4( 35,  0), - 8.0, +6.0, +5.0);    
Leg leg_l3(Leg::Left,   6,  7,  8, Vector4( 35,-90), -10.0, -6.0, -5.0);    
Leg leg_r1(Leg::Right, 17, 16, 15, Vector4(-35, 90), + 3.0, -3.0, +2.0);
Leg leg_r2(Leg::Right, 14, 13, 12, Vector4(-35,  0), + 3.5, +5.0, -8.0);
Leg leg_r3(Leg::Right,  9, 10, 11, Vector4(-35, -90), - 7.5, -7.0, -9.0);


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

    Vector4 tip_points[] = {Vector4( 50,  25, 75), Vector4( 60,  00, 75), Vector4( 50, -25, 75),
                            Vector4(-50,  25, 75), Vector4(-60,  00, 75), Vector4(-50, -25, 75)};

    for (int i = 0; i < LEG_COUNT; ++i)
        legs[i]->setTipPoint(legs[i]->basePoint() + tip_points[i]);    
}

void allLegsSet90()
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        Leg * leg = legs[i];   
        leg->setServoAngles(90, 90, 90);
    }
}

void warm()
{
    for (int i = 0; i < 700; ++i)
    {
        double d = i;
        double alpha = d / 250.0 * 2*PI;
    
//    // Колебания по продольной оси
//    leg_l1.moveTo(Vector4(35, 30*sin(alpha), 70));
//    leg_l2.moveTo(Vector4(35, 30*sin(alpha), 70));
//    leg_l3.moveTo(Vector4(35, 30*sin(alpha), 70));
//
//    leg_r1.moveTo(Vector4(-35, 30*sin(alpha), 70));
//    leg_r2.moveTo(Vector4(-35, 30*sin(alpha), 70));
//    leg_r3.moveTo(Vector4(-35, 30*sin(alpha), 70));

    // Колебания по вертикали
//    leg_l1.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//    leg_l2.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//    leg_l3.moveTo(Vector4(35, 0, 100.0 + 40 * sin(alpha)));
//
//    leg_r1.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
//    leg_r2.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));
//    leg_r3.moveTo(Vector4(-35, 0, 100.0 + 40 * sin(alpha)));


    // Колебания по всем осям

        double dy = 18* sin(alpha);
        double dz = 12 * cos(2*alpha);
        double dx = 16 * cos(alpha);
    
        Vector4 delta(dx, dy, dz);
    
        leg_l1.moveTo(leg_l1.tipPoint() + delta);
        leg_l2.moveTo(leg_l2.tipPoint() + delta);
        leg_l3.moveTo(leg_l3.tipPoint() + delta);
    
        leg_r1.moveTo(leg_r1.tipPoint() + delta);
        leg_r2.moveTo(leg_r2.tipPoint() + delta);
        leg_r3.moveTo(leg_r3.tipPoint() + delta);


    //leg_r1.setServoAngles(90, 90, 90);
    
    //delayMicroseconds(1);
  }
}

void stepAllLegs(double azimuth, double t_start)
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        unsigned long t = millis();    
        double phase = (i%2 == 0) ? 0.0 : 0.5; // смещение по фазе для правых ног
        Leg * leg = legs[i];

        double v_abs = 40; // мм/с
        Vector4 v(v_abs * sinDeg(azimuth), v_abs * cosDeg(azimuth));
        
        leg->moveTo(stepLeg(t, t_start, phase, leg->tipPoint(), v, 40, 35));
    }
}
/*Vector4 turnLeg(
    double t,               // Текущее время (мс) 
    double t0,              // Время начала движения (м)
    double phase,           // Задержка по фазе (безразмерное в диапазоне [0, 1])
    const Vector4 & point0, // Координаты базовой точки ноги - середина основания треугольнияка (мм)
    double w,               // Угловая скорость поворота жука по оси oZ (г/с)
    double ampl,            // Амплитуда поворота кончика ноги (мм)
    double step_h)          // Высота шага - высота треугольника над базовой точкой (мм)*/
void turnAllLegs(double w, double ampl, double t_start)
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        unsigned long t = millis();    
        double phase = (i%2 == 0) ? 0.0 : 0.5; // смещение по фазе для правых ног
        Leg * leg = legs[i];
        
        leg->moveTo(turnLeg(t, t_start, phase, leg->tipPoint(), w, ampl, 35));
    }
}

#endif // __JUK_H
