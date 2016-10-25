
#ifndef _AQUACONTROLLERWIRE_h
#define _AQUACONTROLLERWIRE_h

#include <Arduino.h>
#include <Wire.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

//#include "_globalsWaterSensors.h"
//#include "PHSensor.h"
#include "MemoryExt.h"

//using namespace Globals;

struct WireRunInfo {
    String AccType;
    String LastRun;
    String NextRun;
    String CountDown;
    String RunEvery;
    String ShakesOrTurns;
    String LastSave;
    String Enabled;
    String RunDurration;
    String Updated;
    String RunNow;
};

class AquaControllerWire {

    private:


        //void Init();
        static String SplitString(String data, char separator, int index);
        static void Transmit(String partialResponse);
        static void SetCurrentRunInfo();
    public:
        //WaterSensorWire(PHSensor phSensor, TDSSensor tdsSensor);
        static void Setup();
        static void Loop(NextRunMemory& mem, long updated);
        static void Receive(int bytes);
        static void Request();
        static WireRunInfo& GetUpdatedRunInfo();
        //static void CheckConnection();
        static void Scan();
        static int I2C_ClearBus();
};


#endif
