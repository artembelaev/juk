#include <IRremote.h>
#include "xinda_remote.h"
#include "juk.h"

IRrecv irrecv(11); // указываем вывод, к которому подключен приемник
decode_results ir_result;

double AZIMUTH = 0;
IrXindaRemoteCode LAST_IR_CODE = ircUp;

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

void loop() 
{
    //// Хождение по кругу
    // stepAllLegs(double(millis())/8000.0 * 360);

    
    
    if (irrecv.decode(&ir_result))
    {
        getAzimuth(AZIMUTH, getXindaCode(ir_result.value), LAST_IR_CODE);
        Serial.println(ir_result.value, HEX); // печатаем данные
        Serial.print("no command");
        Serial.println(AZIMUTH);
        irrecv.resume(); // принимаем следующую команду        
    }
   // else Serial.println("no command");
    stepAllLegs(AZIMUTH);  
  
}
