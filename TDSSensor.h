
#ifndef _TDSSENSOR_h
#define _TDSSENSOR_h

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
using namespace std;

#include "SensorsMem.h"
using namespace Memory;
#include "MathExt.h"
#include "LCDBase.h"

class TDSSensor {

#define NUMSAMPLES 10

    private:
        int _pin;

        int _tdsAvgArr[NUMSAMPLES];
        //int _tdsAverage[10];
        int _tdsArrayIndex = 0;
        int _printTDSEvery = 800;
        //float _tdsValue;
        //float _tdsValueAverage;
        //float _tdsTotal;
        bool _printToLCD;
        int _relayPin;
        bool _enabled;
        int _numOfSamples = 0;

        LCDBase _lcd;


        void init();
        //double calculateAverage(int* arr, int number);

        double getTDSValue();

    public:

        double TdsVal = 0;
        String TdsString;
        //String TdsAvgString;

        //double TankOffsetToSubtract = 0;
        //erom::Entry<int> Offset = 1210;
        int Offset = 270;
        double GetTDS();
        void PrintTDSToLCD();
        void CalculateTDS();

        //void PrintPHToSerial();

        void Update(int offset);
        //String GetResponseString();
        TDSSensor(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin);
        // PHSensor();

        void TurnOn();
        void TurnOff();
};


#endif
