
#ifndef _TDSSENSORDIY_h
#define _TDSSENSORDIY_h
//https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/24646-three-dollar-ec-ppm-meter-arduino

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

class TDSSensorDIY {

    private:
        int _pin;
        int _tempSensorPin = 0;

        //##################################################################################
        //-----------  Do not Replace R1 with a resistor lower than 300 ohms    ------------
        //##################################################################################
        int _resistance = 1000;//330; //R1
        int _pinResistance = 25; //Resistance of powering Pins

        float _ppmConversion = 0.7; //common conversion


        //*************Compensating for temperature ************************************//
        //The value below will change depending on what chemical solution we are measuring
        //0.019 is generaly considered the standard for plant nutrients [google "Temperature compensation EC" for more info
        //float TemperatureCoef = 0.019; //this changes depending on what chemical we are measuring
        float _temperatureCoef = 0.0214; //for water according to google.


        //********************** Cell Constant For Ec Measurements *********************//
        //Mine was around 2.9 with plugs being a standard size they should all be around the same
        //But If you get bad readings you can use the calibration script and fluid to get a better estimate for K
        //float K = 2.88;
        float _cellConstant = 2.7;

        float _voltageRatio = 0.652173913;


        float _tempProbeResistance = 10000.0; //10K ohm, always use 10K resistor on sensor board since it is a 10k sensor.


        int _tdsArrayIndex = 0;
        int _printTDSEvery = 800;
        float _temperature = 10;
        bool _printToLCD;
        int _relayPin;
        bool _enabled;
        int _numOfSamples = 0;

        LCDBase _lcd;

        void init();
        double getTDSValue();
        double getTemperature();
        double convTempToFahrenheit(double temp);

    public:

        String TdsString;
        String TempInFahrenheit;

        int Offset = 1;
        double GetTDS();
        void PrintTDSToLCD();
        void CalculateTDS();

        void Update(int offset);
        TDSSensorDIY(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin);
        TDSSensorDIY(int pin, int tempSensorPin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin);

        void TurnOn();
        void TurnOff();
};


#endif
