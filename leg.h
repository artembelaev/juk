#include <Multiservo.h>

#ifndef __LEG_H
#define __LEG_H

#include <Multiservo.h>
#include "vector4.h"
#include "matrix4.h"

// Длина бедра (мм)
#define FEMUR_LENGTH 50.0

// Длина голени (мм)
#define TIBIA_LENGTH 70.0

// Высота начала бюедра - расстояние по вертикали от основания ноги до оси бедренного сустава (мм)
#define FEMUR_H 25.7        

// Выступ бедра - расстояние между осями основного и бедренного сервопривода (мм)
#define FEMUR_LEDGE 11.8   // равняется ширине сервопривода


/// Нога робота 
class Leg
{
public:
    
    /// Сторона жука, на которой расположена нога
    enum Side
    {
        Left,
        Right
    };

    /// Конструктор, принимающий пины приводов, координаты точки крепления ноги
    Leg(Side side,                              // Сторона жука, на которой расположена нога
        int pin_base,                           // Привод поворота ноги 
        int pin_femur,                          // Привод поворота бедра по вертикали
        int pin_tibia,                          // Привод поворота голени (коленка жука)
        const Vector4 & base_point,             // Координаты точки крепления ноги (мм)
        double delta_base = 0, 
        double delta_femur = 0, 
        double delta_tibia = 0
      );

    /// Перемещение кончика ноги к точке (мм)
    /** 
     В координатах жука
     */
    void moveTo(const Vector4 & point);

    /// Координаты точки крепления ноги (мм)
    Vector4 basePoint() const;
    
    /// Начальные координаты кончика ноги (мм)
    Vector4 tipPoint() const;
    void setTipPoint(const Vector4 & value);
    
    /// Управление сервами напрямую
    void setServoAngles(double base, double femur, double tibia);

private:
    Side FSide;
    Multiservo FServoBase;
    Multiservo FServoFemur;
    Multiservo FServoTibia;

    Vector4 FTipPoint;
    Vector4 FBasePoint;
    
    double FDeltaBase;
    double FDeltaFemur;
    double FDeltaTibia;

    bool right() const;
};

#endif // __LEG_H


