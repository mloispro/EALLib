// Pump.h

#ifndef _PUMP_h
#define _PUMP_h

#include <Arduino.h>

#include "Motor.h"

//#include "StandardCplusplus.h"
#include <vector>

#include "SerialExt.h"
#include "AnalogSwitch.h"
using namespace Utils;

using namespace std;


class Pump : public Motor {
  private:

  public:
    //RO Pump
    Pump(int pin, int turns, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled);
    //Tank water drain pump
    Pump(int pin, int turns, short relayPin, long runEverySeconds, bool enabled);
    Pump();
  protected:
    void handleRun();
};

#endif

