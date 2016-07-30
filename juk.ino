#include <IRremote.h>
#include "xinda_remote.h"
#include "juk.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник

IrXindaRemoteCode last_ir_code = ircUp;

void getAzimuth(double & a, IrXindaRemoteCode code, IrXindaRemoteCode & last_code)
{
    if (code == ircLast)
        code = last_code;

    switch (code)
    {
        case ircUp:     a = 0; break;
        case ircDown:   a = 180; break;
        case ircLeft:   a = 90; break;
        case ircRight:  a = 270; break;
        default: return;
    }
    last_code = code;
    
}

double phase_prev = 0;
double t_prev = 0;
double azimuth = 0;
unsigned long t_start = 0;

/// Плавное изменение направления шага ноги в сторону наименьшего поворота
void smoothV(double dt, const Vector4 & v_start, const Vector4 & v_end, double & phase_prev, double & t_prev)
{    
    double t_min = millis();
    double t = t_min;
    double t_max = t_min + dt;
    while (t < t_max)
    {
        t = millis();
        Vector4 v = mapVector(t, t_min, t_max, v_start, v_end);
        phase_prev = stepAllLegs(v, phase_prev, t - t_prev);
        t_prev = t;
    }
}

void turn(double dt, double w, double ampl)
{
    double t_min = millis();
    double t = t_min;
    double t_max = t_min + dt;
    while (t < t_max)
    {
        turnAllLegs(w, ampl, t_start);
        t = millis();
    }
}


void setup() 
{
    Serial.begin(9600);
    

    setupLegs();

    t_start = millis();
    t_prev = t_start;
    irrecv.enableIRIn(); // запускаем прием

    // warm();

    //allLegsSet90();
}

Vector4 getV(double azimuth, double v_abs)
{
    return Vector4(v_abs * sinDeg(azimuth), v_abs * cosDeg(azimuth));
}

void loop() 
{
    //// Хождение по кругу
    // stepAllLegs(double(millis())/8000.0 * 360);
    double v_abs = 70; // мм/с
    decode_results ir_result;
    if (irrecv.decode(&ir_result))
    {
        
        double new_azimuth = azimuth;
        getAzimuth(new_azimuth, getXindaCode(ir_result.value), last_ir_code);
        if (fabs(new_azimuth - azimuth) > 1.0)
        {
            smoothV(800, getV(azimuth, v_abs), getV(new_azimuth, v_abs), phase_prev, t_prev);
        }
        irrecv.resume(); // принимаем следующую команду
        azimuth = new_azimuth;
    }
    
    double t = millis();
    phase_prev = stepAllLegs(getV(azimuth, v_abs), phase_prev, t - t_prev);
    t_prev = t;

   // turn(5000, 25, 10);
    //turn(5000, -25, 10);
    
  
}
