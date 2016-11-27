
#include "ROSensorsMem.h"

namespace Memory {

    static ROSensorsMem _sensorsMem EEMEM;
    //const SensorsPGMem _sensorsPGMem PROGMEM = {{1}};

    ROSensorsMem& TheSensorsMem = _sensorsMem;
    //SensorsPGMem& TheSensorsPGMem = _sensorsPGMem;

    //int16_p TdsAverage[2] PROGMEM = {0, 0};
}

