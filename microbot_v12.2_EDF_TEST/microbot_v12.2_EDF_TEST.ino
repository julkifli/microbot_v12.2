/*
MiCROBOT V12.2

Julkifli Awang Besar
C0d3 for EDF Testing - non BEL

Suite with MiCROBOT PCB.

*/

#include <Servo.h>
Servo ESC;

void setup() {
  ESC.attach(3);//Brushless attach
  ESC.writeMicroseconds(1000); //1000-2500 maxspeed for Brushless
  delay(1000);
}

void loop() {
        ESC.attach(3);//Brushless attach
        ESC.writeMicroseconds(1400); //1000-2500 maxspeed for Brushless
        delay(300);
}
