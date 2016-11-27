
#ifndef _ROSENSORSMEM_H_
#define _ROSENSORSMEM_H_

#include <Arduino.h>
#include <EEPROM.h>
#include <EEWrap.h>
//#include <PGMWrap.h>
#include <StandardCplusplus.h>
#include <vector>
using namespace std;

namespace Memory {

    struct ROSensorsMem {
        float_e Ph_Offset;
        float_e Tds_Offset;
        //float_e Ph_Val;
        //float_e Tds_Val; //not saving this to save of eeprom wear.
        int16_e Ph_AvgArr[30];
        //int16_e Tds_AvgArr[10];
        float_e Tds_volts;
        int32_e LastDoseTime;
        float_e Tds_minVal;
        int16_e DoseDurrationInSecs;
    };

    extern ROSensorsMem& TheSensorsMem;
    //extern SensorsPGMem& TheSensorsPGMem;
}

#endif /* _GLOBALS_H_ */
