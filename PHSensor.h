
#ifndef _PHSENSOR_h
#define _PHSENSOR_h

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;

#include "SensorsMem.h"
using namespace Memory;
#include "MathExt.h"

#include "LCDBase.h"

class PHSensor {

    private:
        int _pin;

        //int _pHAverage[30];
        int _pHArrayIndex = 0;
        int _printPHEvery = 800;

        //vector<double> _pHHourAverage;
        //int _pHHourArrayIndex = 0;
        //float _pHValue;
        //float _pHAvgValue;
        float _voltage;
        bool _printToLCD;
        int _relayPin;
        bool _enabled;
        //int _outlierCount = 0;

        LCDBase _lcd;

        void init();
        void clearLCDLine(short lineNum);
        double getPHValue();
        //bool isOutlier(double x, double avg);
        //PHSensor& operator=(const PHSensor& c);
        //PHSensor(const PHSensor& c);
    public:

        String PhString;
        //String PhAvgString;

        //double TankOffsetToSubtract = 0;
        //erom::Entry<double> Offset = 3.0;
        double Offset = 3.0;
        double GetPH();
        void CalculatePH();
        double GetVoltage();
        void PrintPHToSerial();
        void PrintPHToLCD();
        void Update(double offset);
        //String GetResponseString();

        //PHSensor(int pin, int printPHEvery, LCDBase lcd);
        PHSensor(int pin, int printPHEvery, bool printToLCD, LCDBase lcd, int relayPin);
        //PHSensor() {};

        void TurnOff();
        void TurnOn();
};


#endif
