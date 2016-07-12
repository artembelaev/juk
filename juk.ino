#include "leg.h"

Leg leg(Leg::Left, 0, 1, 2);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 3000; ++i)
  {
    double d = i;
    double alpha = d / 3000.0 * 2*PI;
    leg.moveTo(Vector4(70 + 30 * cos(alpha), 30 * sin(alpha), 50.0));

    //delayMicroseconds(1);
  }
}
