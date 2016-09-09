// Motor.h

#ifndef _MOTOR_h
#define _MOTOR_h

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include "_globals.h"

#include "SerialExt.h"
#include "RTCExt.h"

#include "AnalogSwitch.h"

using namespace Globals;
using namespace Utils;
using namespace Models;


class Motor {
    public:
        AnalogSwitch TheSwitch;
        short RelayPin;
        AccessoryType MotorType;

    protected:
        int _theSpeed;
        int _pin;
        bool _relayHigh;
    private:

    public:
        bool ShouldRunMotor(bool printToSerial);
        void Run();
        void SetRelayHigh();
    protected:
        Motor(int pin, int shakesOrTurns, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType motorType, bool enabled);
        Motor();
        virtual void handleRun() {};

    private:

        void Init(int shakesOrTurns, long runEverySeconds, bool enabled);
        bool ShouldSignalRelay();
        bool IsSwitchOnAndTimeToRun(bool isTimeToRun);

};

#endif
