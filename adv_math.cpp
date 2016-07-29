#include "adv_math.h"
#include <math.h>

double mapDouble(double t, double t_min, double t_max, double out_min, double out_max)
{
    return ((t - t_min) / (t_max - t_min)) * (out_max - out_min) + out_min;
}

Vector4 mapVector(double t, double t_min, double t_max, const Vector4 & out_min, const Vector4 & out_max)
{
    return Vector4(((t - t_min) / (t_max - t_min)) * (out_max - out_min) + out_min);
}

double normalizeAngle(double angle)
{
    bool minus = false;
    if (angle < 0)
    {
        angle *= -1;
        minus = true;
    }
    angle = fmod(angle, 360);

    if (minus) angle = 360 - angle;

    return angle;
}

Vector4 rotateZ(const Vector4 & v, double a)
{
    double sin_a = sinDeg(a);
    double cos_a = cosDeg(a);
    return Vector4(v.x()*cos_a - v.y()*sin_a, 
                   v.x()*sin_a + v.y()*cos_a, 
                   v.z(), 
                   v.w());
}

double sinDeg(double a)
{
    return sin(PI * a / 180.0);
}

double cosDeg(double a)
{
    return cos(PI * a / 180.0);
}

