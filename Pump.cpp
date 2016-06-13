
#include "Pump.h"

Pump::Pump(int pin, int turns, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    Motor(pin, turns, 10, relayPin, runEverySeconds, theSwitch, AccessoryType::WaterPump, enabled) {
}

Pump::Pump() {
    MotorType = AccessoryType::WaterPump;
    //_theSpeed = 10;
}
void Pump::handleRun() {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(MotorType);
    long runDurration = mem.RunDurration * 1000;
    delay(runDurration);
}