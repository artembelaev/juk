#ifndef __CMATRIX_H
#define __CMATRIX_H

#include "vector4.h"

#ifndef PI
    #define PI 3.14159265359
#endif

class Matrix4x4
{
public:
    Matrix4x4();                                // Конструктор.
    Matrix4x4(const Matrix4x4 &m);             // Перегруженный конструктор.
    Matrix4x4(double r11, double r12, double r13, double r14,
              double r21, double r22, double r23, double r24,
              double r31, double r32, double r33, double r34,
              double r41, double r42, double r43, double r44);


    /// Загрузка единичной матрицы
    void clear();
    static Matrix4x4 inverse(const Matrix4x4 & m);


    Matrix4x4 & operator=(const Matrix4x4 & m);
    Matrix4x4 operator-(const Matrix4x4 & m) const;
    Matrix4x4 operator+(const Matrix4x4 & m) const;
    Matrix4x4 operator*(const Matrix4x4 & m) const;
    Matrix4x4 operator/(const Matrix4x4 & m) const;
    Matrix4x4 & operator *=(const Matrix4x4 & m);
    Matrix4x4 & operator /=(const Matrix4x4 & m);


    inline Vector4 operator *(const Vector4 & v) const;

    void translate(const Vector4 & Translate);          // Трансляция точки в 3D.
    void translate(double x, double y, double z);   // Трансляция точки в 3D.

    double matrix[16];                            // 4x4 матрица в одномерном массиве.
};

#endif
