
#include "MathExt.h"




////remeber: dependant functions must be defined first in namespace.
///**Better to use template functions.
namespace MathExt {

    ////use debug prints for debug statements that should be removed, after debugging.
    //template<typename T, typename F>
    //extern void Debug(T&& text, F&& val) {

    ////auto msg = "~ " + text + ": " + val;
    //String msg = String("~ ") + text;
    //Serial.print(msg + ": ");
    //Serial.println(val);
    //Serial.flush();
    //}

    //use debug prints for debug statements that should be removed, after debugging.
    //template<typename T, typename F>
    //extern void Debug(T&& text, F&& val) {
    //
    ////auto msg = "~ " + text + ": " + val;
    //String msg = String("~ ") + text;
    //Serial.print(msg + ": ");
    //Serial.println(val);
    //Serial.flush();
    //}
    float RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
    double GetAverage(vector<double> vec) {
        double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
        double mean = sum / vec.size();
        return mean;
    }

    double GetStdDeviation(vector<double> vec, double mean) {
        std::vector<double> diff(vec.size());
        std::transform(vec.begin(), vec.end(), diff.begin(),
                       std::bind2nd(std::minus<double>(), mean));
        double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
        double stdev = sqrt(sq_sum / vec.size());
        return stdev;
    }
    double CalculateAverage(int* arr, int number) {
        int i;
        int max, min;
        double avg;
        long amount = 0;
        if(number <= 0) {
            Serial.println(F("Error number for the array to avraging!/n"));
            return 0;
        }
        if(number < 5) { //less than 5, calculated directly statistics
            for(i = 0; i < number; i++) {
                amount += arr[i];
            }
            avg = amount / number;
            return avg;
        }
        else {
            if(arr[0] < arr[1]) {
                min = arr[0];
                max = arr[1];
            }
            else {
                min = arr[1];
                max = arr[0];
            }
            for(i = 2; i < number; i++) {
                if(arr[i] < min) {
                    amount += min;      //arr<min
                    min = arr[i];
                }
                else {
                    if(arr[i] > max) {
                        amount += max;  //arr>max
                        max = arr[i];
                    }
                    else {
                        amount += arr[i]; //min<=arr<=max
                    }
                }//if
            }//for
            avg = (double)amount / (number - 2);
        }//if
        return avg;
    }

    double CalculateAverage(int16_e* arr, int number) {
        int i;
        int max, min;
        double avg;
        long amount = 0;
        if(number <= 0) {
            Serial.println(F("Error number for the array to avraging!/n"));
            return 0;
        }
        if(number < 5) { //less than 5, calculated directly statistics
            for(i = 0; i < number; i++) {
                amount += arr[i];
            }
            avg = amount / number;
            return avg;
        }
        else {
            if(arr[0] < arr[1]) {
                min = arr[0];
                max = arr[1];
            }
            else {
                min = arr[1];
                max = arr[0];
            }
            for(i = 2; i < number; i++) {
                if(arr[i] < min) {
                    amount += min;      //arr<min
                    min = arr[i];
                }
                else {
                    if(arr[i] > max) {
                        amount += max;  //arr>max
                        max = arr[i];
                    }
                    else {
                        amount += arr[i]; //min<=arr<=max
                    }
                }//if
            }//for
            avg = (double)amount / (number - 2);
        }//if
        return avg;
    }
    String GetTimeIntervalString(long milliseconds) {
        String dateTime = "0s";
        if (milliseconds >= 1000) {
            long seconds = (long) (milliseconds / 1000) % 60;
            auto minutes =  (milliseconds / 1000) / 60;
            auto hours = minutes / 60;
            auto days = hours / 24;

            dateTime = String(seconds) + "s";
            if(minutes <= 0) {
                return dateTime;
            }
            if(minutes >= 60 ) {
                minutes = minutes % 60;
            }
            dateTime = String(minutes) + "m" + dateTime;
            if(hours <= 0) {
                return dateTime;
            }
            if(hours >= 24 ) {
                hours = hours % 24;
            }
            dateTime = String(hours) + "h" + dateTime;
            if(days <= 0) {
                return dateTime;
            }
            dateTime = String(days) + "d" + dateTime;

            //dateTime = String(days) + "d" + String(hours) + "h" + String(minutes) + "m" + String(seconds) + "s";
        }

        return dateTime;
    }
}



