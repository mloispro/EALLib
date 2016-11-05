
#include "TDSSensorDIY.h"
//https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/24646-three-dollar-ec-ppm-meter-arduino


TDSSensorDIY::TDSSensorDIY(int pin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin):
    TDSSensorDIY(pin, 0, printTDSEvery, printToLCD, lcd, relayPin) {

}

TDSSensorDIY::TDSSensorDIY(int pin, int tempSensorPin, int printTDSEvery, bool printToLCD, LCDBase lcd, int relayPin):
    _pin(pin), _tempSensorPin(tempSensorPin), _printTDSEvery(printTDSEvery), _printToLCD(printToLCD), _lcd(lcd), _relayPin(relayPin) {
    init();
}

void TDSSensorDIY::init() {
    //led to show board working
    pinMode(13, OUTPUT);
    pinMode(_relayPin, OUTPUT);

    //load vars from eeprom
    //TdsOffset.load();
    //if(isnan(TdsOffset)) {
    //TdsOffset = 1210;
    //}

    double offset = TheSensorsMem.TdsOffset;
    if(!isnan(offset)) {
        Offset = offset;
    }
    if(isnan(TheSensorsMem.TdsVal)) {
        TheSensorsMem.TdsVal = 0;
    }
}
void TDSSensorDIY::Update(int offset) {
    Offset = offset;
    TheSensorsMem.TdsOffset = Offset;
}

double TDSSensorDIY::GetTDS() {

    TdsString = String(TheSensorsMem.TdsVal, 0).c_str();
    double temp = convTempToFahrenheit(_temperature);
    TempInFahrenheit = String(temp, 1).c_str();
    TempInFahrenheit += "F";
    return TheSensorsMem.TdsVal;

}
void TDSSensorDIY::PrintTDSToLCD() {
    GetTDS();
    static unsigned long printTime = millis();
    if(millis() - printTime > _printTDSEvery + 400) { //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
        if(_printToLCD) {
            String enabled = "";
            if(_enabled) {
                enabled = "<";
            }
            String text = "TDS:" + TdsString + "," + TempInFahrenheit + " " + enabled;
            _lcd.PrintLine(1, text);

        }
        digitalWrite(13, digitalRead(13) ^ 1);
        printTime = millis();
    }
}
void TDSSensorDIY::CalculateTDS() {

    if(!_enabled) {
        return;
    }

    getTDSValue();

}

double TDSSensorDIY::getTDSValue() {
    static unsigned long samplingTime = millis();
    //todo: change to 5000
    if(millis() - samplingTime > 500) {//wait .5 sec between readings, according to spec
        int numOfSamples = 10;
        int reading = analogRead(_pin);

        Serial.print(F("TDS Raw Reading: "));
        Serial.println(reading);

        float vIn = 3.1;//5;
        if (vIn < 4.5) {
            float voltDiff = 5.0 - vIn + 1; //0, 1 ,2
            reading = reading * (voltDiff * _voltageRatio);
        }

        reading = 1024 - reading; //invert reading

        //_tdsAverage[_tdsArrayIndex++] = reading;
        TheSensorsMem.TdsAvgArr[_tdsArrayIndex++] = reading;
        if(_tdsArrayIndex == numOfSamples) {
            _tdsArrayIndex = 0;
        }
        double temperature = getTemperature();

        double readingAvg = MathExt::CalculateAverage(TheSensorsMem.TdsAvgArr, numOfSamples);

        float ec = 0;
        float ec25 = 0;
        int ppm = 0;


        float vDrop = 0;
        float rc = 0;

        int totalResistance = (_resistance + _pinResistance);
        vDrop = (vIn * readingAvg) / 1024.0;
        rc = (vDrop * totalResistance) / (vIn - vDrop);
        rc = rc - _pinResistance; //acounting for Digital Pin Resitance
        ec = 1000 / (rc * _cellConstant);

        ec25  =  ec / (1 + _temperatureCoef * (temperature - 25.0)); //compensate for temp
        ppm = (ec25) * (_ppmConversion * 1000);

        //todo: multiply offset
        double tankTDS = ppm;// * Offset;

        TheSensorsMem.TdsVal = tankTDS;
        //TheSensorsMem.TdsVal = reading;

        samplingTime = millis();

    }
    return TheSensorsMem.TdsVal;

}
double TDSSensorDIY::getTemperature() {
    if(_tempSensorPin <= 0) {
        return _temperature;
    }
    int reading = analogRead(_tempSensorPin);

    if(reading <= 60) {
        _temperature = 0;
        return 20;    //68F
    }


    _temperature = log(_tempProbeResistance * ((1024.0 / reading - 1)));
    _temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * _temperature * _temperature )) * _temperature );
    _temperature = _temperature - 273.15;

    return _temperature;
}

double TDSSensorDIY::convTempToFahrenheit(double temp) {
    double  tempF = (temp * 9.0) / 5.0 + 32.0;
    return tempF;
}

void TDSSensorDIY::TurnOn() {
    _enabled = true;
    digitalWrite(_relayPin, HIGH);
}

void TDSSensorDIY::TurnOff() {
    _enabled = false;
    digitalWrite(_relayPin, LOW);
    delay(1000);

}



