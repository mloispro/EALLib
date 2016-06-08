
#include "Pump.h"

Pump::Pump(int pin, int turns, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    Motor(pin, turns, 10, relayPin, runEverySeconds, theSwitch, AccessoryType::WaterPump, enabled) {
}

Pump::Pump() {
    MotorType = AccessoryType::WaterPump;
    //_theSpeed = 10;
}
void Pump::handleRun() {
    //todo: need to implement
    delay(3000);
}