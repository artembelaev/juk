#include "adv_math.h"

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

