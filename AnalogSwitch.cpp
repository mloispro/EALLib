
#include "AnalogSwitch.h"

using namespace Models;

AnalogSwitch::AnalogSwitch(short analogPin, int max) :
    AnalogPin(analogPin), Max(max) {
    Init();
}

AnalogSwitch::AnalogSwitch(short analogPin) :
    AnalogPin(analogPin) {
    Init();
}
AnalogSwitch::AnalogSwitch() {}

void AnalogSwitch::Init() {
    if(AnalogPin >= 1) {
        pinMode(AnalogPin, INPUT);    //receive switch signal
    }
}

bool AnalogSwitch::IsOn() {
    //read switch
    int switchReading = analogRead(AnalogPin);
    SwitchReading = switchReading;

    SerialExt::Debug(F("Sensor Reading"), SwitchReading);
    SerialExt::Debug(F("Sensor On at"), Max - 50);
    if(SwitchReading > Max - 50) {
        return true;
    }
    return false;
}

