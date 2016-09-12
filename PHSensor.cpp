
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

    //if(_printToLCD) {
    //_lcd.begin(16, 2);
    //_lcd.clear();
    //_lcd.setCursor(0, 0);
    //}

    //load vars from eeprom
    _mem.load();
    double memOffset = _mem.Offset;
    _offset = memOffset;
    if(isnan(_offset)) {
        _offset = 0;
    }
}
void PHSensor::Update(double offset) {
    _offset = offset;
    _mem.Offset = _offset;
    _mem.save();
}
double PHSensor::GetPH() {

    double tankPH = _pHValue - TankOffsetToSubtract;
    return tankPH;

}

void PHSensor::CalculatePH() {
    float phTotal = GetPHValue();
    int numOfSamples = 1;

    for(int i = 0; i <= 20; i++) {
        int wait = i + 100;
        delay(wait);
        float phVal = GetPHValue();
        phTotal += phVal;
        numOfSamples++;
    }
    float phAverage = phTotal / numOfSamples;
    _pHValue = phAverage;

}

double PHSensor::GetPHValue() {
    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 110) {
        int numOfSamples = 80;
        _pHAverage[_pHArrayIndex++] = analogRead(_pin);
        if(_pHArrayIndex == numOfSamples) {
            _pHArrayIndex = 0;
        }
        _voltage = CalculateAverage(_pHAverage, numOfSamples) * 5.0 / 1024;
        //float pHVal = 3.5 * _voltage + _offset; //for DH Robot PH Sensor
        float pHVal = 7 + ((2.5 - _voltage) / 0.18) + _offset;
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

            _lcd.ClearLine(0);
            _lcd.setCursor(0, 0);
            _lcd.print(F("PH: "));
        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
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





