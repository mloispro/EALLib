
#include "AquaControllerWire.h"

const byte _slave = 8; //has to be greater than 8
static const uint8_t _wireReqLength = 20;
static const uint8_t _wireRespLength = 10;
static String _wireRequest = "";
static String _wireResponse = "";
static int _responseIndex = -1;
static String _cmd = "";
static String _cmdData = "";
static String _response = "";
//static long _lastReqReceived = 0;

static WireRunInfo _dryDoserInfo;
static WireRunInfo _macrosDoserInfo;
static WireRunInfo _microsDoserInfo;
static WireRunInfo _tankPumpInfo;

static WireRunInfo _currentWireRunInfo;
static WireRunInfo _updateWireRunInfo;

void AquaControllerWire::Setup() {
    Serial.print(F("_slave: "));
    Serial.println(_slave);

    Wire.begin(_slave); //attached to esp8266 wifi

    Wire.onRequest(Request);
    Wire.onReceive(Receive);

    //_lastReqReceived = millis();


}

WireRunInfo& AquaControllerWire::GetUpdatedRunInfo() {
    return _updateWireRunInfo;
}

void AquaControllerWire::Loop(NextRunMemory& mem, long updated) {

    if(mem.AccType == MicrosDoser) {
        _microsDoserInfo.AccType = String(mem.AccType).c_str();
        _microsDoserInfo.CountDown = String(mem.CountDown).c_str();
        _microsDoserInfo.Enabled = String(mem.Enabled).c_str();
        _microsDoserInfo.LastRun = String(mem.LastRun).c_str();
        _microsDoserInfo.LastSave = String(mem.LastSave).c_str();
        _microsDoserInfo.NextRun = String(mem.NextRun).c_str();
        _microsDoserInfo.RunDurration = String(mem.RunDurration).c_str();
        _microsDoserInfo.RunEvery = String(mem.RunEvery).c_str();
        _microsDoserInfo.ShakesOrTurns = String(mem.ShakesOrTurns).c_str();
        _microsDoserInfo.Updated = String(updated).c_str();
    }
    else if(mem.AccType == MacrosDoser) {
        _macrosDoserInfo.AccType = String(mem.AccType).c_str();
        _macrosDoserInfo.CountDown = String(mem.CountDown).c_str();
        _macrosDoserInfo.Enabled = String(mem.Enabled).c_str();
        _macrosDoserInfo.LastRun = String(mem.LastRun).c_str();
        _macrosDoserInfo.LastSave = String(mem.LastSave).c_str();
        _macrosDoserInfo.NextRun = String(mem.NextRun).c_str();
        _macrosDoserInfo.RunDurration = String(mem.RunDurration).c_str();
        _macrosDoserInfo.RunEvery = String(mem.RunEvery).c_str();
        _macrosDoserInfo.ShakesOrTurns = String(mem.ShakesOrTurns).c_str();
        _macrosDoserInfo.Updated = String(updated).c_str();
    }
    else if(mem.AccType == WaterPump) {
        _tankPumpInfo.AccType = String(mem.AccType).c_str();
        _tankPumpInfo.CountDown = String(mem.CountDown).c_str();
        _tankPumpInfo.Enabled = String(mem.Enabled).c_str();
        _tankPumpInfo.LastRun = String(mem.LastRun).c_str();
        _tankPumpInfo.LastSave = String(mem.LastSave).c_str();
        _tankPumpInfo.NextRun = String(mem.NextRun).c_str();
        _tankPumpInfo.RunDurration = String(mem.RunDurration).c_str();
        _tankPumpInfo.RunEvery = String(mem.RunEvery).c_str();
        _tankPumpInfo.ShakesOrTurns = String(mem.ShakesOrTurns).c_str();
        _tankPumpInfo.Updated = String(updated).c_str();
    }
    else if(mem.AccType == DryDoser) {
        _dryDoserInfo.AccType = String(mem.AccType).c_str();
        _dryDoserInfo.CountDown = String(mem.CountDown).c_str();
        _dryDoserInfo.Enabled = String(mem.Enabled).c_str();
        _dryDoserInfo.LastRun = String(mem.LastRun).c_str();
        _dryDoserInfo.LastSave = String(mem.LastSave).c_str();
        _dryDoserInfo.NextRun = String(mem.NextRun).c_str();
        _dryDoserInfo.RunDurration = String(mem.RunDurration).c_str();
        _dryDoserInfo.RunEvery = String(mem.RunEvery).c_str();
        _dryDoserInfo.ShakesOrTurns = String(mem.ShakesOrTurns).c_str();
        _dryDoserInfo.Updated = String(updated).c_str();
    }

}

void AquaControllerWire::SetCurrentRunInfo() {
    if(_cmd == "/CheckMicrosDose" ||
            _cmd == "/SetMicrosDose") {
        _currentWireRunInfo = _microsDoserInfo;
    }
    else if(_cmd == "/CheckDryDose") {
        _currentWireRunInfo = _dryDoserInfo;
    }
    else if(_cmd == "/CheckWaterChange" ||
            _cmd == "/SetWaterChange") {
        _currentWireRunInfo = _tankPumpInfo;
    }
    else if(_cmd == "/CheckMacrosDose" ||
            _cmd == "/SetMacrosDose") {
        _currentWireRunInfo = _macrosDoserInfo;
    }
}

void AquaControllerWire::Receive(int bytes) {
    //!!DONT PUT SERIAL.PRINTS IN HERE IT WILL SCREW UP WIRE COMM!!

    _wireRequest = "";
    _cmd = "";
    _cmdData = "";
    if(bytes == _wireReqLength) {
        while (Wire.available() > 0) {
            char c = Wire.read();
            _wireRequest.concat(c);
        }
        //Serial.print("Wire Request: ");
        //Serial.println(_wireRequest);
        _wireRequest.trim();
        if(_wireRequest.startsWith("/")) {
            _cmd = _wireRequest;
            SetCurrentRunInfo();
            Serial.print(F("cmd: "));
            Serial.println(_cmd);
        }
        else {
            _cmdData = _wireRequest;
            Serial.print(F("cmdData: "));
            Serial.println(_cmdData);
            String var = SplitString(_cmdData, '=', 0);
            String val = SplitString(_cmdData, '=', 1);
            //set vals here
            int updateAccType = _updateWireRunInfo.AccType.toInt();
            if(updateAccType == 0) {
                _updateWireRunInfo = _currentWireRunInfo;
            }
            if(var == "enabled") {
                //bool enabled = val.toInt();
                _updateWireRunInfo.Enabled = val;
            }
            else if(var == "dur") {
                //double duration = val.toInt();
                _updateWireRunInfo.RunDurration = val;
            }
            else if(var == "re") {
                //double duration = val.toInt();
                _updateWireRunInfo.RunEvery = val;
            }
            else if(var == "rNow") {
                //double duration = val.toInt();
                _updateWireRunInfo.RunNow = val;
            }
            else if(var == "nr") {
                //double duration = val.toInt();
                _updateWireRunInfo.NextRun = val;
            }
        }
    }
    else {
        Serial.print(F("Unexpected number of bytes received: "));
        Serial.println(bytes);
    }
}
void AquaControllerWire::Request() {
    //!!DONT PUT SERIAL.PRINTS IN HERE IT WILL SCREW UP WIRE COMM!!

    //Serial.println("Request()");
    //_lastReqReceived = millis();

    String partialResponse;
    if(_cmd == "/") {
        partialResponse = "Index";

        Transmit(partialResponse);
        return;
    }

    //
    _responseIndex++;
    //String partialResponse = "";
    if(_responseIndex == 0) {
        partialResponse = _currentWireRunInfo.AccType;
    }
    else if(_responseIndex == 1) {
        partialResponse = _currentWireRunInfo.LastRun;
    }
    else if(_responseIndex == 2) {
        partialResponse = _currentWireRunInfo.NextRun;
    }
    else if(_responseIndex == 3) {
        partialResponse = _currentWireRunInfo.CountDown;
    }
    else if(_responseIndex == 4) {
        partialResponse = _currentWireRunInfo.RunEvery;
    }
    else if(_responseIndex == 5) {
        partialResponse = _currentWireRunInfo.ShakesOrTurns;
    }
    else if(_responseIndex == 6) {
        partialResponse = _currentWireRunInfo.LastSave;
    }
    else if(_responseIndex == 7) {
        partialResponse = _currentWireRunInfo.Enabled;
    }
    else if(_responseIndex == 8) {
        partialResponse = _currentWireRunInfo.RunDurration;
    }
    else if(_responseIndex == 9) {
        partialResponse = _currentWireRunInfo.Updated;
        _responseIndex = -1; //need to keep this in last if always
    }
    else {
        Serial.print(F("~responseIndex not found: "));
        Serial.println(_responseIndex);
        _responseIndex = -1;
        return;
    }

    Transmit(partialResponse);
}



void AquaControllerWire::Transmit(String partialResponse) {
    //Serial.print("partialResponse: ");
    //Serial.println(partialResponse);

    //pad
    int diff = _wireRespLength - partialResponse.length();
    for(int i = 0; i < diff; i++) {
        partialResponse += " ";
    }
    byte response[_wireRespLength];
    for (int i = 0; i < _wireRespLength; i++) {
        response[i] = partialResponse.charAt(i);
        //Serial.println(response[i]);
    }

    //for (int i = 0; i < _wireRespLength; i++) {
    //char p = response[i];
    //Serial.println(p);
    //}
    Wire.write(response, _wireRespLength);
    // delay(10);//todo: may need to delete this
}



String AquaControllerWire::SplitString(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;
    for(int i = 0; i <= maxIndex && found <= index; i++) {
        if(data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void AquaControllerWire::Scan() {
    byte error, address;
    int nDevices;

    Serial.println(F("Scanning..."));

    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print(F("I2C device found at address 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println("  !");

            nDevices++;
        }
        else if (error == 4) {
            Serial.print(F("Unknow error at address 0x"));
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println(F("No I2C devices found\n"));
    }
    else {
        Serial.println(F("done\n"));
    }

    //delay(5000);           // wait 5 seconds for next scan
}

int AquaControllerWire::I2C_ClearBus() {
#if defined(TWCR) && defined(TWEN)
    TWCR &= ~(_BV(TWEN)); //Disable the Atmel 2-Wire interface so we can control the SDA and SCL pins directly
#endif

    pinMode(SDA, INPUT_PULLUP); // Make SDA (data) and SCL (clock) pins Inputs with pullup.
    pinMode(SCL, INPUT_PULLUP);

    delay(2500);  // Wait 2.5 secs. This is strictly only necessary on the first power
    // up of the DS3231 module to allow it to initialize properly,
    // but is also assists in reliable programming of FioV3 boards as it gives the
    // IDE a chance to start uploaded the program
    // before existing sketch confuses the IDE by sending Serial data.

    boolean SCL_LOW = (digitalRead(SCL) == LOW); // Check is SCL is Low.
    if (SCL_LOW) { //If it is held low Arduno cannot become the I2C master.
        return 1; //I2C bus error. Could not clear SCL clock line held low
    }

    boolean SDA_LOW = (digitalRead(SDA) == LOW);  // vi. Check SDA input.
    int clockCount = 20; // > 2x9 clock

    while (SDA_LOW && (clockCount > 0)) { //  vii. If SDA is Low,
        clockCount--;
        // Note: I2C bus is open collector so do NOT drive SCL or SDA high.
        pinMode(SCL, INPUT); // release SCL pullup so that when made output it will be LOW
        pinMode(SCL, OUTPUT); // then clock SCL Low
        delayMicroseconds(10); //  for >5uS
        pinMode(SCL, INPUT); // release SCL LOW
        pinMode(SCL, INPUT_PULLUP); // turn on pullup resistors again
        // do not force high as slave may be holding it low for clock stretching.
        delayMicroseconds(10); //  for >5uS
        // The >5uS is so that even the slowest I2C devices are handled.
        SCL_LOW = (digitalRead(SCL) == LOW); // Check if SCL is Low.
        int counter = 20;
        while (SCL_LOW && (counter > 0)) {  //  loop waiting for SCL to become High only wait 2sec.
            counter--;
            delay(100);
            SCL_LOW = (digitalRead(SCL) == LOW);
        }
        if (SCL_LOW) { // still low after 2 sec error
            return 2; // I2C bus error. Could not clear. SCL clock line held low by slave clock stretch for >2sec
        }
        SDA_LOW = (digitalRead(SDA) == LOW); //   and check SDA input again and loop
    }
    if (SDA_LOW) { // still low
        return 3; // I2C bus error. Could not clear. SDA data line held low
    }

    // else pull SDA line low for Start or Repeated Start
    pinMode(SDA, INPUT); // remove pullup.
    pinMode(SDA, OUTPUT);  // and then make it LOW i.e. send an I2C Start or Repeated start control.
    // When there is only one I2C master a Start or Repeat Start has the same function as a Stop and clears the bus.
    /// A Repeat Start is a Start occurring after a Start with no intervening Stop.
    delayMicroseconds(10); // wait >5uS
    pinMode(SDA, INPUT); // remove output low
    pinMode(SDA, INPUT_PULLUP); // and make SDA high i.e. send I2C STOP control.
    delayMicroseconds(10); // x. wait >5uS
    pinMode(SDA, INPUT); // and reset pins as tri-state inputs which is the default state on reset
    pinMode(SCL, INPUT);
    return 0; // all ok
}