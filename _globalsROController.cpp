
#include "_globalsROController.h"

namespace Globals {

    //int _phSensorPin = A13;//A3;
    int _tdsSensorPin = A12;//A2;
    int _tdsTemperaturePin = A13;
    //int _phRelayPin = 30;
    int _tdsRelayPin = 31;
    //bool ReadingTDS = true;
    long SensorReadInterval = 600000;//300000;//5000; // every 5 min switch ph and tds sensor
    long SensorReadDuration = 0;

    static LCDBase _theLCD = LCDBase();
    //static PHSensor _thePHSensor = PHSensor(_phSensorPin, 2000, true, TheLCD, _phRelayPin);
    static TDSSensorDIY _theTDSSensor = TDSSensorDIY(_tdsSensorPin, _tdsTemperaturePin, 1000, true, TheLCD, _tdsRelayPin);

    LCDBase& TheLCD = _theLCD;

    //PHSensor& ThePHSensor = _thePHSensor;//PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensorDIY& TheTDSSensor = _theTDSSensor;//TDSSensor(_tdsSensorPin, 1000, true, TheLCD);



}

