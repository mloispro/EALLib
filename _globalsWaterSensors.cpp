
#include "_globalsWaterSensors.h"

namespace Globals {

    int _phSensorPin = A3;//A13;
    int _tdsSensorPin = A2;//A12;

    LCDBase TheLCD = LCDBase();
    static PHSensor _thePHSensor = PHSensor(_phSensorPin, 2000, true, TheLCD);
    static TDSSensor _theTDSSensor = TDSSensor(_tdsSensorPin, 1000, true, TheLCD);

    PHSensor& ThePHSensor = _thePHSensor;//PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensor& TheTDSSensor = _theTDSSensor;//TDSSensor(_tdsSensorPin, 1000, true, TheLCD);

}

