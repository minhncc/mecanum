#include <Arduino.h>

#if 1
#define DEBUG_P(...) Serial.print(__VA_ARGS__)
#define DEBUG_PLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_P(...)
#define DEBUG_PLN(...)
#endif

#define M_STOP 0
#define M_FORWARD 1
#define M_BACKWARD 2

#define CMD_Stop 0
#define CMD_moveForward 1
#define CMD_moveBackward 2
#define CMD_moveLeft 3
#define CMD_moveRight 4
#define CMD_moveLeftForward 5
#define CMD_moveRightForward 6
#define CMD_moveLeftBackward 7
#define CMD_moveRightBackward 8
#define CMD_rotateLeft 9
#define CMD_rotateRight 10

byte curr_cmd = CMD_Stop, last_cmd = CMD_Stop;
int cmd_last_update = 0, timeout_cnt = 0;

class MOTOR
{
private:
  byte IN1, IN2;

public:
  MOTOR(byte in1, byte in2);
  void set_speed(byte en);
};

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

MOTOR::MOTOR(byte in1, byte in2)
{
  IN1 = in1;
  IN2 = in2;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

MOTOR M_FrontLeft(2, 3), //Setup the Pins for four motors
    M_FrontRight(4, 5),
    M_RearLeft(5, 7),
    M_RearRight(8, 9);

void Stop()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_STOP);
}
void moveForward()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void moveBackward()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_BACKWARD);
}
void moveLeft()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_BACKWARD);
}
void moveRight()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void moveLeftForward()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_STOP);
}
void moveRightForward()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_FORWARD);
}
void moveLeftBackward()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_STOP);
  M_RearLeft.set_speed(M_STOP);
  M_RearRight.set_speed(M_BACKWARD);
}
void moveRightBackward()
{
  M_FrontLeft.set_speed(M_STOP);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_STOP);
}
void rotateLeft()
{
  M_FrontLeft.set_speed(M_BACKWARD);
  M_FrontRight.set_speed(M_FORWARD);
  M_RearLeft.set_speed(M_BACKWARD);
  M_RearRight.set_speed(M_FORWARD);
}
void rotateRight()
{
  M_FrontLeft.set_speed(M_FORWARD);
  M_FrontRight.set_speed(M_BACKWARD);
  M_RearLeft.set_speed(M_FORWARD);
  M_RearRight.set_speed(M_BACKWARD);
}

void cmdHandle()
{
  if (curr_cmd == last_cmd)
    return;

  switch (curr_cmd)
  {
  case CMD_Stop:
    Stop();
    DEBUG_PLN("Stop");
    break;
  case CMD_moveForward:
    moveForward();
    DEBUG_PLN("moveForward");
    break;
  case CMD_moveBackward:
    moveBackward();
    DEBUG_PLN("moveBackward");
    break;
  case CMD_moveLeft:
    moveLeft();
    DEBUG_PLN("moveLeft");
    break;
  case CMD_moveRight:
    moveRight();
    DEBUG_PLN("moveRight");
    break;
  case CMD_moveLeftForward:
    moveLeftForward();
    DEBUG_PLN("moveLeftForward");
    break;
  case CMD_moveRightForward:
    moveRightForward();
    DEBUG_PLN("moveRightForward");
    break;
  case CMD_moveLeftBackward:
    moveLeftBackward();
    DEBUG_PLN("moveLeftBackward");
    break;
  case CMD_moveRightBackward:
    moveRightBackward();
    DEBUG_PLN("moveRightBackward");
    break;
  case CMD_rotateLeft:
    rotateLeft();
    DEBUG_PLN("rotateLeft");
    break;
  case CMD_rotateRight:
    rotateRight();
    DEBUG_PLN("rotateRight");
    break;
  }
  last_cmd = curr_cmd;
}

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:

  Stop();
  delay(2000);

  moveForward();
  delay(2000);

  moveBackward();
  delay(2000);

  moveLeft();
  delay(2000);

  moveRight();
  delay(2000);

  moveLeftForward();
  delay(2000);

  moveRightForward();
  delay(2000);

  moveLeftBackward();
  delay(2000);

  moveRightBackward();
  delay(2000);

  rotateLeft();
  delay(2000);

  rotateRight();
  delay(2000);
}
