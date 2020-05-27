/*
MiCROBOT V12.2

Julkifli Awang Besar
C0d3 for Motor Test 

Suite with MiCROBOT PCB.

*/

// Motor L
int dir1A = 4;
int dir2A = 9;
int pwmA  = 5;
// Motor R
int dir1B = 7;
int dir2B = 8;
int pwmB  = 6;

int sw    = 12;

void setup()
{
  pinMode(dir1A, OUTPUT);
  pinMode(dir2A, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(dir1B, OUTPUT);
  pinMode(dir2B, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
 

}

void loop()
{
  if (digitalRead(sw) == HIGH)
  {
    while (1)
    {

      digitalWrite(dir1A, LOW);
      digitalWrite(dir2A, HIGH);
      analogWrite(pwmA, 0);//0-255 for maxspeed
      digitalWrite(dir1B, LOW);
      digitalWrite(dir2B, HIGH);
      analogWrite(pwmB, 0);//0-255 for maxspeed
      delay(5000);
      digitalWrite(dir1A, HIGH);
      digitalWrite(dir2A, LOW);
      analogWrite(pwmA, 0);//0-255 for maxspeed
      digitalWrite(dir1B, HIGH);
      digitalWrite(dir2B, LOW);
      analogWrite(pwmB, 0);//0-255 for maxspeed
      delay(5000);
      digitalWrite(dir1A, LOW);
      digitalWrite(dir2A, LOW);
      analogWrite(pwmA, 0);//0-255 for maxspeed
      digitalWrite(dir1B, LOW);
      digitalWrite(dir2B, LOW);
      analogWrite(pwmB, 0);//0-255 for maxspeed

      while (1);
    }
  }
}
