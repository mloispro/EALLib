// SerialExt.h

#ifndef CMDMESSENGEREXT_h
#define CMDMESSENGEREXT_h

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <string>

using namespace std;

#include <CmdMessenger.h>

#include "_globalsWaterSensors.h"
using namespace Globals;


////remeber: dependant functions must be defined first in namespace.
///**Better to use template functions.
namespace CmdMessengerExt {

    CmdMessenger _cmdMessenger = CmdMessenger(Serial);

    bool _acquireData                   = false;
    const unsigned long _sampleInterval = 1000; // 1 second interval
    unsigned long _previousSampleMillis = 0;
    long _startAcqMillis                = 0;

    // This is the list of recognized commands. These can be commands that can either be sent or received.
    // In order to receive, attach a callback function to these events
    enum {
        // Commands
        kAcknowledge         , // Command to acknowledge that cmd was received
        kError               , // Command to report errors
        kStartLogging        , // Command to request logging start      (typically PC -> Arduino)
        kSendPH       , // Command to request PH (typically Arduino -> PC)
        kSetPHOffset,
        kSetPHOffsetResult,
        kIdentify,
    };


    void AttachCommandCallbacks();
    void OnUnknownCommand();
    void OnArduinoReady();
    void OnStartLogging();
    bool HasExpired(unsigned long &prevTime, unsigned long interval);
    void SendPH();
    void OnSetPHOffset();
    void OnIdentifyRequest();


    //template<typename T>
    void Init() {
        //_phSensor = phSensor;

        // Adds newline to every command
        //_cmdMessenger.printLfCr();

        // Attach my application's user-defined callback methods
        AttachCommandCallbacks();

        // Send the status to the PC that says the Arduino has booted
        //_cmdMessenger.sendCmd(kAcknowledge, F("Arduino has started!"));
    }
    void Loop() {
        // Process incoming serial data, and perform callbacks
        _cmdMessenger.feedinSerialData();

        // Do measurement after certain sample interval
        if (HasExpired(_previousSampleMillis, _sampleInterval)) {
            if (_acquireData) {
                SendPH();
            }
        }
    }

    // Commands we send from the PC and want to receive on the Arduino.
    // We must define a callback function in our Arduino program for each entry in the list below.

    void AttachCommandCallbacks() {
        // Attach callback methods
        _cmdMessenger.attach(OnUnknownCommand);
        _cmdMessenger.attach(kStartLogging, OnStartLogging);
        _cmdMessenger.attach(kSetPHOffset, OnSetPHOffset);
        _cmdMessenger.attach(kIdentify, OnIdentifyRequest);
    }

    // Callback function to respond to indentify request. This is part of the
    // Auto connection handshake.
    void OnIdentifyRequest() {
        // Here we will send back our communication identifier. Make sure it
        // corresponds the Id in the C# code. Use F() macro to store ID in PROGMEM

        // You can make a unique identifier per device
        _cmdMessenger.sendCmd(kIdentify, F("WaterSensors"));
        //messenger.sendCmd(kIdentify, F("BFAF4176-766E-436A-ADF2-96133C02B03C"));

    }

    // simple readout of two Analog pins.
    void SendPH() {


        float ph = ThePHSensor.GetPH();

        float seconds = (float) (millis() - _startAcqMillis) / 1000.0 ;

        float volts = ThePHSensor.GetVoltage();

        _cmdMessenger.sendCmdStart(kSendPH);
        _cmdMessenger.sendCmdArg(seconds, 4);
        _cmdMessenger.sendCmdSciArg(ph, 2);
        _cmdMessenger.sendCmdSciArg(volts, 2);
        _cmdMessenger.sendCmdEnd();
    }

    void OnSetPHOffset() {
        // Retreive first parameter as float
        float offset = _cmdMessenger.readFloatArg();
        ThePHSensor.Update(offset);

        // Send back the result
        _cmdMessenger.sendCmdStart(kSetPHOffsetResult);
        _cmdMessenger.sendCmdArg(offset);

        _cmdMessenger.sendCmdEnd();
    }

    // Called when a received command has no attached function
    void OnUnknownCommand() {
        _cmdMessenger.sendCmd(kError, F("Command without attached callback"));
    }

    // Callback function that responds that Arduino is ready (has booted up)
    void OnArduinoReady() {
        _cmdMessenger.sendCmd(kAcknowledge, F("Arduino ready"));
    }

    // Callback function calculates the sum of the two received float values
    void OnStartLogging() {
        // Start data acquisition
        _startAcqMillis = millis();
        _acquireData    = true;
        _cmdMessenger.sendCmd(kAcknowledge, F("Start Logging"));
    }

    // Returns if it has been more than interval (in ms) ago. Used for periodic actions
    bool HasExpired(unsigned long &prevTime, unsigned long interval) {
        if (  millis() - prevTime > interval ) {
            prevTime = millis();
            return true;
        }
        else {
            return false;
        }
    }

}






#endif

