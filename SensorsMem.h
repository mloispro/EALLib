
#ifndef _SENSORSMEM_H_
#define _SENSORSMEM_H_

#include <Arduino.h>
#include <EEPROM.h>
#include <EEWrap.h>
//#include <PGMWrap.h>
#include <StandardCplusplus.h>
#include <vector>
using namespace std;

namespace Memory {

    struct SensorsMem {
        float_e PhOffset;
        int16_e TdsOffset;
    };
    //struct SensorsPGMem {
    ////int16_p TdsAverage[40];
    //int16_p t;
    //};

    extern SensorsMem& TheSensorsMem;
    //extern SensorsPGMem& TheSensorsPGMem;
}

#endif /* _GLOBALS_H_ */
