// FishFeeder.h

#ifndef _FISHFEEDER_h
#define _FISHFEEDER_h

#include <Arduino.h>

#include "Servo.h"
#include "ServoMotor.h"

//#include "StandardCplusplus.h"
//#include "vector"

//#include <stl_vector.h>
#include <vector>

#include "_globals.h"
#include "SerialExt.h"
using namespace Globals;
using namespace Utils;

using namespace std;


class FishFeeder : public ServoMotor {

  private:
    void Feed();

  public:
    FishFeeder();
    FishFeeder(Servo servo, int pin, int shakes, long runEverySeconds, bool enabled);
    FishFeeder(Servo servo, int pin, int shakes, short relayPin, long runEverySeconds, bool enabled);
    static vector<FishFeeder> CreateFeeders(int numOfFeeders, int startingPin, bool enabled);
    static void FeedAll(vector<FishFeeder> feeders, int potVal);
    static void RunDemo(vector<FishFeeder> feeders);
    static FishFeeder CreateFeeder(int pin, short shakes, long runEvery, bool enabled);
    static void FeedAll(vector<FishFeeder> feeders);
};

//vector<FishFeeder> FishFeeder::Feeders;

//extern FishFeederClass FishFeeder;

#endif

