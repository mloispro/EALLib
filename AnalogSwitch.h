#ifndef ANALOGSWITCH_h
#define ANALOGSWITCH_h

#include <Arduino.h>
#include "SerialExt.h"
using namespace Utils;

//#include "SerialExt.h"
namespace Models {
    class AnalogSwitch {
        public:
            short AnalogPin = -1;
            int Max = 1023;
            int SwitchReading;
            AnalogSwitch(short analogPin, int max);
            AnalogSwitch(short analogPin);
            AnalogSwitch();
            bool IsOn();
            void Init();
    };
}
//namespace Utils {
//	namespace AnalogSwitch{
//		//using namespace Utils;
//		bool IsOn(int analogPin, int max){
//			//read switch
//			int switchReading = analogRead(analogPin);
//			SerialExt::Print("Switch Val: ", switchReading);
//			if (switchReading > max - 50){
//				return true;
//			}
//			return false;
//		}
//
//	}
//}

#endif

