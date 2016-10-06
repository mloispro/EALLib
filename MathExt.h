
#ifndef MATHEXT_h
#define MATHEXT_h

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
using namespace std;



////remeber: dependant functions must be defined first in namespace.
///**Better to use template functions.
namespace MathExt {
    extern float RandomFloat(float a, float b);
    extern double GetAverage(vector<double> vec);

    extern double GetStdDeviation(vector<double> vec, double mean);
    extern double CalculateAverage(int* arr, int number);

    ////use debug prints for debug statements that should be removed, after debugging.
    //template<typename T, typename F>
    //extern void Debug(T&& text, F&& val) {

    ////auto msg = "~ " + text + ": " + val;
    //String msg = String("~ ") + text;
    //Serial.print(msg + ": ");
    //Serial.println(val);
    //Serial.flush();
    //}


}




#endif

