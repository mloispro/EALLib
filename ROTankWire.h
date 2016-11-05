
#ifndef _ROTANKWIRE_h
#define _ROTANKWIRE_h

#include <Arduino.h>
#include <Wire.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include "_globalsROController.h"
//#include "PHSensor.h"
#include "TDSSensorDIY.h"

using namespace Globals;


class ROTankWire {

    private:

        //void Init();
        static String SplitString(String data, char separator, int index);
        static void Transmit(String partialResponse);
    public:
        //WaterSensorWire(PHSensor phSensor, TDSSensor tdsSensor);
        static void Setup();
        static void Loop();
        static void Receive(int bytes);
        static void Request();
        //static void CheckConnection();
        static void Scan();
        static int I2C_ClearBus();
};


#endif
