// Motor.h

#ifndef _SERVOMOTOR_h
#define _SERVOMOTOR_h

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include <Servo.h>
#include "_globals.h"

#include "SerialExt.h"
#include "RTCExt.h"
//#include "RunScheduleExt.h" <- only needed for non RTC Timer
//#include "PinValMemoryExt.h"

#include "AnalogSwitch.h"

using namespace Globals;
using namespace Utils;
using namespace Models;

//class MotorsContainer {
//private:
//
//public:
////extern vector<Models::NextRunMemory> _nextRunInfos;
//MotorsContainer() {};
//ServoMotor& AddMotor(ServoMotor& motor);
////bool NextRunInfoExists(AccessoryType accType);
//////template<typename T = Globals::AccessoryType>
////NextRunMemory& FindNextRunInfo(AccessoryType accType);
////NextRunMemory& AddNextRunInfo(NextRunMemory& mem);
////void ClearNextRunInfos();
//};
//extern vector<ServoMotor> Motors;

class ServoMotor {
  public:
    Servo TheServo;
    AnalogSwitch TheSwitch;
    short RelayPin;
    AccessoryType ServoType;
  protected:
    int _theSpeed;
  private:
    int _pin;
    int _pos;
  public:
    bool ShouldRunMotor(bool printToSerial);
    int Calibrate();
    //ServoMotor& AddMotor(ServoMotor& motor);
  protected:
    ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType servoType, bool enabled);
    ServoMotor();

    static int GetNumberOfShakes(int potVal);
    void Run();
    static void RunMotorDemos(vector<ServoMotor> motors);
    static void RunMotorDemo(Servo myServo);

  private:

    void Init(int shakes, long runEverySeconds, bool enabled);
    int TranslateSpeed();
    bool ShouldSignalRelay();
    bool IsSwitchOn(bool isTimeToRun);
    void RunServo();
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