
#include "FishFeeder.h"


//FishFeeder::FishFeeder(int pin) : ServoMotor(pin){};
FishFeeder::FishFeeder() {
    MotorType = AccessoryType::Feeder;
}
FishFeeder::FishFeeder(Servo servo, int pin, int shakes, long runEverySeconds, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 14, -1, runEverySeconds, AnalogSwitch(), AccessoryType::Feeder, enabled) {
}
FishFeeder::FishFeeder(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, bool enabled) :
    ServoMotor(servo, pin, shakes, 0, 14, relayPin, runEverySeconds, AnalogSwitch(), AccessoryType::Feeder, enabled) {
}
vector<FishFeeder> FishFeeder::CreateFeeders(int numOfFeeders, int startingPin, bool enabled) {
    vector<FishFeeder> feeders;

    //if(startingPin > 13 || startingPin < 2) {
    ////Serial.println(F("Error: Starting pin has to be less than 14 and greater than 1"));
    //return feeders;
    //}
    if(numOfFeeders > 11) {
        //Serial.println(F("Error: Number of feeders has to be less than 12"));
        return feeders;
    }

    for(int thisFeeder = 0; thisFeeder < numOfFeeders; thisFeeder++) {
        if(startingPin <= 1) return feeders;  //pin 1 and 0 cant be outputs

        // twelve servo objects can be created on most boards
        //FishFeeder feeder(Servo(), 13, 2, 0, 14); //servo, pin, shakes, pos, speed
        FishFeeder feeder = CreateFeeder(startingPin, 2, 86400, enabled); //run every 24hours
        feeders.push_back(feeder);
        startingPin--;
    }
    return feeders;
}
FishFeeder FishFeeder::CreateFeeder(int pin, short shakes, long runEvery, bool enabled) {
    Servo aServo;
    FishFeeder feeder(aServo, pin, shakes, runEvery, enabled); //run every 24hours

    //feeder.Init();
    return feeder;
}


void FishFeeder::FeedAll(vector<FishFeeder> feeders, int potVal) {
    //int shakesVal = GetNumberOfShakes(potVal);
    //digitalWrite(FishFeeder::FeederPwrSigPin, LOW); //to send relay signal

    int feedersSize = feeders.size();
    for(int thisFeeder = 0; thisFeeder < feedersSize; thisFeeder++) {
        FishFeeder feeder = feeders[thisFeeder];
        //feeder.Shakes = shakesVal; //not setting from pot right now.

        SerialExt::Print("Feeder #", thisFeeder + 1, " Feeding..");
        feeder.Run();
    }
    //digitalWrite(FishFeeder::FeederPwrSigPin, HIGH);
}
void FishFeeder::FeedAll(vector<FishFeeder> feeders) {

    int feedersSize = feeders.size();
    for(int thisFeeder = 0; thisFeeder < feedersSize; thisFeeder++) {
        FishFeeder feeder = feeders[thisFeeder];

        //SerialExt::Debug("thisFeeder", thisFeeder);

        feeder.Run();
    }
}


void FishFeeder::RunDemo(vector<FishFeeder> feeders) {

    //vector<ServoMotor> motors;
    //copy(feeders.begin(), feeders.end(), back_inserter(motors));
    //ServoMotor::RunMotorDemos(motors);

}
