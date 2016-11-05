
#include "Motor.h"


Motor::Motor(int pin, int shakesOrTurns, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType motorType, bool enabled) :
    TheSwitch(theSwitch), RelayPin(relayPin), _theSpeed(theSpeed), _pin(pin), MotorType(motorType) {

    Init(shakesOrTurns, runEverySeconds, enabled);
}

Motor::Motor() {}


void Motor::Init(int shakesOrTurns, long runEverySeconds, bool enabled) {

    if(RelayPin >= 2) {


#ifdef DEBUG
        digitalWrite(RelayPin, LOW);
#else
        digitalWrite(RelayPin, !_relayHigh);
#endif
        //relay, always put digitalwrite before pinmode to prevent relay engage on startup
        pinMode(RelayPin, OUTPUT);

    }

    if(MotorType == AccessoryType::ROWaterPump || //dont need to save to eeprom because triggered by only float switch
            MotorType == AccessoryType::MacrosDoser) { //dont need to save to eeprom because triggered by tds
        return;
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
        SerialExt::Debug(F("Signaling Relay Pin: "), RelayPin);


#ifdef DEBUG
        digitalWrite(RelayPin, HIGH);
#else
        digitalWrite(RelayPin, _relayHigh);
#endif
    }

    handleRun();

    if(signalRelay) {
        //digitalWrite(RelayPin, HIGH);

#ifdef DEBUG
        digitalWrite(RelayPin, LOW);
#else
        digitalWrite(RelayPin, !_relayHigh);
#endif
    }

    if(MotorType == AccessoryType::ROWaterPump || //dont need to save to eeprom because triggered by only float switch
            MotorType == AccessoryType::MacrosDoser) { //dont need to save to eeprom because triggered by tds
        return;
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

        //if(isSwitchOn) {
        //SerialExt::Debug(F("Sensor Reading"), TheSwitch.SwitchReading);
        //}
    }
    else {
        isSwitchOn = true; //no switch to turn it on.
    }
    return isSwitchOn;
}

void Motor::SetRelayHigh() {
    digitalWrite(RelayPin, LOW);
    _relayHigh = true;
}