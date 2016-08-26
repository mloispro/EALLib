
#include "PHSensor.h"

PHSensor::PHSensor(int pin, int printPHEvery) :
    PHSensor(pin, printPHEvery, false) {}

PHSensor::PHSensor(int pin, int printPHEvery, bool printToLCD):
    _pin(pin), _printPHEvery(printPHEvery), _printToLCD(printToLCD), _lcd(8, 9, 4, 5, 6, 7) {
    Init();
}


void PHSensor::Init() {
//led to show board working
    pinMode(13, OUTPUT);
    if(_printToLCD) {
        _lcd.begin(16, 2);
        _lcd.clear();
        _lcd.setCursor(0, 0);
    }

}

double PHSensor::GetPH() {
    static unsigned long samplingTime = millis();
    //static float pHValue, voltage;
    if(millis() - samplingTime > 60) {
        _pHAverage[_pHArrayIndex++] = analogRead(_pin);
        if(_pHArrayIndex == 40) {
            _pHArrayIndex = 0;
        }
        _voltage = CalculateAverage(_pHAverage, 40) * 5.0 / 1024;
        _pHValue = 2.5 * _voltage + _offset;
        samplingTime = millis();
    }
    return _pHValue;
}
double PHSensor::GetVoltage() {

    return _voltage;
}
void PHSensor::PrintPHToSerial() {
    GetPH();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printPHEvery) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        //if(Serial.available()) {
        Serial.print("Voltage:");
        Serial.print(_voltage, 2);
        Serial.print("    pH value: ");
        Serial.println(_pHValue, 2);
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

            ClearLCDLine(0);
            _lcd.setCursor(0, 0);
            _lcd.print("PH: ");
            _lcd.print(_pHValue, 2);

        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
void PHSensor::ClearLCDLine(short lineNum) {
    _lcd.setCursor(0, lineNum);
    _lcd.print("                ");
}
double PHSensor::CalculateAverage(int* arr, int number) {
    int i;
    int max, min;
    double avg;
    long amount = 0;
    if(number <= 0) {
        Serial.println("Error number for the array to avraging!/n");
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





