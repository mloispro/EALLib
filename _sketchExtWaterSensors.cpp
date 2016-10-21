
#include "_sketchExtWaterSensors.h"

namespace Sketch {

    void(* resetFunc) (void) = 0;//declare reset function at address 0

    void Setup() {

        wdt_enable(WDTO_8S);

        ThePHSensor.TurnOn();
        WaterSensorWire::Setup();
    }

    void Loop() {

        ThePHSensor.PrintPHToLCD();
        TheTDSSensor.PrintTDSToLCD();

        //CmdMessengerExt::Loop();

        if(millis() >= 44400000) { //reset every 6 hours. 21600000

            //Serial.print(F("Reseting Arduino: "));
            //Serial.println(millis());
            delay(100);
            resetFunc(); //call reset
        }
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
        WaterSensorWire::Loop();
        if(SensorReadDuration > SensorReadInterval) {

            SwitchSensors();
            lastSensorReadTime = millis();
        }
        if(ReadingTDS) {
            TheTDSSensor.CalculateTDS();
        }
        else {
            ThePHSensor.CalculatePH();
        }

        //WaterSensorWire::Scan();
        //WaterSensorWire::I2C_ClearBus();
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

