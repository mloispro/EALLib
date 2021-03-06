
#include "_globalsROController.h"

namespace Globals {

    bool IsHighLevelRelay = true; //todo: may have to set this low..
    bool _isPhSensorEnabled = false; //todo: ensure proper sensors are enabled..
    bool _isTdsSensorEnabled = true;

    int _tdsSensorPin = 19;//3;//2; //*needs to be a interupt pin: 2, 3, 18, 19, 20, 21
    int _tdsTemperaturePin = A15;//A3;//A13;
    int _tdsPowerPin = 34;//11;
    int _tdsRelayPin = 31;
    int _phSensorPin = A14;//A2;
    int _phPowerPin = 35;
    int _roDoserRelayPin = 30;
    bool ReadingTDS = true;
    long SensorReadInterval = 600000;//300000;//5000; // every 5 min switch ph and tds sensor
    long SensorReadDuration = 0;

    static LCDBase _theLCD = LCDBase();
    static PHSensor _thePHSensor = PHSensor(_phSensorPin, _phPowerPin, 2000, true, TheLCD, _isPhSensorEnabled );
    static TDSSensorDIY _theTDSSensor = TDSSensorDIY(_tdsSensorPin, _tdsPowerPin, _tdsTemperaturePin, 1000, true, TheLCD, _isTdsSensorEnabled);
    static RODoser _roDoser = RODoser(_roDoserRelayPin);


    LCDBase& TheLCD = _theLCD;

    PHSensor& ThePHSensor = _thePHSensor;//PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensorDIY& TheTDSSensor = _theTDSSensor;//TDSSensor(_tdsSensorPin, 1000, true, TheLCD);
    RODoser& TheRODoser = _roDoser;


}

