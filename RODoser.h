// RODoser.h

#ifndef _RODOSER_h
#define _RODOSER_h

#include <Arduino.h>

#include "Servo.h"
#include "ServoMotor.h"

//#include "StandardCplusplus.h"
#include <vector>

#include "SerialExt.h"
#include "AnalogSwitch.h"
using namespace Utils;

using namespace std;


class RODoser : public ServoMotor {
  private:

  public:
    RODoser(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled);
    RODoser(Servo servo, int pin, int shakes, long runEverySeconds, AnalogSwitch theSwitch, bool enabled);
    RODoser();
    static void RunDemo(vector<RODoser> dosers);
    void Dose();
};

//vector<RODoser> RODoser::Feeders;

//extern RODoserClass RODoser;

#endif

