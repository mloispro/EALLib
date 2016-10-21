
#include "PHSensor.h"


//PHSensor::PHSensor(int pin, int printPHEvery, LCDBase lcd) :
//PHSensor(pin, printPHEvery, false, lcd) {}

PHSensor::PHSensor(int pin, int printPHEvery, bool printToLCD, LCDBase lcd, int relayPin):
    _pin(pin), _printPHEvery(printPHEvery), _printToLCD(printToLCD), _lcd(lcd), _relayPin(relayPin) {
    init();
}

//PHSensor::PHSensor() :
//PHSensor(0, 0, false) {}

void PHSensor::init() {
    //led to show board working
    pinMode(13, OUTPUT);
    pinMode(_relayPin, OUTPUT);

    //load vars from eeprom
    double offset = TheSensorsMem.PhOffset;
    if(!isnan(offset)) {
        Offset = offset;
    }

    if(isnan(TheSensorsMem.PhVal)) {
        TheSensorsMem.PhVal = 0;
    }
}
void PHSensor::Update(double offset) {
    Offset = offset;
    TheSensorsMem.PhOffset = Offset;
}


double PHSensor::GetPH() {

    //Serial.print(F("TheSensorsMem.PhVal load: "));
    //Serial.print(TheSensorsMem.PhVal);

    //double tankPH = _pHValue;// - TankOffsetToSubtract;
    PhString = String(TheSensorsMem.PhVal, 2).c_str();
    //PhAvgString = String(_pHAvgValue, 2).c_str();
    return TheSensorsMem.PhVal;

}

void PHSensor::CalculatePH() {

    if(!_enabled) {
        return;
    }

    //TheSensorsMem.PhVal = getPHValue();
    getPHValue();

    ////hourly avg
    //static unsigned long samplingTime = millis();
    //if(millis() - samplingTime > 60000) { //add every 1 minute.
    ////_phValue = MathExt::RandomFloat(8, 6.9);
    //double avg = 0;
    //if(_pHHourAverage.size() < 5) {
    //_pHHourAverage.push_back(_pHValue);
    //
    //avg = MathExt::GetAverage(_pHHourAverage);
    //_pHAvgValue = avg;
    //return;
    //}
    //avg = MathExt::GetAverage(_pHHourAverage);
    //
    ////soften the avg
    //double phAvg = (_pHValue + avg) / 2;
    //
    //bool isAOutlier = isOutlier(_pHValue, phAvg);
    //if(isAOutlier && _outlierCount < 10) {
    //_outlierCount++;
    ////Serial.print(F("Outlier Found, skipping add: "));
    ////Serial.print(phAvg);
    ////Serial.print(F(" - "));
    ////Serial.println(millis() - samplingTime);
    ////Serial.print(F("_outlierCount: "));
    ////Serial.println(_outlierCount);
    //return;
    //}
    //_outlierCount = 0;
    //
    //int numOfSamples = 15;
    //int pHHourAverageSize = _pHHourAverage.size();
    //
    //if(pHHourAverageSize < numOfSamples) {
    //Serial.print(F("Adding phVal: "));
    //Serial.println(phAvg);
    //_pHHourAverage.push_back(phAvg);
    //
    //}
    //else {
    //Serial.print(F("Setting phVal: "));
    //Serial.println(phAvg);
    //_pHHourAverage[_pHHourArrayIndex++] = phAvg;
    //
    //}
    //
    //if(_pHHourArrayIndex == numOfSamples) {
    //_pHHourArrayIndex = 0;
    //}
    //
    //double avgPh = MathExt::GetAverage(_pHHourAverage);
    //_pHAvgValue = avgPh;
    //samplingTime = millis();
    //}
    ////Serial.print(F("samplingTime: "));
    ////Serial.println(millis() - samplingTime);
    ////Serial.print(F("_pHHourAverage.size: "));
    ////Serial.println(_pHHourAverage.size());
    ////Serial.print(F("_pHHourArrayIndex: "));
    ////Serial.println(_pHHourArrayIndex);
    ////Serial.print(F("_pHAvgValue: "));
    ////Serial.println(_pHAvgValue);
    ////Serial.print(F("_pHValue: "));
    ////Serial.println(_pHValue);

}

double PHSensor::getPHValue() {

    int interval = 5000;

#if DEBUG
    interval = 2;
#endif

    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > interval) { //read every 1 second.
        int numOfSamples = 30;
        int reading = analogRead(_pin);

        Serial.print(F("PH Raw Reading: "));
        Serial.println(reading);

        TheSensorsMem.PhAvgArr[_pHArrayIndex++] = reading;
        if(_pHArrayIndex == numOfSamples) {
            _pHArrayIndex = 0;
        }
        double avgReading = MathExt::CalculateAverage(TheSensorsMem.PhAvgArr, numOfSamples);
        _voltage = avgReading * 5.0 / 1024;
        //float pHVal = 3.5 * _voltage + Offset; //for DH Robot PH Sensor
        float pHVal = 7 + ((2.5 - _voltage) / 0.18) + Offset;

        if(pHVal < 0) {
            pHVal = 0;
        }

        //Serial.print(F("Voltage:"));
        //Serial.print(_voltage, 2);
        //Serial.print(F("    pH value: "));
        //Serial.println(pHVal, 2);

        TheSensorsMem.PhVal = pHVal;
        samplingTime = millis();
        //return pHVal;
    }
    return TheSensorsMem.PhVal;

}

double PHSensor::GetVoltage() {

    return _voltage;
}
void PHSensor::PrintPHToSerial() {
    double tankPH = GetPH();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printPHEvery) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        //if(Serial.available()) {
        Serial.print(F("Voltage:"));
        Serial.print(_voltage, 2);
        Serial.print(F("    pH value: "));
        Serial.println(tankPH, 2);
        //}
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
void PHSensor::PrintPHToLCD() {
    GetPH();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printPHEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {
            //Serial.print(F("LCD Print: "));
            //Serial.println(tankPH, 2);
            String enabled = "";
            if(_enabled) {
                enabled = "<";
            }

            String text = "PH: " + PhString + " " + enabled;
            _lcd.PrintLine(0, text);
        }
        //digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}



void PHSensor::TurnOn() {
    _enabled = true;
    digitalWrite(_relayPin, HIGH);
}

void PHSensor::TurnOff() {
    _enabled = false;
    digitalWrite(_relayPin, LOW);
    delay(1000);

}
//bool PHSensor::isOutlier(double x, double avg) {
//double cuttOff = .2;//stdDev;// * 1.12; // * 3;
//bool isAbove = x < (avg - cuttOff);
//bool isBelow = x > (avg + cuttOff);
//bool isAOutlier = (isAbove || isBelow);
//return isAOutlier;
//}


