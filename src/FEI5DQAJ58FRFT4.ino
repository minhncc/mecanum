// #include <math.h>
// #include <SPI.h>
// #include <printf.h>
// #include <RF24.h>

// #define ANALOG_SPEED 1      //1 for Analog Speed; 0 for Full Speed
// #define MIN_MOTOR_SPD 100   //Minium Speed(PWM) for motors
// #define MAX_MOTOR_SPD 255   //Maximum Speed(PWM) for motors

// #if 1
//   #define DEBUG_P(...) Serial.print(__VA_ARGS__)
//   #define DEBUG_PLN(...) Serial.println(__VA_ARGS__)
// #else
//   #define DEBUG_P(...)
//   #define DEBUG_PLN(...)
// #endif

// #define  CE_PIN  A0   // The pins to be used for CE and SN
// #define  CSN_PIN 10

// RF24 RF_Mecan (CE_PIN,CSN_PIN);                    //create RF24 object called transmit
// byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

// struct dataStruct {
//   unsigned long _micros;  // to save response times
//   int Xposition;          // The Joystick position values
//   int Yposition;
//   bool switch0;           // The Joystick push-down switch
//   bool switch1;           // Rotate Left
//   bool switch2;           // Rotate Right
// } myData;

// #define M_STOP      0
// #define M_FORWARD   1
// #define M_BACKWARD  2

// #define CMD_Stop              0
// #define CMD_moveForward       1
// #define CMD_moveBackward      2
// #define CMD_moveLeft          3
// #define CMD_moveRight         4
// #define CMD_moveLeftForward   5
// #define CMD_moveRightForward  6
// #define CMD_moveLeftBackward  7
// #define CMD_moveRightBackward 8
// #define CMD_rotateLeft        9
// #define CMD_rotateRight       10

// #define CMD_TIMEOUT_MS  1000

// byte curr_cmd = CMD_Stop, last_cmd = CMD_Stop, curr_spd = 255, last_spd = 255;
// int cmd_last_update = 0, timeout_cnt = 0;

// typedef enum{
//   E_Center = 0,
//   E_Up,
//   E_Down,
//   E_Left,
//   E_Right,
//   E_UpLeft,
//   E_UpRight,
//   E_DownLeft,
//   E_DownRight
// } J_DIR;

// J_DIR joystickDIR;
// #define JOYSTICK_CENTER_X 512       //ADC reading when X is centered
// #define JOYSTICK_CENTER_Y 512       //ADC reading when Y is centered
// #define JOYSTICK_CENTER_ADC_TOL 100 //ADC reading tolerance for center detection

// #define JOYSTICK_MAX_RADIUS  sqrt(2*pow(JOYSTICK_CENTER_X,2))         //Max Radius
// #define JOYSTICK_MIN_RADIUS  sqrt(2*pow(JOYSTICK_CENTER_ADC_TOL,2))   //Min Radius

// class MOTOR {
//   private:
//     byte IN1, IN2, EN;
//   public:
//     MOTOR(byte in1, byte in2, byte en);
//     void set_speed(byte en, byte spd);
// };

// MOTOR::MOTOR(byte in1, byte in2, byte en) {
//   IN1 = in1;
//   IN2 = in2;
//   EN = en;
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(EN, OUTPUT);
// }

// void MOTOR::set_speed (byte dir, byte spd) {
//   if(spd<0||spd>255) return;
//   switch(dir)
//   {
//     case M_FORWARD:
//       digitalWrite(IN1, HIGH);
//       digitalWrite(IN2, LOW);
//       break;
//     case M_BACKWARD:
//       digitalWrite(IN1, LOW);
//       digitalWrite(IN2, HIGH);
//       break;
//    case M_STOP:
//    default:
//       digitalWrite(IN1, LOW);
//       digitalWrite(IN2, LOW);
//       break;
//   }
//   analogWrite(EN,spd);
// }

// MOTOR M_FrontLeft(2, 7, 3),     //Setup the Pins for four motors
//       M_FrontRight(8, 4, 5),
//       M_RearLeft(A4, A3, 9),
//       M_RearRight(A2, A1, 6);

// void(* resetFunc) (void) = 0; //declare reset function @ address 0

// void setup() {
//   Serial.begin(115200);
//   printf_begin(); // Needed for "printDetails" Takes up some memory
//   RF_Mecan.begin();          // Initialize the nRF24L01 Radio
//   RF_Mecan.setChannel(108);  // 2.508 Ghz - Above most Wifi Channels
//   RF_Mecan.setDataRate(RF24_250KBPS); // Fast enough.. Better range
//   RF_Mecan.setPALevel(RF24_PA_MIN);
//   RF_Mecan.openWritingPipe(addresses[1]);
//   RF_Mecan.openReadingPipe(1, addresses[0]);
//   RF_Mecan.printDetails(); //Uncomment to show LOTS of debugging information
//   RF_Mecan.startListening();
//   Stop();
//   delay(500);
//   if(!RF_Mecan.isChipConnected())
//     resetFunc();
//   DEBUG_PLN(F("Start"));

// }

// void loop() {
//   int now = millis();
//   if (RF_Mecan.available())
//   {
//     timeout_cnt = now;
//     while (RF_Mecan.available())   // While there is data ready to be retrieved from the receive pipe
//     {
//       RF_Mecan.read( &myData, sizeof(myData) );             // Get the data
//     }
//     RF_Mecan.stopListening();                               // First, stop listening so we can transmit
//     RF_Mecan.write( &myData, sizeof(myData) );              // Send the received data back.
//     RF_Mecan.startListening();                              // Now, resume listening so we catch the next packets.

//     DEBUG_P(F("Packet Received - Sent response "));  // Print the received packet data
//     DEBUG_P(myData._micros);
//     DEBUG_P(F("uS X= "));
//     DEBUG_P(myData.Xposition);
//     DEBUG_P(F(" Y= "));
//     DEBUG_P(myData.Yposition);
//     if ( myData.switch0 == 1)
//       DEBUG_P(F(" Switch0 ON"));
//     else
//       DEBUG_P(F(" Switch0 OFF"));
//     if ( myData.switch1 == 1)
//       DEBUG_P(F(" Switch1 ON"));
//     else
//       DEBUG_P(F(" Switch1 OFF"));
//     if ( myData.switch2 == 1)
//       DEBUG_PLN(F(" Switch2 ON"));
//     else
//       DEBUG_PLN(F(" Switch2 OFF"));
//     joystickDIR = xyToDir(myData.Xposition,myData.Yposition);
//     if(joystickDIR==E_Center)
//     {
//       if(myData.switch1 == 1 && myData.switch2 != 1)
//       {
//         curr_cmd = CMD_rotateLeft;
//         curr_spd = MAX_MOTOR_SPD;
//       }
//       else if(myData.switch2 == 1 && myData.switch1 != 1)
//       {
//         curr_cmd = CMD_rotateRight;
//         curr_spd = MAX_MOTOR_SPD;
//       }
//       else
//         curr_cmd = CMD_Stop;
//     }
//     else
//       curr_cmd = joystickDIR;
//   }
//   else if(now-timeout_cnt>CMD_TIMEOUT_MS) //If nothing is received after CMD_TIMEOUT_MS, set CMD to CMD_Stop
//   {
//     DEBUG_PLN(F("Timeout"));
//     timeout_cnt = now;
//     curr_cmd = CMD_Stop;
//     Stop();
//     resetFunc();  //call reset
//   }
//   if(!RF_Mecan.isChipConnected())
//   {
//     curr_cmd = CMD_Stop;
//     Stop();
//     resetFunc();
//   }
//   cmdHandle();
// }

// J_DIR xyToDir(int xo, int yo) {   //Translate XY coordinate to Joystick Driection
//   long radius;
//   float angle;
//   long x = xo - JOYSTICK_CENTER_X;
//   long y = yo - JOYSTICK_CENTER_Y;
//   x = 0-x;
//   if(x == 0 && y == 0 ){
//     radius = 0;
//     angle = 0;
//   }
//   else
//   {
//     radius = sqrt(y*y+x*x);
//     angle = atan2(y,x)*180/PI;
//   }
//   if(angle<0) angle+=360;
//   DEBUG_P("x:");
//   DEBUG_P(x);
//   DEBUG_P(", y:");
//   DEBUG_PLN(y);
//   DEBUG_P("angle:");
//   DEBUG_P(angle);
//   DEBUG_P(", r:");
//   DEBUG_PLN(radius);
//   if(radius<sqrt(2*pow(JOYSTICK_CENTER_ADC_TOL,2))) return E_Center;
//   if(ANALOG_SPEED)
//   {
//     curr_spd = map(radius,JOYSTICK_MIN_RADIUS,JOYSTICK_MAX_RADIUS,MIN_MOTOR_SPD,255);
//     DEBUG_P("spd:");
//     DEBUG_PLN(curr_spd);
//   }
//   if(angle<0+22.5||angle>=360-22.5)
//     return E_Right;
//   if(angle<45+22.5)
//     return E_UpRight;
//   if(angle<90+22.5)
//     return E_Up;
//   if(angle<135+22.5)
//     return E_UpLeft;
//   if(angle<180+22.5)
//     return E_Left;
//   if(angle<225+22.5)
//     return E_DownLeft;
//   if(angle<270+22.5)
//     return E_Down;
//   if(angle<315+22.5)
//     return E_DownRight;
// }

// void cmdHandle() {
//   if(curr_cmd==last_cmd && curr_spd==last_spd) return;
//   switch(curr_cmd)
//   {
//     case CMD_Stop:
//       Stop();
//       DEBUG_PLN("Stop");
//       break;
//     case CMD_moveForward:
//       moveForward(curr_spd);
//       DEBUG_PLN("moveForward");
//       break;
//     case CMD_moveBackward:
//       moveBackward(curr_spd);
//       DEBUG_PLN("moveBackward");
//       break;
//     case CMD_moveLeft:
//       moveLeft(curr_spd);
//       DEBUG_PLN("moveLeft");
//       break;
//     case CMD_moveRight:
//       moveRight(curr_spd);
//       DEBUG_PLN("moveRight");
//       break;
//     case CMD_moveLeftForward:
//       moveLeftForward(curr_spd);
//       DEBUG_PLN("moveLeftForward");
//       break;
//     case CMD_moveRightForward:
//       moveRightForward(curr_spd);
//       DEBUG_PLN("moveRightForward");
//       break;
//     case CMD_moveLeftBackward:
//       moveLeftBackward(curr_spd);
//       DEBUG_PLN("moveLeftBackward");
//       break;
//     case CMD_moveRightBackward:
//       moveRightBackward(curr_spd);
//       DEBUG_PLN("moveRightBackward");
//       break;
//     case CMD_rotateLeft:
//       rotateLeft(curr_spd);
//       DEBUG_PLN("rotateLeft");
//       break;
//     case CMD_rotateRight:
//       rotateRight(curr_spd);
//       DEBUG_PLN("rotateRight");
//       break;
//   }
//   last_cmd = curr_cmd;
//   last_spd = curr_spd;
// }

// void Stop() {
//   M_FrontLeft.set_speed(M_STOP,0);
//   M_FrontRight.set_speed(M_STOP,0);
//   M_RearLeft.set_speed(M_STOP,0);
//   M_RearRight.set_speed(M_STOP,0);
// }
// void moveForward(byte spd) {
//   M_FrontLeft.set_speed(M_FORWARD,spd);
//   M_FrontRight.set_speed(M_FORWARD,spd);
//   M_RearLeft.set_speed(M_FORWARD,spd);
//   M_RearRight.set_speed(M_FORWARD,spd);
// }
// void moveBackward(byte spd) {
//   M_FrontLeft.set_speed(M_BACKWARD,spd);
//   M_FrontRight.set_speed(M_BACKWARD,spd);
//   M_RearLeft.set_speed(M_BACKWARD,spd);
//   M_RearRight.set_speed(M_BACKWARD,spd);
// }
// void moveLeft(byte spd) {
//   M_FrontLeft.set_speed(M_BACKWARD,spd);
//   M_FrontRight.set_speed(M_FORWARD,spd);
//   M_RearLeft.set_speed(M_FORWARD,spd);
//   M_RearRight.set_speed(M_BACKWARD,spd);
// }
// void moveRight(byte spd) {
//   M_FrontLeft.set_speed(M_FORWARD,spd);
//   M_FrontRight.set_speed(M_BACKWARD,spd);
//   M_RearLeft.set_speed(M_BACKWARD,spd);
//   M_RearRight.set_speed(M_FORWARD,spd);
// }
// void moveLeftForward(byte spd) {
//   M_FrontLeft.set_speed(M_STOP,0);
//   M_FrontRight.set_speed(M_FORWARD,spd);
//   M_RearLeft.set_speed(M_FORWARD,spd);
//   M_RearRight.set_speed(M_STOP,0);
// }
// void moveRightForward(byte spd) {
//   M_FrontLeft.set_speed(M_FORWARD,spd);
//   M_FrontRight.set_speed(M_STOP,0);
//   M_RearLeft.set_speed(M_STOP,0);
//   M_RearRight.set_speed(M_FORWARD,spd);
// }
// void moveLeftBackward(byte spd) {
//   M_FrontLeft.set_speed(M_BACKWARD,spd);
//   M_FrontRight.set_speed(M_STOP,0);
//   M_RearLeft.set_speed(M_STOP,0);
//   M_RearRight.set_speed(M_BACKWARD,spd);
// }
// void moveRightBackward(byte spd) {
//   M_FrontLeft.set_speed(M_STOP,0);
//   M_FrontRight.set_speed(M_BACKWARD,spd);
//   M_RearLeft.set_speed(M_BACKWARD,spd);
//   M_RearRight.set_speed(M_STOP,0);
// }
// void rotateLeft(byte spd) {
//   M_FrontLeft.set_speed(M_BACKWARD,spd);
//   M_FrontRight.set_speed(M_FORWARD,spd);
//   M_RearLeft.set_speed(M_BACKWARD,spd);
//   M_RearRight.set_speed(M_FORWARD,spd);
// }
// void rotateRight(byte spd) {
//   M_FrontLeft.set_speed(M_FORWARD,spd);
//   M_FrontRight.set_speed(M_BACKWARD,spd);
//   M_RearLeft.set_speed(M_FORWARD,spd);
//   M_RearRight.set_speed(M_BACKWARD,spd);
// }

