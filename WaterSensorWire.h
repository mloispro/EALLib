
#ifndef _WATERSENSORWIRE_h
#define _WATERSENSORWIRE_h

#include <Arduino.h>
#include <Wire.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include "_globalsWaterSensors.h"
#include "PHSensor.h"
#include "TDSSensor.h"

using namespace Globals;

class WaterSensorWire {

    private:

        //void Init();
        static String SplitString(String data, char separator, int index);
    public:
        //WaterSensorWire(PHSensor phSensor, TDSSensor tdsSensor);
        static void Setup();
        static void Receive(int bytes);
        static void Request();
};


#endif
