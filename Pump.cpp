
#include "Pump.h"

//Tank water drain pump
Pump::Pump(int pin, int turns, short relayPin, long runEverySeconds, bool enabled) :
    Motor(pin, turns, 10, relayPin, runEverySeconds, AnalogSwitch(), AccessoryType::WaterPump, enabled) {
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