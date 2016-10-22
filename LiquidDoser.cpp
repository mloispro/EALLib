
#include "LiquidDoser.h"

LiquidDoser::LiquidDoser(short relayPin, AccessoryType accType) :
    Motor(relayPin, 0, 0, relayPin, 0, AnalogSwitch(), accType, true) {

}
LiquidDoser::LiquidDoser() {
    MotorType = AccessoryType::None;
}
void LiquidDoser::handleRun() {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(MotorType);
    long runDurration = mem.RunDurration * 1000;
    delay(runDurration);
}
