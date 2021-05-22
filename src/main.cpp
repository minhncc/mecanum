#include <Arduino.h>
#include <Mecanum.h>

#if 1
#define DEBUG_P(...) Serial.print(__VA_ARGS__)
#define DEBUG_PLN(...) Serial.println(__VA_ARGS__)
#else
#define DEBUG_P(...)
#define DEBUG_PLN(...)
#endif

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

Mecanum vehicle;

void cmdHandle()
{
  if (curr_cmd == last_cmd)
    return;

  switch (curr_cmd)
  {
  case CMD_Stop:
    vehicle.stop();
    // DEBUG_PLN("Stop");
    break;
  case CMD_moveForward:
    vehicle.moveForward();
    // DEBUG_PLN("moveForward");
    break;
  case CMD_moveBackward:
    vehicle.moveBackward();
    // DEBUG_PLN("moveBackward");
    break;
  case CMD_moveLeft:
    vehicle.moveLeft();
    // DEBUG_PLN("moveLeft");
    break;
  case CMD_moveRight:
    vehicle.moveRight();
    // DEBUG_PLN("moveRight");
    break;
  case CMD_moveLeftForward:
    vehicle.moveLeftForward();
    // DEBUG_PLN("moveLeftForward");
    break;
  case CMD_moveRightForward:
    vehicle.moveRightForward();
    // DEBUG_PLN("moveRightForward");
    break;
  case CMD_moveLeftBackward:
    vehicle.moveLeftBackward();
    // DEBUG_PLN("moveLeftBackward");
    break;
  case CMD_moveRightBackward:
    vehicle.moveRightBackward();
    // DEBUG_PLN("moveRightBackward");
    break;
  case CMD_rotateLeft:
    vehicle.rotateLeft();
    // DEBUG_PLN("rotateLeft");
    break;
  case CMD_rotateRight:
    vehicle.rotateRight();
    // DEBUG_PLN("rotateRight");
    break;
  }

  last_cmd = curr_cmd;
}

void setup()
{
  Serial.begin(9600);
  vehicle.init(2, 3, 4, 5, 6, 7, 8, 9);
}

void loop()
{
  if (Serial.available()) {
    curr_cmd = Serial.parseInt();
    // DEBUG_P("curr_cmd:");
    // DEBUG_PLN(curr_cmd);
  }

  cmdHandle();

/* Test montor directions
  M_FrontLeft.set_speed(M_FORWARD);
  delay(2000);
  M_FrontLeft.set_speed(M_STOP);

  M_FrontRight.set_speed(M_FORWARD);
  delay(2000);
  M_FrontRight.set_speed(M_STOP);

  M_RearLeft.set_speed(M_FORWARD);
  delay(2000);
  M_RearLeft.set_speed(M_STOP);

  M_RearRight.set_speed(M_FORWARD);
  delay(2000);
  M_RearRight.set_speed(M_STOP);
 */
/* Test all movements
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
 */
}
