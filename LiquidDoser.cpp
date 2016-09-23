
#include "LiquidDoser.h"


//Tank water drain pump
LiquidDoser::LiquidDoser(short relayPin, int runDurationInSecs) :
    Motor(relayPin, 0, 0, relayPin, 0, AnalogSwitch(), AccessoryType::LiqDoser, true),
    _runDurationInSecs(runDurationInSecs) {
    Init();
}
LiquidDoser::LiquidDoser() {
    MotorType = AccessoryType::LiqDoser;
    Init();
}
void LiquidDoser::Init() {
    issue(RunDurationInSecs);
    RunDurationInSecs.load();
    if(RunDurationInSecs > 900) {
        RunDurationInSecs = _runDurationInSecs;
        RunDurationInSecs.save(true);
    }
}
void LiquidDoser::SetRunDurration(int secs) {
    RunDurationInSecs = secs;
    RunDurationInSecs.save();
}
void LiquidDoser::handleRun() {
    int dur = RunDurationInSecs; //todo: delete this
    delay(RunDurationInSecs * 1000);
}