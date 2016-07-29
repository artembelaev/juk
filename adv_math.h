#ifndef __ADV_MATH_H
#define __ADV_MATH_H

#include <math.h>
#include "vector4.h"
#define PI 3.14159265359

/// Линейная интерполяция числа по времени
double mapDouble(double t, double t_min, double t_max, double out_min, double out_max);

/// Линейная интерполяция вектора по времени
Vector4 mapVector(double t, double t_min, double t_max, const Vector4 & out_min, const Vector4 & out_max);

/// Поворот вектора v вокруг оси oZ на угол a (в градусах)
Vector4 rotateZ(const Vector4 & v, double a);

/// Приведение угла в диапазон (0, 360) градусов
double normalizeAngle(double angle);

double sinDeg(double a);
double cosDeg(double a);

#endif // __ADV_MATH_H
