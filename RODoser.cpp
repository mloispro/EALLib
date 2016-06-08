
#include "RODoser.h"

RODoser::RODoser(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 10, relayPin, runEverySeconds, theSwitch, AccessoryType::DryDoser, enabled) {
}

RODoser::RODoser(Servo servo, int pin, int shakes, long runEverySeconds, AnalogSwitch theSwitch, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 10, -1, runEverySeconds, theSwitch, AccessoryType::DryDoser, enabled) {
}

RODoser::RODoser() {
    MotorType = AccessoryType::DryDoser;
    //_theSpeed = 10;
}


void RODoser::RunDemo(vector<RODoser> dosers) {

    //vector<ServoMotor> motors;
    //copy(dosers.begin(), dosers.end(), back_inserter(motors));
    //ServoMotor::RunMotorDemos(motors);

}
