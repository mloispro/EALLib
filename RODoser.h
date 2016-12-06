// RODoser.h

#ifndef _RODOSER_h
#define _RODOSER_h

#include <Arduino.h>

//#include "StandardCplusplus.h"
//#include <vector>

//#include "SerialExt.h"
#include "AnalogSwitch.h"
#include "SensorsMem.h"
using namespace Memory;
using namespace Utils;

using namespace std;


class RODoser { // : public ServoMotor {
    private:
        int _pin;
        bool _relayHigh;
        bool _isRunning;
        long _stopTime;
        bool handleRun();
    public:
        RODoser(int pin);
        RODoser();

        bool CheckPin();
        bool ShouldRun(double tdsVal);
        void Run(double tdsVal);
        void Run(double tdsVal, bool force);
        // void SetRelayHigh();
        void Init();
};

#endif

