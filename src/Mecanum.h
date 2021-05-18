#ifndef mecanum_h
#define mecanum_h

#include <Motor.h>

class Mecanum
{
private:
  MOTOR M_FrontLeft,
      M_FrontRight,
      M_RearLeft,
      M_RearRight;

public:
  Mecanum();

  void init(byte M_FrontLeft_Int1, byte M_FrontLeft_Int2,
            byte M_FrontRight_Int1, byte M_FrontRight_Int2,
            byte M_RearLeft_Int1, byte M_RearLeft_Int2,
            byte M_RearRight_Int1, byte M_RearRight_Int2);
  void stop();
  void moveForward();
  void moveBackward();
  void moveLeft();
  void moveRight();
  void moveLeftForward();
  void moveRightForward();
  void moveLeftBackward();
  void moveRightBackward();
  void rotateRight();
  void rotateLeft();
};

#endif
