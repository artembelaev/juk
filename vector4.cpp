#include "vector4.h"

Vector4 operator *(double f, const Vector4 & v)
{
    return Vector4(v.X * f, v.Y * f, v.Z * f);
}


