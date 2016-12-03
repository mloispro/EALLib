
#include "RODoser.h"

RODoser::RODoser(int pin) : _pin(pin) {
    Init();
}

RODoser::RODoser() {}

void RODoser::Init() {

    if(_pin >= 2) {
        //Serial.print("init - runTime: ");
        //Serial.println(_runTime);
        //_runTime = millis();
        digitalWrite(_pin, LOW);
        pinMode(_pin, OUTPUT);

    }

    //long lastDoseTime = TheSensorsMem.LastDoseTime;
    //if(isnan(lastDoseTime) || isinf(lastDoseTime) != 0) {
    //TheSensorsMem.LastDoseTime = 0;
    //}

    TheSensorsMem.LastDoseTime = 0; //setting to 0 on reset, so we dont wait for days for millis to catch up.

}


void RODoser::Run(double tdsVal) {
    bool pinSet = CheckPin();
    bool shouldRun = ShouldRun(tdsVal);
    bool signalRelay = pinSet && shouldRun;

    if(signalRelay) {
        //SerialExt::Debug(F("Signaling Relay Pin: "), RelayPin);
        Serial.print(F("Signaling Relay Pin: "));
        Serial.println(_pin);
        digitalWrite(_pin, HIGH);

        handleRun();
    }

    if(signalRelay && !_isRunning) {
        //digitalWrite(RelayPin, HIGH);
        digitalWrite(_pin, LOW);
    }


}

bool RODoser::handleRun() {
    long doseDurr = TheSensorsMem.DoseDurrationInSecs * 1000;

    if(!_isRunning) {
        _stopTime = millis() + doseDurr;
    }

    Serial.print("millis: ");
    Serial.println(millis());

    Serial.print("stopTime: ");
    Serial.println(_stopTime);

    _isRunning = true;

    if(millis() >= _stopTime) { //stop running if true.
        _isRunning = false;
        TheSensorsMem.LastDoseTime = millis();
    }
    //delay(doseDurr);
    //TheSensorsMem.LastDoseTime = millis();
}

bool RODoser::CheckPin() {
    if(_pin >= 2) {
        return true;
    }
    return false;
}


bool RODoser::ShouldRun(double tdsVal) {

    bool run = false;

    //check that last dose time is greater than 30 min.
    long lastDoseTime = millis() - TheSensorsMem.LastDoseTime;
    long lastDoseTimeInSecs = lastDoseTime / 1000;
    long lastDoseTimeInMin = lastDoseTimeInSecs / 60; //minute(lastDoseTime);

#ifdef DEBUG
    lastDoseTimeInMin = lastDoseTimeInMin * 15; //to speed up debugging
#endif
    if(lastDoseTimeInMin < 0 || lastDoseTimeInSecs >= 45) {
        //if(lastDoseTimeInMin < 0 || lastDoseTimeInMin >= 20) { //todo: uncomment this and comment above, should be 20

        //get tds check if less than 50..
        int minTds = TheSensorsMem.Tds_minVal;

        if(tdsVal < minTds) {
            run = true;
        }
    }

    return run;
}


//void RODoser::SetRelayHigh() {
//digitalWrite(_pin, LOW);
//_relayHigh = true;
//}