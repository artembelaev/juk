#ifndef __ADV_MATH_H
#define __ADV_MATH_H

#include <math.h>
#include "vector4.h"

/// Линейная интерполяция вектора по времени
Vector4 mapVector(double t, double t_min, double t_max, const Vector4 & out_min, const Vector4 & out_max);

/// Приведение угла в диапазон (0, 360) градусов
double normalizeAngle(double angle);

#endif // __ADV_MATH_H
