
#ifndef _ROPUMP_h
#define _ROPUMP_h

#include <Arduino.h>

#include "Motor.h"

//#include "StandardCplusplus.h"
#include <vector>

#include "SerialExt.h"
#include "AnalogSwitch.h"
using namespace Utils;

using namespace std;


class ROPump : public Motor {
    private:
        bool _runDurringDayOnly;
        //int _waterSensorPin;

    public:
        AnalogSwitch WaterSensor;
        //RO Pump
        ROPump(int pin, AnalogSwitch theSwitch, AnalogSwitch waterSensor, bool runDurringDayOnly);
        ROPump();
        bool IsOkToRun();
    protected:
        void handleRun();
};

#endif

