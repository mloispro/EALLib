
#ifndef _LIQUIDDOSER_h
#define _LIQUIDDOSER_h

#include <Arduino.h>
#include "Motor.h"

//#include "StandardCplusplus.h"
#include <vector>

#include "SerialExt.h"
#include "AnalogSwitch.h"
using namespace Utils;

using namespace std;


//class LiquidDoserStorage : public erom::Storage {
//protected:
//// Define rules for loading storage into RAM
//virtual void OnLoad() {
//RunDurationInSecs.load();
//
//}
//// Define rules for saving storage into EEPROM
//virtual void OnSave() {
//RunDurationInSecs.save();
//
//}
//
//public:
//// Storage data/variables
//erom::Entry<int> RunDurationInSecs;
//
//// Binding/allocating variable to EEPROM memory addresses
//LiquidDoserStorage() {
//issue(RunDurationInSecs);
//}
//};

class LiquidDoser : public Motor {
    private:

    public:
        //Tank water drain pump
        LiquidDoser(short relayPin, AccessoryType accType);
        LiquidDoser();
        // void SetRunDurration(int secs);
    protected:
        void handleRun();
};

#endif

