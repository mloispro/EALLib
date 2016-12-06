
#include "_sketchExtWaterSensors.h"

namespace Sketch {


    void(* resetFunc) (void) = 0;//declare reset function at address 0

    void Setup() {

        wdt_enable(WDTO_8S);

        TdsSensorRun.Start(TDSSensorRun_Start);
        TdsSensorRun.Stop(TDSSensorRun_Stop);
        ThePHSensor.TurnOff();
        TheTDSSensor.TurnOn();
        WaterSensorWire::Setup();
    }

    void Loop() {
        TdsSensorRun.Loop();
        TheTDSSensor.PrintTDSToLCD();

        String tdsVal = TheTDSSensor.TdsString;
        String tempF = TheTDSSensor.TempInFahrenheit;
        ThePHSensor.PrintPHToLCD(tdsVal, tempF);


        //CmdMessengerExt::Loop();

        //if(millis() >= 44400000) { //reset every 6 hours. 21600000
        //
        ////Serial.print(F("Reseting Arduino: "));
        ////Serial.println(millis());
        //delay(100);
        //resetFunc(); //call reset
        //}
        delay(60); //give a little time to complete processing..
    }

    void AsyncDoWork() {

        wdt_reset();

        //Serial.print("WakeDurr: ");
        //Serial.println(TdsSensorRun.WakeDurration);

        //Serial.print(F("millis: "));
        //Serial.println(millis());

        static unsigned long lastSensorReadTime = millis();

        if(TheLCD.DetectKeyPress() == LcdKeyPress::Select) {
            Serial.println(F("[Selelct] Pressed"));
            SwitchSensors();
            lastSensorReadTime = millis();
        }
        SensorReadDuration = millis() - lastSensorReadTime;

        WaterSensorWire::Loop();

        if(SensorReadDuration > SensorReadInterval) {

            SwitchSensors();
            lastSensorReadTime = millis();
        }

        if(!ReadingTDS) {
            ThePHSensor.CalculatePH();
        }
        else {
            //TheTDSSensor.CalculateTDS();
        }


        TheRODoser.Run(TheTDSSensor.TdsVal);

        //WaterSensorWire::Scan();
        //WaterSensorWire::I2C_ClearBus();
    }
    void TDSSensorRun_Start() {
        TheTDSSensor.StartReading();

    }
    void TDSSensorRun_Stop() {
        TheTDSSensor.StopReading();
    }

    void SwitchSensors() {
        Serial.println(F("Switching Sensors.."));

        ReadingTDS = !ReadingTDS;

        if(!ThePHSensor.Enabled) {
            ReadingTDS = true;
        }

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

