
#include "TDSSensor.h"


//TDSSensor::TDSSensor(int pin, int printPHEvery, LCDBase lcd) :
//TDSSensor(pin, printPHEvery, false, lcd) {}

TDSSensor::TDSSensor(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin):
    _pin(pin), _printTDSEvery(printTDSEvery), _printToLCD(printToLCD), _lcd(lcd), _relayPin(relayPin) {
    init();
}

//PHSensor::PHSensor() :
//PHSensor(0, 0, false) {}

void TDSSensor::init() {
    //led to show board working
    pinMode(13, OUTPUT);
    pinMode(_relayPin, OUTPUT);

    //load vars from eeprom
    //TdsOffset.load();
    //if(isnan(TdsOffset)) {
    //TdsOffset = 1210;
    //}

    double offset = TheSensorsMem.TdsOffset;
    if(!isnan(offset)) {
        Offset = offset;
    }
}
void TDSSensor::Update(int offset) {
    Offset = offset;
    TheSensorsMem.TdsOffset = Offset;
}

double TDSSensor::GetTDS() {
    //double offset = 1210;
    //double tankTDS = 0;

    // read the analog in value:
    //double tdsReading = analogRead(_pin);
    //double voltage = tdsReading * (5.00 / 1024);
    //tankTDS = voltage * Offset;

    // map it to the range of the analog out:
    //double outputValue = map(tdsReading, 0, 1023, 0, 5000);
    //// change the analog out value:
    //analogWrite(9, outputValue);
    //double sensorVal2 = analogRead(_pin);//analogRead(1);


    TdsString = String(_tdsValue, 0).c_str();
    TdsAvgString = String(_tdsValueAverage, 0).c_str();
    return _tdsValue;

}
void TDSSensor::PrintTDSToLCD() {
    GetTDS();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printTDSEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {
            String enabled = "";
            if(_enabled) {
                enabled = "<";
            }
            String text = "TDS: " + TdsAvgString + ", " + TdsString + enabled;
            _lcd.PrintLine(1, text);

        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
void TDSSensor::CalculateTDS() {

    if(!_enabled) {
        return;
    }

    _tdsValue = getTDSValue();

    if(_numOfSamples <= 1) {
        _numOfSamples = 1;
        _tdsTotal = _tdsValue;
    }

    //_tdsTotal = getTDSValue();

    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 60000) { //wait 1 min inbetween readings

        _tdsValue = getTDSValue();
        _tdsTotal += _tdsValue;
        _numOfSamples++;

        samplingTime = millis();
    }

    _tdsValueAverage = _tdsTotal / _numOfSamples;
    //Serial.print(F("tdsTotal: "));
    //Serial.println(_tdsTotal, 2);
    //Serial.print(F("_numOfSamples: "));
    //Serial.println(_numOfSamples);
    //Serial.print(F("_tdsValueAverage: "));
    //Serial.println(_tdsValueAverage, 2);

    //soften
    _tdsValueAverage = (_tdsValueAverage + _tdsValue) / 2;
    //Serial.print(F("sft_tdsValueAverage: "));
    //Serial.println(_tdsValueAverage, 2);

    if(_numOfSamples > 10) {
        _numOfSamples = 1;
    }

}

double TDSSensor::getTDSValue() {
    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 500) {//wait .5 sec between readings, according to spec
        int numOfSamples = 40;
        _tdsAverage[_tdsArrayIndex++] = analogRead(_pin);
        if(_tdsArrayIndex == numOfSamples) {
            _tdsArrayIndex = 0;
        }
        double tdsAvg = MathExt::CalculateAverage(_tdsAverage, numOfSamples);
        double voltage = tdsAvg * (5.0 / 1024);
        double tankTDS = voltage * Offset;

        return tankTDS;
        samplingTime = millis();
    }
    return _tdsValue;

}


void TDSSensor::TurnOn() {
    _enabled = true;
    digitalWrite(_relayPin, HIGH);
}

void TDSSensor::TurnOff() {
    _enabled = false;
    digitalWrite(_relayPin, LOW);
    delay(1000);

}



