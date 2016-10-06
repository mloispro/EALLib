
#include "_globalsWaterSensors.h"

namespace Globals {

    int _phSensorPin = A3;//A13;
    int _tdsSensorPin = A2;//A12;
    int _phRelayPin = 3;
    int _tdsRelayPin = 2;
    bool ReadingTDS = false;
    long SensorReadInterval = 300000;//300000;//5000; // every 5 min switch ph and tds sensor

    static LCDBase _theLCD = LCDBase();
    static PHSensor _thePHSensor = PHSensor(_phSensorPin, 2000, true, TheLCD, _phRelayPin);
    static TDSSensor _theTDSSensor = TDSSensor(_tdsSensorPin, 1000, true, TheLCD, _tdsRelayPin);

    LCDBase& TheLCD = _theLCD;

    PHSensor& ThePHSensor = _thePHSensor;//PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensor& TheTDSSensor = _theTDSSensor;//TDSSensor(_tdsSensorPin, 1000, true, TheLCD);

    void SwitchSensors() {
        ReadingTDS = !ReadingTDS;
        if(ReadingTDS) {
            ThePHSensor.TurnOff();
            TheTDSSensor.TurnOn(); //signal mofset
        }
        else {
            TheTDSSensor.TurnOff();//signal mofset
            ThePHSensor.TurnOn();
        }
    }

}

