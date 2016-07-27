#include <IRremote.h>
#include "xinda_remote.h"
#include "juk.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник
decode_results ir_result;

double azimuth = 0;
IrXindaRemoteCode last_it_code = ircUp;

void setup() 
{
    Serial.begin(9600);
    

    setupLegs();

    t_start = millis();
    irrecv.enableIRIn(); // запускаем прием

    // warm();

    //allLegsSet90();
}

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

double mapDouble(double t, double t_min, double t_max, double out_min, double out_max)
{
    return ((t - t_min) / (t_max - t_min)) * (out_max - out_min) + out_min;
}

void smoothAzimuth(double dt, double a_start, double a_end, double t_start)
{
    double t_min = millis();
    double t = t_min;
    double t_max = t_min + dt;
    while (t < t_max)
    {
        double azimuth = mapDouble(t, t_min, t_max, a_start, a_end);
        stepAllLegs(azimuth, t_start);
        t = millis();
    }
}

void loop() 
{
    //// Хождение по кругу
    // stepAllLegs(double(millis())/8000.0 * 360);

    
    if (irrecv.decode(&ir_result))
    {
        double new_azimuth = azimuth;
        getAzimuth(new_azimuth, getXindaCode(ir_result.value), last_it_code);
        if (fabs(new_azimuth - azimuth) > 1.0)
        {
            smoothAzimuth(700, azimuth, new_azimuth, t_start);
        }
        irrecv.resume(); // принимаем следующую команду        
        azimuth = new_azimuth;
    }
   // else Serial.println("no command");
    stepAllLegs(azimuth, t_start);  
  
}
