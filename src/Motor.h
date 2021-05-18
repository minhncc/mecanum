#ifndef motor_h
#define motor_h

#include <Arduino.h>

class MOTOR
{
private:
  byte IN1, IN2;

public:
  MOTOR();
  void attach(byte in1, byte in2);
  void set_speed(byte en);
};

#endif
