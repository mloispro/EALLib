// SerialExt.h

#ifndef DIGITALTIME_h
#define DIGITALTIME_h

#include <Arduino.h>

//#include <StandardCplusplus.h>
//#include <string>
//#include <vector>

#include <Wire.h>
#include <Time.h>
//#include <TimeLib.h>

//#include "C:\Users\lenovo\Documents\Arduino\libraries\Time\Time.h"
//#include "C:\Users\lenovo\Documents\Arduino\libraries\Time\TimeLib.h"
//#include "Wire.h"
//#include "SerialExt.h"

using namespace std;

namespace Models {

    //template<class T>
    class DigitalTime {

      public:
        int Hours;
        int Minutes;
        int Seconds;

        DigitalTime(int hours, int minutes, int seconds) : Hours(hours), Minutes(minutes), Seconds(seconds) {}
    };
}

namespace TimeHelpers {
    using namespace Models;

    template<typename H = int, typename M = int, typename S = int, typename I = bool>
    String FormatDigialTime(H && hours, M && minutes, S && seconds, I && includeSeconds) {

        String hourString = String(hours);
        if(hours < 10)
            hourString = "0" + hourString;
        String minString = String(minutes);
        if(minutes < 10)
            minString = "0" + minString;

        String timeString = hourString + ":";
        timeString += minString; //+":";

        if(includeSeconds) {
            String secString = String(seconds);
            if(seconds < 10)
                secString = "0" + secString;
            timeString = timeString + ":" + secString;
        }

        return timeString;
    }
    template<typename M = int, typename S = int>
    String FormatMinutesSeconds(M && minutes, S && seconds) {

        String minString = String(minutes) + "m";
        if(minutes < 10)
            minString = "0" + minString;

        String timeString = minString;
        // timeString += minString; //+":";


        String secString = String(seconds) + "s";
        if(seconds < 10)
            secString = "0" + secString;

        timeString = timeString + ":" + secString;


        return timeString;
    }
    template<typename T = DigitalTime, typename I = bool>
    String FormatDigialTime(T && time, I && includeSeconds) {

        String timeString = FormatDigialTime(time.Hours, time.Minutes, time.Seconds, includeSeconds);

        return timeString;
    }
    template<typename T = time_t>
    DigitalTime GetDigitalTime(T && seconds) {

        int h, m, s;
        s = second(seconds); //seconds;
        m = minute(seconds);
        h = hourFormat12(seconds);

        DigitalTime time = DigitalTime(h, m, s);

        return time;
    }
    template<typename T = time_t>
    String GetMinutesSecondsString(T && seconds) {

        DigitalTime time = GetDigitalTime(seconds);

        String runTime = FormatMinutesSeconds(time.Minutes, time.Seconds);
        return runTime;
    }
    template<typename T = time_t, typename I = bool>
    String GetDigitalTimeString(T && seconds, I && includeSeconds) {

        DigitalTime time = GetDigitalTime(seconds);

        String runTime = FormatDigialTime(time, includeSeconds);
        return runTime;
    }

    template<typename T = time_t, typename I = bool>
    String GetTimeString(T && seconds, I && includeSeconds) {


        DigitalTime time = GetDigitalTime(seconds);

        String runTime = FormatDigialTime(time.Hours, time.Minutes, time.Seconds, includeSeconds);
        return runTime;
    }

    template<typename T = time_t>
    String GetMonthAndDateString(T && seconds) {


        String theDate;

        int theDay = day(seconds);
        int theMonth = month(seconds);
        int theYear = year(seconds);

        //SerialExt::Debug("theDay", theDay);

        String dayString = String(theDay);
        if(theDay < 10)
            dayString = "0" + dayString;
        String monthString = String(theMonth);
        if(theMonth < 10)
            monthString = "0" + monthString;
        String yearString = String(theYear);
        yearString.remove(0, 2);

        theDate = monthString + "/" + dayString + "/" + yearString;

        return theDate;
    }
    //returns digital date & time ##/##/#### ##:##:##
    template<typename T = time_t, typename I = bool>
    extern String GetShortDateTimeString(T && seconds, I && includeSeconds) {


        String result;

        String theDate = GetMonthAndDateString(seconds);
        String theTime = GetDigitalTimeString(seconds, includeSeconds);

        result = theDate + " " + theTime;

        String am = F("AM");
        if(isPM(seconds))
            am = F("PM");

        result += am;

        return result;

    }
    template<typename T = void>
    long ConvHoursToSec(int hour) {
        //T t(hour);
        long sec = (long)(hour * SECS_PER_HOUR);
        return sec;
    }
    template<typename T = void>
    int ConvSecToHour(long seconds) {
        //T t(hour);
        int h = (int)(seconds / SECS_PER_HOUR);
        return h;
    }
    template<typename T = time_t>
    DigitalTime GetTimeRemaining(T && seconds) {


        int h, m;
        m = seconds / SECS_PER_MIN;
        h = seconds / SECS_PER_HOUR;
        auto min = fmod(m, 60);

        int s = second(seconds);

        DigitalTime time = DigitalTime(h, min, s);

        return time;
    }
    template<typename T = long, typename I = bool>
    String GetTimeRemainingString(T && seconds, I && includeSeconds) {


        DigitalTime time = GetTimeRemaining(seconds);
        auto timeString = FormatDigialTime(time.Hours, time.Minutes, time.Seconds, includeSeconds);
        return timeString;
    }

}

#endif

