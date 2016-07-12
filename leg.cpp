#include "leg.h"


Leg::Leg(Leg::Side side,
        int pin_base,
        int pin_femur,
        int pin_tibia,
        double x_pos,
        double y_pos,
        double z_pos):
    FSide(side),
    FPos(x_pos, y_pos, z_pos)
{
    FServoBase.attach(pin_base);
    FServoFemur.attach(pin_femur);
    FServoTibia.attach(pin_tibia);
}

static bool intersectCircleWithLine(
    double & x, double & y,      // Искомые координаты
    double r,                   // Радиус окружности (с центром в начале координат)
    double a, double b, double c) // Коэффициенты уравнения прямой a*x + b*y + c = 0
{
    double x0 = -a*c / (a*a + b*b);
    double y0 = -b*c / (a*a + b*b);
    const double EPS = 0.001;

    double param = c*c - r*r*(a*a+b*b);

    if (param > EPS)                // 0 points
        return false;
    else if (fabs(param) < EPS)    // 1 point
    {
        x = x0;
        y = y0;
    }
    else                            // 2 points
    {
        double d = r*r - c*c/(a*a+b*b);
        double mult = sqrt (d / (a*a+b*b));

        double ax = x0 + b * mult;
        double bx = x0 - b * mult;
        double ay = y0 - a * mult;
        double by = y0 + a * mult;
        // Выбираем верхнюю точку, чтобы коленки были вверху
        x = (ay > by) ? ax : bx;
        y = (ay > by) ? ay : by;
    }
    return true;
}

/// Пересечение двух окружностей (одна из двух точек, которая выше)
/**
 Возвращает true, если имеется хотя бы одно пересечение, иначе false

 Если центры окружностей совпадают, возвращает false
*/
static bool intersectCircles(
    double & x, double & y,     // Искомые координаты
    double r1,                 // Радиус первой окружности (с центром в начале координат)
    double x2, double y2,       // Координаты центра второй окружности
    double r2)                 // Радиус второй окружности
{
    if (x2 == 0 && y2 == 0) return false;
 
    // Сведем нашу задачу к пересечению окружности и прямой
    // Коэффициенты уравнения прямой a*x + b*y + c = 0 
    double a = -2*x2;
    double b = -2*y2;
    double c = x2*x2 + y2*y2 + r1*r1 - r2*r2;
    
    return intersectCircleWithLine(x, y, r1, a, b, c);
}

void Leg::moveTo(const Vector4 & point)
{
    double x = point.x();
    double y = point.y();
    double z = point.z();
    
    double base_angle = atan2(y, x) * 180.0 / PI;
    FServoBase.write(90 + base_angle);
        
    // Координаты коленки в плоскости бедра и голени (относительно бедренного сустава)
    double knee_x;
    double knee_y;
    // Координаты кончика ноги в той же системе
    double x2 = sqrt(x*x + y*y) - FEMUR_LEDGE;
    double y2 = -(point.z() - FEMUR_H);
    if (intersectCircles(knee_x, knee_y, FEMUR_LENGTH, x2, y2, TIBIA_LENGTH))
    {
        double femur_angle = atan2(knee_y, knee_x) * 180.0 / PI;
        double tibia_angle = femur_angle + atan2(-(y2 - knee_y), x2 - knee_x) * 180 / PI;
        FServoFemur.write(90 + femur_angle);
        FServoTibia.write(tibia_angle);
    }
}







