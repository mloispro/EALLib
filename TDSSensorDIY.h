
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

#define NUMSAMPLES 8 //**If you up this, increase the "AsyncDelay". how many samples to take and average, more takes longer, but is more 'smooth'

    private:
        int _pin;
        int _tempSensorPin;
        int _powerPin;

        int _printTDSEvery = 800;
        bool _printToLCD;

        bool _isReading;

        int _tdsAvgArr[NUMSAMPLES];
        int _tdsAvgArrIndex = 0;
        int _samples[NUMSAMPLES];
        //int _numOfSamples = 0;

        LCDBase _lcd;

        void init();
        static void onPulse();
        //double getTDSValue();
        double getTemperature();
        double convTempToFahrenheit(double temp);
        void calculateTDS();
        bool shouldRead();

    public:

        //constants
        const int TEMP_MANUAL = 25; // temp. for nominal resistance (almost always 25 C)
        //const static long SAMPLING_PERIOD = 2200; //*DONT EVER CHANGE *affects reading* default is 2000, the number of seconds to measure 555 oscillations
        const long THERMISTOR_NOMINAL = 10000; //*DONT EVER CHANGE resistance at 25 degrees C
        const long SERIES_RESISTOR = 10000;  //*DONT EVER CHANGE the value of the 'other' resistor
        const long BETA_COEFFICIENT = 3950; // The beta coefficient of the thermistor (usually 3000-4000)
        const float ALPHA_LTC = 0.022; // Temperature correction coefficient

        bool Enabled;

        String TdsString;
        String TempInFahrenheit;
        String TimeSinceLastDose;
        String TimeSinceLastDoseLcd;
        String TdsMin;
        String DoseDuration;
        String TdsSampleDuration;

        double TdsVal = 0;
        float Temperature = 10;
        double Offset = 1.0;
        double Volts = 5.0;
        long SampleDuration = 2200; //*DONT EVER CHANGE *affects reading* default is 2000, the number of seconds to measure 555 oscillations

        long LastDoseTime;
        double GetTDS();
        void PrintTDSToLCD();
        void PrintTDSToSerial();

        void StartReading();
        void StopReading();

        void Update(double offset);
        void UpdateVolts(double volts);
        void UpdateTdsMin(int tdsMin);
        void UpdateRunDurration(int runDurr);
        void UpdateSampleDurration(long sampleDurr);
        TDSSensorDIY(int pin, int tdsPowerPin, int printTDSEvery, bool printToLCD, LCDBase lcd, bool enabled);
        TDSSensorDIY(int pin, int tdsPowerPin, int tempSensorPin, int printTDSEvery, bool printToLCD, LCDBase lcd, bool enabled);

        void TurnOn();
        void TurnOff();
};


#endif
