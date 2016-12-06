
#include "_globalsWaterSensors.h"

namespace Globals {

    bool _isPhSensorEnabled = true; //todo: ensure proper sensors are enabled..
    bool _isTdsSensorEnabled = true;

    int _tdsSensorPin = 19;//3;//2; //*needs to be a interupt pin: 2, 3, 18, 19, 20, 21
    int _tdsTemperaturePin = A13;//A3;//A13;
    int _tdsPowerPin = 24;//11;
    // int _tdsRelayPin = 31;
    int _phSensorPin = A14;//A2;
    int _phPowerPin = 25;
    int _roDoserRelayPin = 51;

    bool ReadingTDS = true;
    long SensorReadInterval = 600000;//300000;//5000; // every 5 min switch ph and tds sensor
    long SensorReadDuration = 0;

    static LCDBase _theLCD = LCDBase();
    static PHSensor _thePHSensor = PHSensor(_phSensorPin, _phPowerPin, 2000, true, TheLCD, _isPhSensorEnabled );
    static TDSSensorDIY _theTDSSensor = TDSSensorDIY(_tdsSensorPin, _tdsPowerPin, _tdsTemperaturePin, 1000, true, TheLCD, _isTdsSensorEnabled);
    static AsyncDelay _tdsSensorRun(TheTDSSensor.SampleDuration, 2500);

    //static TDSSensor _theTDSSensor = TDSSensor(_tdsSensorPin, 1000, true, TheLCD, _tdsRelayPin);

    static RODoser _roDoser = RODoser(_roDoserRelayPin);

    LCDBase& TheLCD = _theLCD;

    PHSensor& ThePHSensor = _thePHSensor;//PHSensor(_phSensorPin, 2000, true, TheLCD);

    TDSSensorDIY& TheTDSSensor = _theTDSSensor;
    AsyncDelay& TdsSensorRun = _tdsSensorRun;
    //TDSSensor& TheTDSSensor = _theTDSSensor;

    RODoser& TheRODoser = _roDoser;

}

