
#ifndef _SKETCHEXTROCONTROLLER_H_
#define _SKETCHEXTROCONTROLLER_H_

#include <Arduino.h>
#include <EEPROM.h>
#include <EEWrap.h>
#include <StandardCplusplus.h>
#include <vector>
using namespace std;

#include "_globalsROController.h"
#include "ROTankWire.h"
#include "LCDBase.h"
//#include "PhSensor.h"
#include "TDSSensorDIY.h"

namespace Sketch {


    //extern void SwitchSensors();
    extern void Setup();
    extern void Loop();
    extern void AsyncDoWork();


}

#endif /* _GLOBALS_H_ */
