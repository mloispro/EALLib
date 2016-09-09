
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


    if(WaterSensor.IsOn()) {
        SerialExt::Print(F("Water Sensor is Detecting High Water"));
        SerialExt::Print(F("Trigger: "), WaterSensor.Max - 50);
        SerialExt::Print(F("Reading: "), WaterSensor.SwitchReading);
        return;// break if overflow detected
    }

    while(TheSwitch.IsOn() && !WaterSensor.IsOn()) {

        delay(500); //keep relay on until float switch is off.
    }

    delay(8000); //keep filling for 8 seconds to ensure enough water to stop float
}
bool ROPump::IsOkToRun() {

    //SerialExt::Debug(F("Relay Pin:"), _pin);
    //SerialExt::Debug(F("Float Pin:"), TheSwitch.AnalogPin);
    //SerialExt::Debug(F("Water Sensor Pin:"), WaterSensor.AnalogPin);

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