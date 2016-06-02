
#include "RODoser.h"

RODoser::RODoser(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 14, relayPin, runEverySeconds, theSwitch, AccessoryType::DryDoser, enabled) {
}

RODoser::RODoser(Servo servo, int pin, int shakes, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 14, -1, runEverySeconds, theSwitch, AccessoryType::DryDoser, enabled) {
}

RODoser::RODoser() {
    ServoType = AccessoryType::DryDoser;
}

void RODoser::Dose() {
    _theSpeed = 10;
    Run();
}

void RODoser::RunDemo(vector<RODoser> dosers) {

    //vector<ServoMotor> motors;
    //copy(dosers.begin(), dosers.end(), back_inserter(motors));
    //ServoMotor::RunMotorDemos(motors);

}
