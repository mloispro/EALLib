
#ifndef _PHSENSOR_h
#define _PHSENSOR_h

#include <Arduino.h>
#include <LiquidCrystal.h>

#include <StandardCplusplus.h>
#include <vector>
using namespace std;

class PHSensor {

private:
    int _pin;
    double _offset = 0.0;
    int _printPHEvery = 800;
    int _pHAverage[40];
    int _pHArrayIndex = 0;
    float _pHValue;
    float _voltage;
    bool _printToLCD;

    //LiquidCrystal* _lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
    LiquidCrystal _lcd;

    void Init();
    double CalculateAverage(int* arr, int number);
    void ClearLCDLine(short lineNum);

public:
    double GetPH();
    double GetVoltage();
    void PrintPHToSerial();
    void PrintPHToLCD();

    PHSensor(int pin, int printPHEvery);
    PHSensor(int pin, int printPHEvery, bool printToLCD);

};

#endif
