
#include "SensorsMem.h"

namespace Memory {

    static SensorsMem _sensorsMem EEMEM;
    //const SensorsPGMem _sensorsPGMem PROGMEM = {{1}};

    SensorsMem& TheSensorsMem = _sensorsMem;
    //SensorsPGMem& TheSensorsPGMem = _sensorsPGMem;

    //int16_p TdsAverage[2] PROGMEM = {0, 0};
}

