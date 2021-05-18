#include <Motor.h>

#define M_STOP 0
#define M_FORWARD 1
#define M_BACKWARD 2

MOTOR::MOTOR() {};

void MOTOR::attach(byte  in1, byte in2) {
  IN1 = in1;
  IN2 = in2;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void MOTOR::set_speed(byte dir)
{
  switch (dir)
  {
  case M_FORWARD:
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    break;
  case M_BACKWARD:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    break;
  case M_STOP:
  default:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    break;
  }
}