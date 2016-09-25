
#include "PHSensor.h"


PHSensor::PHSensor(int pin, int printPHEvery, LCDBase lcd) :
    PHSensor(pin, printPHEvery, false, lcd) {}

PHSensor::PHSensor(int pin, int printPHEvery, bool printToLCD, LCDBase lcd):
    _pin(pin), _printPHEvery(printPHEvery), _printToLCD(printToLCD), _lcd(lcd) {
    Init();
}

//PHSensor::PHSensor() :
//PHSensor(0, 0, false) {}

void PHSensor::Init() {
    //led to show board working
    pinMode(13, OUTPUT);

    //load vars from eeprom
    Offset.load();
    if(isnan(Offset)) {
        Offset = 3.0;
    }
}
void PHSensor::Update(double offset) {
    Offset = offset;
    Offset.save();
}


double PHSensor::GetPH() {

    //double tankPH = _pHValue;// - TankOffsetToSubtract;
    PhString = String(_pHValue, 2).c_str();
    PhAvgString = String(_pHAvgValue, 2).c_str();
    return _pHValue;

}

void PHSensor::CalculatePH() {
    _pHValue = GetPHValue();

    //hourly avg
    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 60000) { //add every 1 minute.
        int numOfSamples = 60;
        int pHHourAverageSize = _pHHourAverage.size();
        if(pHHourAverageSize <= numOfSamples) {
            _pHHourAverage.push_back(_pHValue);
        }
        else {
            _pHHourAverage[_pHHourArrayIndex++] = _pHValue;
        }

        if(_pHHourArrayIndex == numOfSamples) {
            _pHHourArrayIndex = 0;
        }
        _pHAvgValue = CalculateAverage(_pHHourAverage);
        samplingTime = millis();
    }
    //Serial.print(F("samplingTime: "));
    //Serial.println(millis() - samplingTime);
    //Serial.print(F("_pHHourAverage.size: "));
    //Serial.println(_pHHourAverage.size());
    //Serial.print(F("_pHHourArrayIndex: "));
    //Serial.println(_pHHourArrayIndex);
    //Serial.print(F("_pHAvgValue: "));
    //Serial.println(_pHAvgValue);
    //Serial.print(F("_pHValue: "));
    //Serial.println(_pHValue);

}

double PHSensor::GetPHValue() {
    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 1000) { //read every 1 second.
        int numOfSamples = 40;
        _pHAverage[_pHArrayIndex++] = analogRead(_pin);
        if(_pHArrayIndex == numOfSamples) {
            _pHArrayIndex = 0;
        }
        double avgReading = CalculateAverage(_pHAverage, numOfSamples);
        _voltage = avgReading * 5.0 / 1024;
        //float pHVal = 3.5 * _voltage + Offset; //for DH Robot PH Sensor
        float pHVal = 7 + ((2.5 - _voltage) / 0.18) + Offset;
        return pHVal;
        samplingTime = millis();
    }
    return _pHValue;

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
    double tankPH = GetPH();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printPHEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {

            String text = "PH: " + String(tankPH, 2);
            _lcd.PrintLine(0, text);
        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}

double PHSensor::CalculateAverage(vector<double> phs) {
    double total = 0;
    for(int i = 0; i < phs.size(); i++) {
        total += phs[i];
    }
    double avgPh = total / phs.size();
    return avgPh;
}
double PHSensor::CalculateAverage(int* arr, int number) {
    int i;
    int max, min;
    double avg;
    long amount = 0;
    if(number <= 0) {
        Serial.println(F("Error number for the array to avraging!/n"));
        return 0;
    }
    if(number < 5) { //less than 5, calculated directly statistics
        for(i = 0; i < number; i++) {
            amount += arr[i];
        }
        avg = amount / number;
        return avg;
    }
    else {
        if(arr[0] < arr[1]) {
            min = arr[0];
            max = arr[1];
        }
        else {
            min = arr[1];
            max = arr[0];
        }
        for(i = 2; i < number; i++) {
            if(arr[i] < min) {
                amount += min;      //arr<min
                min = arr[i];
            }
            else {
                if(arr[i] > max) {
                    amount += max;  //arr>max
                    max = arr[i];
                }
                else {
                    amount += arr[i]; //min<=arr<=max
                }
            }//if
        }//for
        avg = (double)amount / (number - 2);
    }//if
    return avg;
}





