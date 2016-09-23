
#include "TDSSensor.h"


//TDSSensor::TDSSensor(int pin, int printPHEvery, LCDBase lcd) :
//TDSSensor(pin, printPHEvery, false, lcd) {}

TDSSensor::TDSSensor(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd):
    _pin(pin), _printTDSEvery(printTDSEvery), _printToLCD(printToLCD), _lcd(lcd) {
    Init();
}

//PHSensor::PHSensor() :
//PHSensor(0, 0, false) {}

void TDSSensor::Init() {
    //led to show board working
    pinMode(13, OUTPUT);


    //load vars from eeprom
    Offset.load();
    if(isnan(Offset)) {
        Offset = 1210;
    }
}
void TDSSensor::Update(double offset) {
    Offset = offset;
    Offset.save();
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

    TdsString = String(_tdsValue, 2).c_str();
    TdsAvgString = String(_tdsValueAverage, 2).c_str();
    return _tdsValue;

}
void TDSSensor::PrintTDSToLCD() {
    double tankTDS = GetTDS();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printTDSEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {

            String text = "TDS: " + String(tankTDS, 2);
            _lcd.PrintLine(1, text);

        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
void TDSSensor::CalculateTDS() {
    float tdsTotal = GetTDSValue();
    int numOfSamples = 1;

    for(int i = 0; i <= 10; i++) {
        int wait = i + 100;
        delay(wait);
        float tdsVal = GetTDSValue();
        tdsTotal += tdsVal;
        numOfSamples++;
    }
    float phAverage = tdsTotal / numOfSamples;
    _tdsValue = phAverage;

}

double TDSSensor::GetTDSValue() {
    static unsigned long samplingTime = millis();
    if(millis() - samplingTime > 110) {
        int numOfSamples = 40;
        _tdsAverage[_tdsArrayIndex++] = analogRead(_pin);
        if(_tdsArrayIndex == numOfSamples) {
            _tdsArrayIndex = 0;
        }
        double tdsAvg = CalculateAverage(_tdsAverage, numOfSamples);
        double voltage = tdsAvg * (5.0 / 1024);
        double tankTDS = voltage * Offset;

        return tankTDS;
        samplingTime = millis();
    }
    return _tdsValue;

}


double TDSSensor::CalculateAverage(int* arr, int number) {
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





