// Motor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include <Servo.h>
#include "_globals.h"

#include "Motor.h"
#include "SerialExt.h"
#include "RTCExt.h"

#include "AnalogSwitch.h"

using namespace Globals;
using namespace Utils;
using namespace Models;

class ServoMotor : public Motor {
  public:
    Servo TheServo;
  protected:
    int _theSpeed;
  private:
    int _pos;
  public:
    //bool ShouldRunMotor(bool printToSerial);
    int Calibrate();

  protected:
    ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType servoType, bool enabled);
    ServoMotor();

    static int GetNumberOfShakes(int potVal);
    void handleRun();
    static void RunMotorDemos(vector<ServoMotor> motors);
    static void RunMotorDemo(Servo myServo);

  private:

    void Init();
    int TranslateSpeed();

};
//extern vector<ServoMotor> Motors;

#endif

#pragma region OLD_STUFF
/*ServoMotor(Servo servo, int pin, int shakes, long runEverySeconds);
ServoMotor(Servo servo, int pin, int shakes, short relayPin);
ServoMotor(Servo servo, int pin, int shakes);
ServoMotor(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds);
ServoMotor(Servo servo, int pin, int shakes, long runEverySeconds, AnalogSwitch theSwitch);
ServoMotor(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, AnalogSwitch theSwitch);

ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed);
ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin);
ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin, long runEverySeconds);*/

//void PrintSerialInstructions();
//bool ProcessSerialInput(int incomingNum);

//3-6 = 6 shakes, returns true if could process successfully
// static bool ProcessSerialInput(int incomingNum, vector<ServoMotor> motors);
//1 to run, 2 to run demo
//static bool ShouldRunMotorBySerialInput(int incomingByte);
//static bool ShouldRunMotorDemo(int incomingByte);
#pragma endregion OLD_STUFF