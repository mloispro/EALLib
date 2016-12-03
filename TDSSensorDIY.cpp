
#include "TDSSensorDIY.h"
//https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/24646-three-dollar-ec-ppm-meter-arduino

//*dont change*
const float noEC = 0.00;   //  The conductivity probe is dry
const float lowEC = 6.00;//2.00   //  Value of calibration buffers
const float medEC = 46.0;//12.88;  //  You can use any other buffers
const float highEC = 76.00;//80.0;
const float highHighEC = 142.00;

//calibration vars, these change after calibration
const int noPulse = 230;
const int lowPulse = 1340;
const int medPulse = 4140;
const int highPulse = 6350;//7350;
const int highHighPulse = 10200;

long _pulseCount = 0;  //a pulse counter variable
unsigned long _pulseTime, _lastTime, _duration, _totalDuration;

static int _tdsSensorPin;

TDSSensorDIY::TDSSensorDIY(int pin, int tdsPowerPin, int printTDSEvery, bool printToLCD, LCDBase lcd, bool enabled):
    TDSSensorDIY(pin, tdsPowerPin, 0, printTDSEvery, printToLCD, lcd, enabled) {
}

TDSSensorDIY::TDSSensorDIY(int pin, int tdsPowerPin, int tempSensorPin, int printTDSEvery, bool printToLCD, LCDBase lcd, bool enabled):
    _pin(pin), _tempSensorPin(tempSensorPin), _powerPin(tdsPowerPin), _printTDSEvery(printTDSEvery), _printToLCD(printToLCD), _lcd(lcd), Enabled(enabled) {
    init();
}

void TDSSensorDIY::init() {

    //led to show board working
    pinMode(13, OUTPUT);

    pinMode(_powerPin, OUTPUT);
    _tdsSensorPin = _pin;

    //load vars from eeprom
    //TdsOffset.load();
    //if(isnan(TdsOffset)) {
    //TdsOffset = 1210;
    //}

    double offset = TheSensorsMem.Tds_Offset;
    if(!isnan(offset)) {
        Offset = offset;
    }
    //if(isnan(TheSensorsMem.Tds_Val)) {
    //TheSensorsMem.Tds_Val = 0;
    //}
    double volts = TheSensorsMem.Tds_volts;
    if(isnan(volts) ||
            isinf(volts) != 0 ||
            volts < 2 ||
            volts > 5) {
        TheSensorsMem.Tds_volts = 5.0;
        Volts = 5.0;
    }
    else {
        Volts = volts;
    }

    int tdsMin = TheSensorsMem.Tds_minVal;
    if(isnan(tdsMin) ||
            isinf(tdsMin) != 0 ||
            tdsMin < 5 ||
            tdsMin > 260) {
        TheSensorsMem.Tds_minVal = 50;
    }
    int doseDurr = TheSensorsMem.DoseDurrationInSecs;
    if(isnan(doseDurr) ||
            isinf(doseDurr) != 0 ||
            doseDurr < 0 ||
            doseDurr > 120) {
        TheSensorsMem.DoseDurrationInSecs = 2;//2 secs
    }

}
void TDSSensorDIY::Update(double offset) {
    Offset = offset;
    TheSensorsMem.Tds_Offset = Offset;
}
void TDSSensorDIY::UpdateVolts(double volts) {
    Volts = volts;
    TheSensorsMem.Tds_volts = Volts;
}
void TDSSensorDIY::UpdateTdsMin(int tdsMin) {
    //TdsMin = tdsMin;
    TheSensorsMem.Tds_minVal = tdsMin;
}
void TDSSensorDIY::UpdateRunDurration(int runDurr) {
    //TdsMin = tdsMin;
    TheSensorsMem.DoseDurrationInSecs = runDurr;
}

double TDSSensorDIY::GetTDS() {

    TdsString = String(TdsVal, 0).c_str();
    double temp = convTempToFahrenheit(Temperature);
    TempInFahrenheit = String(temp, 1).c_str();
    TempInFahrenheit += "F";

    long lastDoseInterval =  millis() - TheSensorsMem.LastDoseTime;//millis() - TheSensorsMem.LastDoseTime;//TheSensorsMem.LastDoseTime - millis();
    long timeSinceLastDose = lastDoseInterval / 1000;
    TimeSinceLastDose = String(timeSinceLastDose).c_str();
    TimeSinceLastDose += "s";

    String interString = MathExt::GetTimeIntervalString(lastDoseInterval).c_str();
    TimeSinceLastDoseLcd = "LD:" + interString;

    TdsMin = String(TheSensorsMem.Tds_minVal, 0).c_str();

    int doseDurr = TheSensorsMem.DoseDurrationInSecs;
    DoseDuration = String(doseDurr).c_str();
    DoseDuration += "s";

    return TdsVal;

}
void TDSSensorDIY::PrintTDSToLCD() {
    if(!shouldRead()) {
        return;
    }
    GetTDS();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printTDSEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {
            String enabled = "";
            //if(_isReading) {
            //enabled = "<";
            //}
            String text = "TDS:" + TdsString + " " + TempInFahrenheit + " " + enabled;
            _lcd.PrintLine(0, text);

            String line2 = TimeSinceLastDoseLcd + " mTds:" + TdsMin;
            //_lcd.PrintLine(1, line2);
            _lcd.HandleScrollText(1, line2);

        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
//void TDSSensorDIY::CalculateTDS() {
//
//if(!_enabled) {
//return;
//}
//
//getTDSValue();
//
//}

void TDSSensorDIY::calculateTDS() {

    float a;
    float b;
    float c = 0;

    long lowPulseCount = (noPulse + lowPulse);
    long medPulseCount = (medPulse + lowPulse + noPulse);
    long highHighPulseCount = (highPulse + medPulse + lowPulse + noPulse);

    int higherPulseVar;
    int lowerPulseVar;
    float higherEcVar;
    float lowerEcVar;

    Serial.print("pulseCount: ");
    Serial.println(_pulseCount);

    if (_pulseCount >= noPulse && _pulseCount < lowPulseCount) {
        //low
        //Serial.println(F("calc case - low"));
        higherPulseVar = lowPulse;
        lowerPulseVar = noPulse;
        higherEcVar = lowEC;
        lowerEcVar = noEC;
    }
    else if (_pulseCount >= lowPulseCount && _pulseCount < medPulseCount) {
        //med
        //Serial.println(F("calc case - med"));
        higherPulseVar = medPulse;
        lowerPulseVar = lowPulse;
        higherEcVar = medEC;
        lowerEcVar = lowEC;
    }
    else if (_pulseCount >= medPulseCount && _pulseCount < highHighPulseCount) {
        //high
        //Serial.println(F("calc case - high"));
        higherPulseVar = highPulse;
        lowerPulseVar = medPulse;
        higherEcVar = highEC;
        lowerEcVar = medEC;
    }
    else if (_pulseCount >= highHighPulseCount) {
        //highhigh
        //Serial.println(F("calc case - highhigh"));
        higherPulseVar = highHighPulse;
        lowerPulseVar = highPulse;
        higherEcVar = highHighEC;
        lowerEcVar = highEC;
    }

    if (_pulseCount > noPulse) {
        a = (higherPulseVar - lowerPulseVar) / (higherEcVar - lowerEcVar);
        b = lowerPulseVar - (a * lowerEcVar);
        c = (_pulseCount - b) / a;
    }
    else {
        //Serial.println(F("calc case - none"));
        c = 0;
    }

    double tds = (c / (1 + ALPHA_LTC * (Temperature - 25.00))); //  temperature compensation
    tds += Offset;
    //TdsVal = tds;
    Serial.print(F("TdsReading: "));
    Serial.println(tds);

    _tdsAvgArr[_tdsAvgArrIndex++] = tds;
    if(_tdsAvgArrIndex == NUMSAMPLES) {
        _tdsAvgArrIndex = 0;
    }
    double avgReading = MathExt::CalculateAverage(_tdsAvgArr, NUMSAMPLES);
    TdsVal = avgReading;
    Serial.print(F("TdsAvg: "));
    Serial.println(TdsVal);



    //return tds;

}


double TDSSensorDIY::convTempToFahrenheit(double temp) {
    float vIn = Volts;//3.1;//5;
    if (vIn < 5.0) {
        float voltDiff = 5.0 - vIn; //0, 1 ,2
        vIn = 5.0 + voltDiff;
    }

    double  tempF = (temp * 9.0) / vIn + 32.0;
    return tempF;
}



void TDSSensorDIY::StartReading() {

    if(!shouldRead()) {
        return;
    }

    Serial.println(F("startReading "));
    //String sensorPin = "Sensor Pin: " + String(_tdsSensorPin);
    //Serial.println(sensorPin);

    //turn on the 555 system
    digitalWrite(_powerPin, HIGH); //turns on the 555 timer subcircuit

    getTemperature();

    // conductivity --------------------------------------

    _pulseCount = 0; //reset the pulse counter
    _totalDuration = 0; //reset the totalDuration of all pulses measured

    //start sampling
    attachInterrupt(digitalPinToInterrupt(_tdsSensorPin), onPulse, RISING); //attach an interrupt counter to interrupt pin 1 (digital pin #3) -- the only other possible pin on the 328p is interrupt pin #0 (digital pin #2)
    //attachInterrupt(1,onPulse,RISING);

    _pulseTime = micros(); // start the stopwatch
}

void TDSSensorDIY::StopReading() {
    if(!shouldRead()) {
        return;
    }

    Serial.println(F("stopReading "));
    detachInterrupt(digitalPinToInterrupt(_pin)); //we've finished sampling, so detach the interrupt function -- don't count any more pulses
    //detachInterrupt(1);

    //turn off the 555 system
    digitalWrite(_powerPin, LOW);

    if (_pulseCount > 0) { //use this logic in case something went wrong

        double durationS = _totalDuration / double(_pulseCount) / 1000000.; //the total duration, in seconds, per pulse (note that totalDuration was in microseconds)

        // print out stats
        /*Serial.print("sampling period=");
        Serial.print(samplingPeriod);
          Serial.print(" sec; #pulses=");
        Serial.print(pulseCount);
        Serial.print("; duration per pulse (sec)=");
        */

        // print conductivity value
        //    Serial.print(durationS,4);
        //    Serial.print(", ");
        //    Serial.println(Temp);

    }

    //TempInFahrenheit = convTempToFahrenheit(Temperature);
    calculateTDS();

    //should be called from controller in real app.
    //printValsToSerial();
    //printValsToLCD();
}

void TDSSensorDIY::onPulse() {

    _pulseCount++;
    //  Serial.print("pulsecount=");
    //  Serial.println(pulseCount);
    _lastTime = _pulseTime;
    _pulseTime = micros();
    _duration = _pulseTime - _lastTime;
    _totalDuration += _duration;
    //Serial.println(totalDuration);
}

bool TDSSensorDIY::shouldRead() {
    return (Enabled && _isReading);
}

void TDSSensorDIY::PrintTDSToSerial() {
    Serial.println(F(""));
    Serial.print(F("  t "));
    Serial.print(Temperature, 1);
    Serial.print(F("*C "));
    Serial.print(F(" , "));
    Serial.print(TempInFahrenheit);
    //Serial.print("*F ");
    Serial.print(F("  TDS "));
    Serial.print(TdsVal, 2);
    Serial.print(F("   PPM "));
    Serial.print(TdsVal * 500, 0);
    Serial.print(F("   Frequency "));
    Serial.print(_pulseCount);
    Serial.println(F(" Hz"));
}

double TDSSensorDIY::getTemperature() {
    // temperature ---------------------------------------------

    float average;

    // take N samples in a row, with a slight delay
    for (int i = 0; i < NUMSAMPLES; i++) {
        int tempReading = analogRead(_tempSensorPin);
        //     Serial.print("tempReading: ");
        //      Serial.println(tempReading);
        _samples[i] = tempReading;
        delay(10);
    }

    // average all the samples out
    average = 0;
    for (int i = 0; i < NUMSAMPLES; i++) {
        average += _samples[i];
    }
    average /= NUMSAMPLES;

    // convert the value to resistance
    average = 1023 / average - 1;
    average = SERIES_RESISTOR / average;
    //    Serial.print("Thermistor resistance ");
    //    Serial.println(average);

    float steinhart;
    steinhart = average / THERMISTOR_NOMINAL;     // (R/Ro)
    steinhart = log(steinhart);                  // ln(R/Ro)
    steinhart /= BETA_COEFFICIENT;                   // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMP_MANUAL + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                 // Invert
    steinhart -= 273.15;                         // convert to C

    Temperature = steinhart;
    //  Serial.print(Temp);
    //  Serial.println(" *C");
}

void TDSSensorDIY::TurnOn() {
    _isReading = true;
    //digitalWrite(_relayPin, HIGH);
}

void TDSSensorDIY::TurnOff() {
    _isReading = false;
    digitalWrite(_powerPin, LOW);
    delay(1000);

}

//pen   diy   cnt     lvl   match
//-------------------------
//30          2420
//52          3848
//70          4939
//94    70    6722   high  no       <-need intermediate level
//130         8770
//180   180   11080   high  yes
//220   226   12260
//280   300   15300
//310   330   16370
//440   447   21000



//double TDSSensorDIY::getTemperature() {
//if(_tempSensorPin <= 0) {
//return _temperature;
//}
//int reading = analogRead(_tempSensorPin);
//
//if(reading <= 60) {
//_temperature = 0;
//return 20;    //68F
//}
//
//
//_temperature = log(_tempProbeResistance * ((1024.0 / reading - 1)));
//_temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * _temperature * _temperature )) * _temperature );
//_temperature = _temperature - 273.15;
//
//return _temperature;
//}