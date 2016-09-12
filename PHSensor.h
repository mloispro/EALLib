
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

// Define a 'Storage' class that will manage EEPROM related data
class PHSensorStorage : public erom::Storage {
    protected:
        // Define rules for loading storage into RAM
        virtual void OnLoad() {
            Offset.load();
            //brightness.load();
        }
        // Define rules for saving storage into EEPROM
        virtual void OnSave() {
            Offset.save();
            //brightness.save();
        }

    public:
        // Storage data/variables
        erom::Entry<double> Offset;
        //erom::Entry<short> brightness;

        // Binding/allocating variable to EEPROM memory addresses
        PHSensorStorage() {
            issue(Offset);
            //issue(brightness);
        }
};

class PHSensor {

    private:
        int _pin;

        int _pHAverage[80];
        int _pHArrayIndex = 0;
        int _printPHEvery = 800;
        float _pHValue;
        float _voltage;
        bool _printToLCD;

        //eeprom vars
        PHSensorStorage _mem;
        double _offset = 0;

        LCDBase _lcd;
        //LiquidCrystal* _lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
        //LiquidCrystal _lcd;

        void Init();
        double CalculateAverage(int* arr, int number);
        void ClearLCDLine(short lineNum);
        double GetPHValue();

        //PHSensor& operator=(const PHSensor& c);
        //PHSensor(const PHSensor& c);
    public:

        double TankOffsetToSubtract = 0;
        double GetPH();
        void CalculatePH();
        double GetVoltage();
        void PrintPHToSerial();
        void PrintPHToLCD();
        void Update(double offset);

        PHSensor(int pin, int printPHEvery, LCDBase lcd);
        PHSensor(int pin, int printPHEvery, bool printToLCD, LCDBase lcd);
        // PHSensor();

};


#endif
