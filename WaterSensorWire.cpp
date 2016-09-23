
#include "WaterSensorWire.h"

const byte _slave = 18;
static const uint8_t _wireReqLength = 20;
static const uint8_t _wireRespLength = 10;
static String _wireRequest = "";
static String _wireResponse = "";
static int _responseIndex = -1;
static String _cmd = "";
static String _cmdData = "";
static String _response = "";

void WaterSensorWire::Setup() {
    Wire.begin(_slave); //attached to esp8266 wifi
    Wire.onRequest(Request);
    Wire.onReceive(Receive);

}
void WaterSensorWire::Receive(int bytes) {
    //!!DONT PUT SERIAL.PRINTS IN HERE IT WILL SCREW UP WIRE COMM!!
    _wireRequest = "";
    _cmd = "";
    _cmdData = "";
    if(bytes == _wireReqLength) {
        while (0 < Wire.available()) {
            char c = Wire.read();
            _wireRequest.concat(c);
        }
        //Serial.println("Wire Request: " + _wireRequest);
        _wireRequest.trim();
        if(_wireRequest.startsWith("/")) {
            _cmd = _wireRequest;
            //Serial.println("cmd: " + _cmd);
        }
        else {
            _cmdData = _wireRequest;
            //Serial.println("cmdData: " + _cmdData);
            String var = SplitString(_cmdData, '=', 0);
            String val = SplitString(_cmdData, '=', 1);
            if(var == "tdsoffset") {
                double offset = val.toFloat();
                TheTDSSensor.Update(offset);
            }
            else if(var == "phoffset") {
                double offset = val.toFloat();
                ThePHSensor.Update(offset);
            }
        }
    }
    else {
        Serial.print(F("Unexpected number of bytes received: "));
        Serial.println(bytes);
    }
}
void WaterSensorWire::Request() {
    //!!DONT PUT SERIAL.PRINTS IN HERE IT WILL SCREW UP WIRE COMM!!

    _responseIndex++;
    String partialResponse = "";
    if(_responseIndex == 0) {
        partialResponse = ThePHSensor.PhString;
    }
    else if(_responseIndex == 1) {
        partialResponse = ThePHSensor.PhAvgString;
    }
    else if(_responseIndex == 2) {
        partialResponse = TheTDSSensor.TdsString;
    }
    else if(_responseIndex == 3) {
        partialResponse = TheTDSSensor.TdsAvgString;
    }
    else if(_responseIndex == 4) {
        partialResponse = String(ThePHSensor.Offset, 2).c_str();
    }
    else if(_responseIndex == 5) {
        partialResponse = String(TheTDSSensor.Offset, 2).c_str();
        _responseIndex = -1; //need to keep this in last if always
    }
    else {
        Serial.print("~responseIndex not found: ");
        Serial.println(_responseIndex);
        _responseIndex = -1;
        return;
    }

    //Pad
    int diff = _wireRespLength - partialResponse.length();
    for(int i = 0; i < diff; i++) {
        partialResponse += " ";
    }
    byte response[_wireRespLength];
    for (byte i = 0; i < _wireRespLength; i++) {
        response[i] = (byte)partialResponse.charAt(i);
    }
    Wire.write(response, sizeof(response));
}

String WaterSensorWire::SplitString(String data, char separator, int index) {
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
