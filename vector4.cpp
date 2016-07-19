#include "vector4.h"

Vector4 operator *(double f, const Vector4 & v)
{
    return Vector4(v.X * f, v.Y * f, v.Z * f);
}

Vector4 mapVector(double t, double t_min, double t_max, const Vector4 & out_min, const Vector4 & out_max)
{
    return Vector4(((t - t_min) / (t_max - t_min)) * (out_max - out_min) + out_min);
}

