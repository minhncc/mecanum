#include <Mecanum.h>
#include <Motor.h>

#define M_STOP 0
#define M_FORWARD 1
#define M_BACKWARD 2

Mecanum::Mecanum() {};

void Mecanum::init(byte M_FrontLeft_Int1, byte M_FrontLeft_Int2,
                   byte M_FrontRight_Int1, byte M_FrontRight_Int2,
                   byte M_RearLeft_Int1, byte M_RearLeft_Int2,
                   byte M_RearRight_Int1, byte M_RearRight_Int2) {
  M_FrontLeft.attach(M_FrontLeft_Int1, M_FrontLeft_Int2);
  M_FrontRight.attach(M_FrontRight_Int1, M_FrontRight_Int2);
  M_RearLeft.attach(M_RearLeft_Int1, M_RearLeft_Int2);
  M_RearRight.attach(M_RearRight_Int1, M_RearRight_Int2);
}

void Mecanum::stop()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_STOP);
}
void Mecanum::moveForward()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void Mecanum::moveBackward()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_BACKWARD);
}
void Mecanum::moveLeft()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_BACKWARD);
}
void Mecanum::moveRight()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void Mecanum::moveLeftForward()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_STOP);
}
void Mecanum::moveRightForward()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_FORWARD);
}
void Mecanum::moveLeftBackward()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_BACKWARD);
}
void Mecanum::moveRightBackward()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_STOP);
}
void Mecanum::rotateLeft()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void Mecanum::rotateRight()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_BACKWARD);
}