
#include "_sketchExtROController.h"

namespace Sketch {

    AsyncDelay _tdsSensorRun(TDSSensorDIY::SAMPLING_PERIOD, 2500);

    void(* resetFunc) (void) = 0;//declare reset function at address 0

    void Setup() {

        wdt_enable(WDTO_8S);

        //if(IsHighLevelRelay) {
        //TheRODoser.SetRelayHigh(); //doing this because using a high level relay in aquarium controler
        //}

        _tdsSensorRun.Start(TDSSensorRun_Start);
        _tdsSensorRun.Stop(TDSSensorRun_Stop);
        TheTDSSensor.TurnOn();
        ROTankWire::Setup();
    }

    void Loop() {
        _tdsSensorRun.Loop();
        ThePHSensor.PrintPHToLCD();
        TheTDSSensor.PrintTDSToLCD();

        //CmdMessengerExt::Loop();

        //if(millis() >= 44400000) { //reset every 6 hours. 21600000
        //
        ////Serial.print(F("Reseting Arduino: "));
        ////Serial.println(millis());
        //delay(100);
        //resetFunc(); //call reset
        //}
    }

    void AsyncDoWork() {

        wdt_reset();

        //Serial.print(F("millis: "));
        //Serial.println(millis());

        static unsigned long lastSensorReadTime = millis();

        if(TheLCD.DetectKeyPress() == LcdKeyPress::Select) {
            Serial.println(F("[Selelct] Pressed"));
            SwitchSensors();
            lastSensorReadTime = millis();
        }
        SensorReadDuration = millis() - lastSensorReadTime;

        ROTankWire::Loop();
        if(SensorReadDuration > SensorReadInterval) {

            //SwitchSensors();
            lastSensorReadTime = millis();
        }

        if(!ReadingTDS) {
            ThePHSensor.CalculatePH();
        }

        TheRODoser.Run(TheTDSSensor.TdsVal);

    }
    void TDSSensorRun_Start() {
        TheTDSSensor.StartReading();

    }
    void TDSSensorRun_Stop() {
        TheTDSSensor.StopReading();
    }

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

