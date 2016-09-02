
#include "Motor.h"


Motor::Motor(int pin, int shakesOrTurns, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType motorType, bool enabled) :
    TheSwitch(theSwitch), RelayPin(relayPin), _theSpeed(theSpeed), _pin(pin), MotorType(motorType) {

    Init(shakesOrTurns, runEverySeconds, enabled);
}
Motor::Motor() {}


void Motor::Init(int shakesOrTurns, long runEverySeconds, bool enabled) {

    if(RelayPin >= 2) {
        pinMode(RelayPin, OUTPUT);
        digitalWrite(RelayPin, HIGH);
    }

    if(MotorType == AccessoryType::ROWaterPump) {
        return; //dont need to save to eeprom because triggered by only float switch
    }

    RTCExt::LoadNextRunInfos(MotorType);
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(MotorType);
    SerialExt::Print("Init Pin: ", _pin);
    if(mem.LastSave <= 0) {
        mem = RTCExt::SaveNextRunInfos(MotorType);

        mem.Enabled = enabled;
        //mem.Pin = _pin;
        mem.AccType = MotorType;
        mem.ShakesOrTurns = shakesOrTurns;
        mem.RunEvery = runEverySeconds;
        mem.RunDurration = 0;
        RTCExt::RefreshNextRunInfo(MotorType, true);
        //RTCExt::SetShakesOrTurns(shakes, ServoType);
        //RTCExt::SetRunEvery(runEverySeconds, ServoType);
    }

}

//void Motor::RunMotor() {
////hopfully called in child class
//}

void Motor::Run() {
    bool signalRelay = ShouldSignalRelay();

    if(signalRelay) {
        SerialExt::Print(F("Signaling Relay Pin: "), RelayPin);
        digitalWrite(RelayPin, LOW);
    }

    handleRun();

    if(signalRelay) {
        digitalWrite(RelayPin, HIGH);
    }

    if(MotorType == AccessoryType::ROWaterPump) {
        return; //dont need to save to eeprom because triggered by only float switch
    }

    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(MotorType);

    if(mem.RunEvery > 0) {
        mem.LastRun = RTCExt::GetRTCTime(); //using rtc
        RTCExt::RefreshNextRunInfo(MotorType, true);
    }
}

bool Motor::ShouldSignalRelay() {
    if(RelayPin >= 2) {
        return true;
    }
    return false;
}


bool Motor::ShouldRunMotor(bool printToSerial) {

    bool runMotor;
    bool isTimeToRun = RTCExt::IsTimeToRun(MotorType);

    bool isSwitchOn = IsSwitchOnAndTimeToRun(isTimeToRun);

    runMotor = (isTimeToRun) && (isSwitchOn);
    return runMotor;
}
//analog pin must be greater than 1 because of lcd
bool Motor::IsSwitchOnAndTimeToRun(bool isTimeToRun) {
    bool isSwitchOn = true;
    //see if this motor has a switch
    int switchPin = TheSwitch.AnalogPin;
    if(switchPin >= 1) {

        if(isTimeToRun) {
            isSwitchOn = TheSwitch.IsOn();
        }

        if(isSwitchOn) {
            SerialExt::Debug("Switch Val: ", TheSwitch.SwitchReading);
        }
    }
    else {
        isSwitchOn = true; //no switch to turn it on.
    }
    return isSwitchOn;
}

