#include "matrix4.h"

static double mycos(double deg)
{
    return cos(PI * deg / 180.0);
}

static double mysin(double deg)
{
    return sin(PI * deg / 180.0);
}

Matrix4x4::Matrix4x4()
{ /// Инициализируем все переменные
    clear();
}

   // Matrix4x4();                                // Конструктор.
   // Matrix4x4(const Matrix4x4 &m);             // Перегруженный конструктор.
    // Matrix4x4(double r11, double r12, double r13, double r14,
              // double r21, double r22, double r23, double r24,
              // double r31, double r32, double r33, double r34,
              // double r41, double r42, double r43, double r44);


    /// Загрузка единичной матрицы
void Matrix4x4::clear()
{ 
    matrix[0]  = 1.0f; matrix[1]  = 0.0f; matrix[2]  = 0.0f; matrix[3]  = 0.0f;
    matrix[4]  = 0.0f; matrix[5]  = 1.0f; matrix[6]  = 0.0f; matrix[7]  = 0.0f;
    matrix[8]  = 0.0f; matrix[9]  = 0.0f; matrix[10] = 1.0f; matrix[11] = 0.0f;
    matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = 1.0f;
}

//static Matrix4x4 inverse(const Matrix4x4 & m);


    Matrix4x4 & Matrix4x4::operator=(const Matrix4x4 & m)                // Перегруженный оператор =
    {
        // Устанавливает все значения матрицы в значения "m"
        matrix[0] = m.matrix[0];  matrix[1] = m.matrix[1];  matrix[2] = m.matrix[2];  matrix[3] = m.matrix[3];
        matrix[4] = m.matrix[4];  matrix[5] = m.matrix[5];  matrix[6] = m.matrix[6];  matrix[7] = m.matrix[7];
        matrix[8] = m.matrix[8];  matrix[9] = m.matrix[9];  matrix[10]= m.matrix[10]; matrix[11]= m.matrix[11];
        matrix[12]= m.matrix[12]; matrix[13]= m.matrix[13]; matrix[14]= m.matrix[14]; matrix[15]= m.matrix[15];
        return (*this);
    }


    inline Vector4 Matrix4x4::operator *(const Vector4 & v) const             // Vector4 * matrix (умножение вектора на матрицу)
    {
        return Vector4(matrix[0] * v.X + matrix[4] * v.Y + matrix[8]  * v.Z + matrix[12] * v.W,
                        matrix[1] * v.X + matrix[5] * v.Y + matrix[9]  * v.Z + matrix[13] * v.W,
                        matrix[2] * v.X + matrix[6] * v.Y + matrix[10] * v.Z + matrix[14] * v.W,
                        matrix[3] * v.X + matrix[7] * v.Y + matrix[11] * v.Z + matrix[15] * v.W);
    }

   // void translate(const Vector4 & Translate);          // Трансляция точки в 3D.
   // void translate(double x, double y, double z);   // Трансляция точки в 3D.



