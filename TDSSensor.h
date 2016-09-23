
#ifndef _TDSSENSOR_h
#define _TDSSENSOR_h

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
using namespace std;


#include "LCDBase.h"

class TDSSensor : public erom::Storage {

    private:
        int _pin;

        int _tdsAverage[40];
        int _tdsArrayIndex = 0;
        int _printTDSEvery = 800;
        float _tdsValue;
        float _tdsValueAverage;
        bool _printToLCD;


        LCDBase _lcd;


        void Init();
        double CalculateAverage(int* arr, int number);

        double GetTDSValue();

    public:

        String TdsString;
        String TdsAvgString;

        //double TankOffsetToSubtract = 0;
        erom::Entry<double> Offset = 1210;
        double GetTDS();
        void PrintTDSToLCD();
        void CalculateTDS();

        //void PrintPHToSerial();

        void Update(double offset);
        //String GetResponseString();
        TDSSensor(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd);
        // PHSensor();

};


#endif
