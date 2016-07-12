#ifndef __CVECTOR_H
#define __CVECTOR_H

#include <math.h>

//#define PI 3.14159265359

class Vector4
{
public:

    Vector4()
    { 
        X = Y = Z = 0.0;
        W = 1.0;
    }
    Vector4(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
        W = 1.0;
    }
    Vector4(double x, double y, double z, double w)
    { 
        X = x;
        Y = y;
        Z = z;
        W = w;
    }
    Vector4(const Vector4 &v)
    {
        X = v.X;
        Y = v.Y;
        Z = v.Z;
        W = v.W;
    }

    Vector4 & operator=(const Vector4 & v)
    { /// Делает переменные x, y,z и w эквивалентными обьекту справа от знака "=".
       X = v.X;
       Y = v.Y;
       Z = v.Z;
       W = v.W;
       return (*this);
    }
    Vector4 operator-(const Vector4 & v) const
    { /// Возвращает значения этого вектора минус v.
       return Vector4(X - v.X, Y - v.Y, Z - v.Z);
    }
    Vector4 operator-() const
    { /// Возвращает значения этого вектора, умноженного на единицу.
       return Vector4(-X, -Y, -Z);
    }
    Vector4 operator+(const Vector4 & v) const
    { /// Возвращает значения этого вектора плюс v.
       return Vector4(X + v.X, Y + v.Y, Z + v.Z);
    }

    inline Vector4 operator+(double f) const { return Vector4(X + f, Y + f, Z + f);}
    inline Vector4 operator-(double f) const { return Vector4(X - f, Y - f, Z - f);}
    inline Vector4 operator*(double f) const { return Vector4(X * f, Y * f, Z * f);}
    inline Vector4 operator/(double f) const
    {
        f = 1/f;
        return Vector4(X * f, Y * f, Z * f);
    }

    Vector4 & operator +=(const Vector4 & v)
    {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return (*this);
    }
    
    Vector4 & operator -=(const Vector4 & v)
    {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return (*this);
    }
    
    Vector4 & operator *=(double f)
    {
        X *= f;
        Y *= f;
        Z *= f;
        return (*this);
    }
    
    Vector4 & operator /=(double f)
    {
        f = 1/f;
        X *= f;
        Y *= f;
        Z *= f;
        return (*this);
    }

    /// Длина вектора
    double length() const                                 
    {
        return sqrt(X * X + Y * Y + Z * Z);
    }

    /// Нормализует вектор
    void normal()
    {
        double lenght = length();

        if(lenght == 0.0f)
           lenght = 1.0f;
    
        X = X/lenght;
        Y = Y/lenght;
        Z = Z/lenght;
        W = W/lenght;
    }

    inline double x() const {return X;}
    inline double y() const {return Y;}
    inline double z() const {return Z;}
    inline double w() const {return W;}
    inline void setX (double value) {X = value;}
    inline void setY (double value) {Y = value;}
    inline void setZ (double value) {Z = value;}
    inline void setW (double value) {W = value;}
    inline void setXYZ(double x, double y, double z) {X = x; Y = y; Z = z;}
    inline void setXYZW(double x, double y, double z, double w) {X = x; Y = y; Z = z; W = w;}

//private:
    double X, Y, Z, W;                                  // Вершинные x, y, и z координаты.
};

#endif

