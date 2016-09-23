
#include "_globalsWaterSensors.h"

namespace Globals {

    int _phSensorPin = A5;//A15;
    int _tdsSensorPin = A4;//A14;

    LCDBase TheLCD = LCDBase();

    PHSensor ThePHSensor = PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensor TheTDSSensor = TDSSensor(_tdsSensorPin, 1000, true, TheLCD);

}

