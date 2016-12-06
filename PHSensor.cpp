
#include "PHSensor.h"

#define PH_NUMSAMPLES 36
int _phAvgArr[PH_NUMSAMPLES];

//PHSensor::PHSensor(int pin, int printPHEvery, LCDBase lcd) :
//PHSensor(pin, printPHEvery, false, lcd) {}


PHSensor::PHSensor(int pin, int powerPin, int printPHEvery,  bool printToLCD, LCDBase lcd, bool enabled):
    _pin(pin), _powerPin(powerPin), _printPHEvery(printPHEvery),  _printToLCD(printToLCD), _lcd(lcd), Enabled(enabled) {
    init();
}

//PHSensor::PHSensor() :
//PHSensor(0, 0, false) {}

void PHSensor::init() {

    //led to show board working
    pinMode(13, OUTPUT);

    //digitalWrite(_powerPin, HIGH); //** turns pnp off, needed before pinmode.
    pinMode(_powerPin, OUTPUT);
    //digitalWrite(_powerPin, HIGH);

    //load vars from eeprom
    double offset = TheSensorsMem.Ph_Offset;
    if(!isnan(offset)) {
        Offset = offset;
    }

    //if(isnan(TheSensorsMem.PhVal)) {
    //TheSensorsMem.PhVal = 0;
    //}
}
void PHSensor::Update(double offset) {
    Offset = offset;
    TheSensorsMem.Ph_Offset = Offset;
}


double PHSensor::GetPH() {

    //Serial.print(F("TheSensorsMem.PhVal load: "));
    //Serial.print(TheSensorsMem.PhVal);

    //double tankPH = _pHValue;// - TankOffsetToSubtract;
    PhString = String(PhVal, 2).c_str();
    //PhAvgString = String(_pHAvgValue, 2).c_str();
    return PhVal;

}

void PHSensor::CalculatePH() {

    if(!shouldRead()) {
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

int _runningAvg = 0;
float _runningPHAvg = 0;
double PHSensor::getPHValue() {

    int interval = 4000;

#if DEBUG
    interval = 2;
#endif

    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > interval) { //read every 1 second.
        //int numOfSamples = 30;
        int reading = analogRead(_pin);

        Serial.print(F("PH Raw Reading: "));
        Serial.println(reading);

        ////Serial.print(F("PH Sensor ON"));
        //String powerPin = "power pin: " + String(_powerPin);
        //Serial.println(powerPin);

        if(_runningAvg == 0) {
            _runningAvg = reading;
        }

        _runningAvg = (_runningAvg + reading) / 2;

        _phAvgArr[_pHArrayIndex++] = _runningAvg;
        if(_pHArrayIndex == PH_NUMSAMPLES) {
            _pHArrayIndex = 0;
        }
        double avgReading = MathExt::CalculateAverage(_phAvgArr, PH_NUMSAMPLES);
        _voltage = avgReading * 5.0 / 1024;
        //float pHVal = 3.5 * _voltage + Offset; //for DH Robot PH Sensor
        float pHVal = 7 + ((2.5 - _voltage) / 0.18) + Offset;

        if(_runningPHAvg == 0) {
            _runningPHAvg = pHVal;
        }

        _runningPHAvg = (_runningPHAvg + pHVal) / 2;
        pHVal = _runningPHAvg;

        if(pHVal < 0) {
            pHVal = 0;
        }

        //Serial.print(F("Voltage:"));
        //Serial.print(_voltage, 2);
        //Serial.print(F("    pH value: "));
        //Serial.println(pHVal, 2);

        PhVal = pHVal;
        samplingTime = millis();
        //return pHVal;
    }
    return PhVal;

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
void PHSensor::PrintPHToLCD(String tds, String tempF) {
    if(!shouldRead()) {
        return;
    }

    GetPH();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printPHEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {
            //Serial.print(F("LCD Print: "));
            //Serial.println(tankPH, 2);
            String enabled = "";
            if(_isReading) {
                enabled = "<";
            }

            String text = "PH:" + PhString + " " + enabled;
            _lcd.PrintLine(0, text);

            //String text = "TDS:" + TdsString + " " + TempInFahrenheit + " " + enabled;
            //_lcd.PrintLine(0, text);

            String tdsText = "TDS:" + tds + " " + tempF;
            _lcd.PrintLine(1, tdsText);
        }
        //digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}


bool PHSensor::shouldRead() {
    return (Enabled && _isReading);
}
void PHSensor::TurnOn() {
    _isReading = true;
    Serial.println(F("PH Sensor ON"));
    String powerPin = "power pin: " + String(_powerPin);
    Serial.println(powerPin);
    Serial.println(_powerPin);
    //digitalWrite(_powerPin, LOW); //pnp
    digitalWrite(_powerPin, HIGH);
}

void PHSensor::TurnOff() {
    _isReading = false;
    //digitalWrite(_powerPin, HIGH); //pnp
    digitalWrite(_powerPin, LOW);
    delay(1000);

}
//bool PHSensor::isOutlier(double x, double avg) {
//double cuttOff = .2;//stdDev;// * 1.12; // * 3;
//bool isAbove = x < (avg - cuttOff);
//bool isBelow = x > (avg + cuttOff);
//bool isAOutlier = (isAbove || isBelow);
//return isAOutlier;
//}


