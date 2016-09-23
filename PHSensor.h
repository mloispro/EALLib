
#ifndef _PHSENSOR_h
#define _PHSENSOR_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
using namespace std;


#include "LCDBase.h"

class PHSensor : public erom::Storage {

    private:
        int _pin;

        int _pHAverage[60];
        int _pHArrayIndex = 0;
        int _printPHEvery = 800;
        float _pHValue;
        float _pHAvgValue;
        float _voltage;
        bool _printToLCD;

        LCDBase _lcd;

        void Init();
        double CalculateAverage(int* arr, int number);
        void ClearLCDLine(short lineNum);
        double GetPHValue();

        //PHSensor& operator=(const PHSensor& c);
        //PHSensor(const PHSensor& c);
    public:

        String PhString;
        String PhAvgString;

        //double TankOffsetToSubtract = 0;
        erom::Entry<double> Offset = 3.0;
        double GetPH();
        void CalculatePH();
        double GetVoltage();
        void PrintPHToSerial();
        void PrintPHToLCD();
        void Update(double offset);
        //String GetResponseString();

        PHSensor(int pin, int printPHEvery, LCDBase lcd);
        PHSensor(int pin, int printPHEvery, bool printToLCD, LCDBase lcd);
        //PHSensor() {};

};


#endif
