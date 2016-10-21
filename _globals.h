
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <StandardCplusplus.h>
#include <vector>
#include <string>
using namespace std;



namespace Globals {
    enum AccessoryType : int {
        None,
        Clock,
        Feeder,
        LiqDoser,
        DryDoser,
        WaterPump,
        Lcd,
        ROWaterPump
    };

}



namespace MegaPins {
    const int PWM_2 = 2;
    const int PWM_3 = 3;
    const int PWM_4 = 4;
    const int PWM_5 = 5;
    const int PWM_6 = 6;
    const int PWM_7 = 7;
    const int PWM_8 = 8;
    const int PWM_9 = 9;
    const int PWM_10 = 10;
    const int PWM_11 = 11;
    const int PWM_12 = 12;
    const int PWM_13 = 13;
    const int PWM_44 = 44;
    const int PWM_45 = 45;
    const int PWM_46 = 46;

    //analog pins
    const int A_0 = 0;
    const int A_1 = 1;
    const int A_2 = 2;
    const int A_3 = 3;
    const int A_4 = 4;
    const int A_5 = 5;
    const int A_6 = 6;
    const int A_7 = 7;
    const int A_8 = 8;
    const int A_9 = 9;
    const int A_10 = 10;
    const int A_11 = 11;
    const int A_12 = 12;
    const int A_13 = 13;
    const int A_14 = 14;
    const int A_15 = 15;

    //communication
    const int SDA_20 = 20;
    const int SCL_21 = 21;


}
namespace UnoPins {
    const int PWM_3 = 3;
    const int PWM_5 = 5;
    const int PWM_6 = 6;
    const int PWM_9 = 9;
    const int PWM_10 = 10;
    const int PWM_11 = 11;
    const int PWM_13 = 13;
}
namespace LCDPins {

    // LCD Analog Pins: A1, A2, A3, A4, A5
    const int A_1 = 1;
    const int A_2 = 2;
    const int A_3 = 3;
    const int A_4 = 4;
    const int A_5 = 5;

    // LCD Analog or Digital Pins: 15, 16, 17, 18, 19
    const int AD_1 = 15;
    const int AD_2 = 16;
    const int AD_3 = 17;
    const int AD_4 = 18;
    const int AD_5 = 19;

    // LCD Digital Pins: 0, 1, 2, 3, 11, 12, 13
    const int D_1 = 1;
    const int D_2 = 2;
    const int D_3 = 3;
    const int D_11 = 11;
    const int D_12 = 12;
    const int D_13 = 13;

}



#endif /* _GLOBALS_H_ */