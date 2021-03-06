
#include "ServoMotor.h"

//ServoMotor::ServoMotor(Servo servo, int pin, int shakes) :
//	ServoMotor(servo, pin, shakes, 0, 14){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, long runEverySeconds) :
//	ServoMotor(servo, pin, shakes, 0, 14, 0, runEverySeconds){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, AnalogSwitch theSwitch) :
//	ServoMotor(servo, pin, shakes, 0, 14, relayPin, runEverySeconds, theSwitch){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, long runEverySeconds, AnalogSwitch theSwitch) :
//	ServoMotor(servo, pin, shakes, 0, 14, -1, runEverySeconds, theSwitch){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed) :
//	ServoMotor(servo, pin, shakes, pos, theSpeed, 0){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin) :
//	ServoMotor(servo, pin, shakes, 0, 14, relayPin, 0){};
//
//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, short relayPin) :
//	ServoMotor(servo, pin, shakes, 0, 14, relayPin){};

ServoMotor::ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType servoType, bool enabled) :
    Motor(pin, shakes, theSpeed, relayPin, runEverySeconds, theSwitch, servoType, enabled), TheServo(servo), _pos(pos) {

    Init();
}

//ServoMotor::ServoMotor(Servo servo, int pin, int shakes, int pos, int theSpeed, short relayPin, long runEverySeconds, AnalogSwitch theSwitch, AccessoryType servoType, bool enabled) :
//TheServo(servo), TheSwitch(theSwitch), RelayPin(relayPin), _theSpeed(theSpeed), _pin(pin), _pos(pos), MotorType(servoType) {
////TranslateSpeed();
//Init(shakes, runEverySeconds, enabled);
//}
ServoMotor::ServoMotor() {}


void ServoMotor::Init() {

    if(_pos <= 6)
        _pos = 6;
    else if(_pos >= 174)
        _pos = 174;

    TheServo.attach(_pin);
    TheServo.write(_pos);
    delay(200);

}

void ServoMotor::handleRun() {

    //TheServo.detach();
    //while(!TheServo.attached()) { //wait until servo is attached.
    //TheServo.attach(_pin);
    //SerialExt::Print(F("Servo Attached: "), TheServo.attached());
    //delay(100);
    //}

    SerialExt::Print(F("Servo Pin: "), _pin);

    TheServo.write(_pos);
    delay(500);

    int speed =  TranslateSpeed();
    int downAngle = 200;
    //int feedAngle = 180 - _pos;
    //_utils.Debug("FeedAngle: ", feedAngle);
    for(int downPos = _pos; downPos <= downAngle; downPos += 1) {  // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        TheServo.write(downPos);              // tell servo to go to position in variable 'pos'
        delay(speed);                 // waits 15ms for the servo to reach the position
    }
    int shakes = RTCExt::GetShakesOrTurns(MotorType);
    if(shakes > 0) {
        SerialExt::Print(F("Shaking: "), shakes, F(" Times"));
        //delay(4000);
        int shakeCount = 0;
        while(shakeCount < shakes) {
            TheServo.write(downAngle - 120);
            delay(220);
            TheServo.write(downAngle);
            delay(220);

            shakeCount++;
        }
    }
    //SerialExt::Print("Resetting Servo Angle: ", _pos);
    TheServo.write(_pos);
    delay(2200); // wait for servo to get back to 0
    //TheServo.detach();
    //delay(1000);

}


int ServoMotor::GetNumberOfShakes(int potVal) {
    //_utils.Debug("In val: ", val);
    int shakesVal = map(potVal, 0, 1023, 0, 10); // scale it to use it with the servo (value between 0 and 180)
    return shakesVal;

}


int ServoMotor::Calibrate() {
    SerialExt::Debug("Calibrate Servo:");
    SerialExt::Debug("Enter 0 to 180, -1 to exit");

    int degrees;

    while(true) {

        while(Serial.available() == 0);  //pause until data is recieved from computer<-- this line added

        int incomingNum = SerialExt::Read();

        SerialExt::Debug("Entered", incomingNum);

        if(incomingNum == -1)  //not working
            return degrees;

        if(incomingNum <= 6) {
            degrees = 6;
        } else if(incomingNum >= 174) {
            degrees = 174;
        } else {
            degrees = incomingNum;
        }

        SerialExt::Debug("Degrees:", degrees);
        TheServo.write(degrees);
    }


    return degrees;
}
int ServoMotor::TranslateSpeed() {
    int speed = 14;
    if(_theSpeed >= 14) {
        speed = 2;
        return speed;
    }
    switch(_theSpeed) {
        case 13:
            speed = 3;
            break;
        case 12:
            speed = 4;
            break;
        case 11:
            speed = 5;
            break;
        case 10:
            speed = 6;
            break;
        case 9:
            speed = 7;
            break;
        case 8:
            speed = 8;
            break;
        case 7:
            speed = 9;
            break;
        case 6:
            speed = 10;
            break;
        case 5:
            speed = 11;
            break;
        case 4:
            speed = 12;
            break;
        case 3:
            speed = 13;
            break;
        case 2:
            speed = 14;
            break;
        case 1:
            speed = 15;
            break;
        default:
            break;
    }
    return speed;
}
//vector<ServoMotor> Motors;


#pragma region SERIAL_INPUT

//void ServoMotor::RunMotorDemo(Servo myServo) {
//Serial.println(F("Demoing motor.."));
//int pos = 0;
//for(pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
//// in steps of 1 degree
//myServo.write(pos);              // tell servo to go to position in variable 'pos'
//delay(5);                       // waits 15ms for the servo to reach the position
//}
//for(pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
//myServo.write(pos);              // tell servo to go to position in variable 'pos'
//delay(10);                       // waits 15ms for the servo to reach the position
//}
//}
//void ServoMotor::RunMotorDemos(vector<ServoMotor> motors) {
//
//int motorsSize = motors.size();
//for(int thisMotor = 0; thisMotor < motorsSize; thisMotor++) {
//ServoMotor motor = motors[thisMotor];
//Servo aServo = motor.TheServo;
//
//ServoMotor::RunMotorDemo(aServo);
//
//}
//}

////1 to run, 2 to run demo
//bool ServoMotor::ShouldRunMotorBySerialInput(int incomingByte) {
//
//switch(incomingByte) {
//case 1: //1
//return true;
//default:
//return false;
//}
//}
//
////1 to run, 2 to run demo
//bool ServoMotor::ShouldRunMotorDemo(int incomingByte) {
//
//switch(incomingByte) {
//case 2: //2
//return true;
//default:
//return false;
//}
//}

//void ServoMotor::PrintSerialInstructions() {
//Serial.println(F("1 to Run, 2 to Demo."));
//Serial.println(F("3-# to set Shakes, ex: 3-4."));
//
//Serial.print(F("Translated Speed: "));
//Serial.println(_theSpeed);
//
//Serial.print(F("Shakes: "));
//Serial.println(GetShakes());
//
//SerialExt::Print(F("Servo attached to Pin: "), _pin);
//}

//3-6 = 6 shakes, returns true if could process successfully
//bool ServoMotor::ProcessSerialInput(int incomingNum, vector<ServoMotor> motors) {
//bool processed = false;
//int motorsSize = motors.size();
//
//for(int thisMotor = 0; thisMotor < motorsSize; thisMotor++) {
//ServoMotor motor = motors[thisMotor];
//
//processed = motor.ProcessSerialInput(incomingNum);
//
//}
//
//return processed;
//}
//3-6 = 6 shakes, returns true if could process successfully
//bool ServoMotor::ProcessSerialInput(int incomingNum) {
//bool processed;
//
//String inString(incomingNum);
//if(inString.length() > 1 && inString.startsWith("3")) {
////set shakes
//String shakesString = inString.substring(1);
//long shks = shakesString.toInt();
////SerialExt::Debug("shks: ", shks);
//RTCExt::SetShakesOrTurns(shks, ServoType);
//processed = true;
//}
//
//return processed;
//}
#pragma endregion SERIAL_INPUT