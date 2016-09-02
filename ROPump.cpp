
#include "ROPump.h"
//RO Pump
//ROPump::ROPump(int pin, AnalogSwitch theSwitch, short waterSensorPin, bool runDurringDayOnly) :
//Motor(pin, 0, 0, pin, 0, theSwitch, AccessoryType::ROWaterPump, true),
//_runDurringDayOnly(runDurringDayOnly), _waterSensorPin(waterSensorPin) {
//
//_waterSensor = AnalogSwitch(waterSensorPin, 350);
//}

ROPump::ROPump(int pin, AnalogSwitch theSwitch, AnalogSwitch waterSensor, bool runDurringDayOnly) :
    Motor(pin, 0, 0, pin, 0, theSwitch, AccessoryType::ROWaterPump, true),
    _runDurringDayOnly(runDurringDayOnly), WaterSensor(waterSensor) {

}

ROPump::ROPump() {
    MotorType = AccessoryType::ROWaterPump;
}
void ROPump::handleRun() {
    //NextRunMemory& mem = RTCExt::RefreshNextRunInfo(MotorType);
    //long runDurration = mem.RunDurration * 1000;
    //delay(runDurration);
    while(TheSwitch.IsOn()) {
        if(WaterSensor.IsOn()) {
            SerialExt::Print(F("Water Sensor is Detecting High Water"));
            SerialExt::Print(F("Max: "), WaterSensor.Max);
            SerialExt::Print(F("Reading: "), WaterSensor.SwitchReading);
            return;// break if overflow detected
        }
        delay(500); //keep relay on until float switch is off.
    }
}
bool ROPump::IsOkToRun() {
    bool isSwitchOn = TheSwitch.IsOn();
    if(!isSwitchOn) {
        return false;
    }
    if(_runDurringDayOnly) {
        bool isDayTime = RTCExt::IsDayTime();
        if(!isDayTime) {
            return false;
        }
    }
    return true;
}