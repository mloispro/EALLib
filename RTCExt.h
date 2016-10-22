// SerialExt.h

#ifndef RTCEXT_h
#define RTCEXT_h

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <string>
#include <vector>


#include <Wire.h>
#include <TimeLib.h>
#include <Time.h>
#include <DS3232RTC.h>
#include <EEPROM.h>

//#include "EEPRomMem.h"

#include "_globals.h"
#include "MemoryExt.h"
#include "SerialExt.h"
#include "DigitalTime.h"
#include "LCDMenu.h"

using namespace std;

using namespace Utils;

using namespace Models;
using namespace TimeHelpers;
using namespace LCD;


namespace Utils {
    using namespace MemoryExt;

    ////remeber: dependant functions must be defined first in namespace.
    ///**Better to use template functions.
    namespace RTCExt {

        //static NextRunMemory NextFeedInfo;
        //static NextRunMemory NextDoseInfo;
        static MemoryContainer _memoryContainer;

        //static only sticks local
        static tmElements_t _timeBuffer;
        //static tmElements_t _nextRunBuffer;


        template<typename T = void>
        long GetRTCTime() {
            return now();
        }
        template<typename T = void>
        void SetRTCTime(int theHour, int theMinute, int theSecond, int theDay, int theMonth, int theYear) {
            //23h31m30s on 13Feb2009
            //setTime(8, 22, 00, 28, 2, 2016);
            setTime(theHour, theMinute, theSecond, theDay, theMonth, theYear);
            //#if !DEBUG
            RTC.set(now());

            //RTCExt::Init();
            //#endif
            //tmElements_t tm;
            //tm.Hour = theHour;
            //tm.Minute = theMinute;
            //tm.Day = theDay;
            //tm.Month = theMonth;
            //tm.Year = theYear;
            //time_t t = makeTime(tm);
            //RTC.set(t);
        }
        template<typename T = void>
        void Init() {
            //#if !DEBUG
            setSyncProvider(RTC.get);   // the function to get the time from the RTC
            //#endif

            if(timeStatus() != timeSet) {
                SerialExt::Print(F("Unable to sync with the RTC, time not set."));
            }
            else {
                String digitalTime = GetDigitalTimeString(GetRTCTime(), false);
                SerialExt::Print(F("RTC Initialized: "), digitalTime);
                //_initalized = true;
            }
            delay(200);//wait for rtc

            //LoadNextRunInfos();
        }

        /*template<typename T = void>
        void SetDefaultRTCTime()
        {
        	SetRTCTime(1, 1, 1, 1, 1, 2000);
        }
        template<typename T = void>
        bool IsDefaultRTCTime()
        {
        	time_t rtcTime = GetRTCTime();
        	int y = year(rtcTime);
        	int m = month(rtcTime);
        	int d = day(rtcTime);
        	int h = hour(rtcTime);
        	if (y == 2000 && m == 1 && d == 1 && h == 1)
        		return true;

        	return false;

        }*/
        template<typename T = void>
        bool IsRTCTimeSet() {
            auto time = GetRTCTime();
            auto theYear = year(time);
            //SerialExt::Debug("theYear", theYear);
            if(theYear >= 2016) {
                return true;
            }
            else {
                return false;
            }
        }
        //loads collection from eeprom
        template<typename T = void>
        void LoadNextRunInfos(AccessoryType accType) {
            //int accTypeFeed = static_cast<int>(AccessoryType::Feeder);
            //int accTypeDoser = static_cast<int>(AccessoryType::DryDoser);

            NextRunMemory mem;
            mem.AccType = accType;
            NextRunMemory newMem = MemoryExt::GetNextRunMem(mem);
            //mem = MemoryExt::GetNextRunMem(mem);
            if(!_memoryContainer.NextRunInfoExists(accType)) {
                _memoryContainer.AddNextRunInfo(newMem);
            }

        }
        template<typename T = void>
        void ClearNextRunInfos() {
            _memoryContainer.ClearNextRunInfos();
        }
        template<typename T = void>
        NextRunMemory & SaveNextRunInfos(AccessoryType accType) {
            //int accTypeFeed = static_cast<int>(AccessoryType::Feeder);
            //int accTypeDoser = static_cast<int>(AccessoryType::DryDoser);

            NextRunMemory mem;
            //mem.Pin = pin;
            mem.AccType = accType;
            NextRunMemory newMem = MemoryExt::SaveNextRunMem(mem);
            if(!_memoryContainer.NextRunInfoExists(accType)) {
                _memoryContainer.AddNextRunInfo(newMem);
            }

            return newMem;
        }
        template<typename T = AccessoryType>
        NextRunMemory & FindNextRunInfo(T && accType) {
            NextRunMemory& mem = _memoryContainer.FindNextRunInfo(accType);
            return mem;
        }

        template<typename T = AccessoryType, typename S = bool>
        NextRunMemory & RefreshNextRunInfo(T && accType, S && forceSave) {

            NextRunMemory& nextRunMem = _memoryContainer.FindNextRunInfo((AccessoryType)accType);

            if(!forceSave && !nextRunMem.Enabled) {
                return nextRunMem;
            }

            auto rtcTime = GetRTCTime();
            long runEvery = nextRunMem.RunEvery;
            long countDown = nextRunMem.CountDown;
            long nextRun = nextRunMem.NextRun;
            long lastRun = nextRunMem.LastRun;


            //auto rtc1 = GetShortDateTimeString(rtcTime, true);
            //auto nr1 = GetShortDateTimeString(nextRun, true);
            //auto cd1 = GetTimeRemainingString(countDown, true);
            //auto re1 = GetTimeRemainingString(runEvery, true);

            if(!IsRTCTimeSet() || runEvery == 0) {
                return nextRunMem;    // rtcTime;
            }

            if(lastRun == 0) { //before first feeding
                lastRun = rtcTime;
            }

            if(lastRun > rtcTime) {
                lastRun = rtcTime;
                nextRun = 0;
            }

            if(nextRun <= 0) {
                nextRun = rtcTime + runEvery;    //08:51:49
            }

            if(lastRun > 0 && nextRun <= rtcTime) {
                nextRun = lastRun + runEvery;
            }

            countDown = nextRun - rtcTime; //00:00:06

            if(nextRun <= rtcTime) {
                nextRun = rtcTime;
                countDown = 0;
            }


            //auto nr2 = GetShortDateTimeString(nextRun, true);
            //auto cd2 = GetTimeRemainingString(countDown, true);
            //auto re2 = GetTimeRemainingString(runEvery, true);

            nextRunMem.RunEvery = runEvery;
            nextRunMem.CountDown = countDown;
            nextRunMem.NextRun = nextRun;
            nextRunMem.LastRun = lastRun;

            if(forceSave) {
                nextRunMem.LastSave = 0;
            }

            //save every 15 min. 900 sec
            long saveTime = nextRunMem.LastSave + 900;
            if(saveTime <= rtcTime) {
                //SaveNextRunInfo(accType);
                int accTypeInt = static_cast<int>(accType);
                nextRunMem.AccType = accTypeInt;
                nextRunMem = MemoryExt::SaveNextRunMem(nextRunMem);
            }

            return nextRunMem;
        }
        template<typename T = AccessoryType>
        NextRunMemory & RefreshNextRunInfo(T && accType) {
            RefreshNextRunInfo(accType, false);
        }



        template<typename T = void>
        bool IsTimeToRun(AccessoryType accType) {
            NextRunMemory& mem = RefreshNextRunInfo(accType);

            if(!mem.Enabled) {
                return false;
            }
            if(mem.RunEvery <= 0) {
                return true;    //not using rtc
            }

            time_t runTime = RTCExt::GetRTCTime();

            time_t nextRun = mem.NextRun;
            //int runTime = TimerExt::GetRuntimeInSeconds();
            if(nextRun <= runTime) {
                return true;
            }
            return false;
        }
        template<typename T = void>
        bool IsAccEnabled(AccessoryType accType) {
            NextRunMemory& mem = RefreshNextRunInfo(accType);
            return mem.Enabled;
        }
        template<typename T = long, typename N = long>
        String GetTimeFrequencyString(T && runEvery, N && nextRun) {
            String freq = "";

            String am = F("AM");
            if(isPM(nextRun)) {
                am = F("PM");
            }

            String theTime = GetDigitalTimeString(nextRun, false);
            theTime = theTime + am;

            int h = ConvSecToHour(runEvery);

            if(h == 24) {
                freq = F(", Daily");
            }
            else if(h == 48) {
                freq = F(", Every Other Day");
            }
            else if(h == 168) {
                freq = F(", Weekly");
            }
            else if(h == 336) {
                freq = F(", Every 2 Weeks");
            }
            else if(h == 504) {
                freq = F(", Every 3 Weeks");
            }
            else if(h == 672) {
                freq = F(", Monthly");
            }

            String freqTime = theTime + freq;
            return freqTime;
        }

        template<typename T = long, typename M = AccessoryType>
        void SetRunEvery(T && hour, M && accType) {
            T t(hour);
            long sec = ConvHoursToSec(hour);
            NextRunMemory& nextRunMem = RefreshNextRunInfo(accType);

            nextRunMem.RunEvery = sec;
            nextRunMem.NextRun = 0; //need to set to 0 so it recalculates

            RefreshNextRunInfo(accType, true);
        }
        template<typename T = long, typename M = AccessoryType>
        void SetRunEverySeconds(T && seconds, M && accType) {
            T t(seconds);
            //long sec = second(seconds);
            NextRunMemory& nextRunMem = RefreshNextRunInfo(accType);

            nextRunMem.RunEvery = seconds;
            nextRunMem.NextRun = 0; //need to set to 0 so it recalculates

            RefreshNextRunInfo(accType, true);
        }
        template<typename T = AccessoryType>
        int GetRunEvery(T && accType) {

            NextRunMemory& mem = RefreshNextRunInfo(accType);
            int shakes = mem.RunEvery;
            return shakes;
        }
        template<typename T = int, typename M = AccessoryType>
        void SetMotorShakesOrTurns(T && shakesOrTurns, M && accType) {

            NextRunMemory& mem = RefreshNextRunInfo(accType);
            mem.ShakesOrTurns = shakesOrTurns;
            RefreshNextRunInfo(accType, true);
        }
        template<typename T = AccessoryType>
        int GetShakesOrTurns(T && accType) {

            NextRunMemory& mem = RefreshNextRunInfo(accType);
            int shakes = mem.ShakesOrTurns;
            return shakes;
        }
        template<typename T = void>
        void SetRTCTimeFromTemp() {
            SetRTCTime(_timeBuffer.Hour, _timeBuffer.Minute, _timeBuffer.Second, _timeBuffer.Day, _timeBuffer.Month, _timeBuffer.Year);
        }

        template<typename T = void>
        void ClearTimeTemp() {
            _timeBuffer.Hour = 0;
            _timeBuffer.Minute = 0;
            _timeBuffer.Second = 0;
            _timeBuffer.Day = 0;
            _timeBuffer.Month = 0;
            _timeBuffer.Year = 0;
            _timeBuffer.Wday = 0;
        }

        template<typename T, typename M = RangeType>
        void SetTimeTemp(T && val, M && rangeType) {
            T t(val);

            if(rangeType == RangeType::Year) {
                ClearTimeTemp();
                _timeBuffer.Year = val;
            }
            else if(rangeType == RangeType::Month) {
                _timeBuffer.Month = val;
            }
            else if(rangeType == RangeType::Day) {
                _timeBuffer.Day = val;
            }
            else if(rangeType == RangeType::Hour) {
                _timeBuffer.Hour = val;
            }
            else if(rangeType == RangeType::Minute) {
                _timeBuffer.Minute = val;
            }
            else if(rangeType == RangeType::AmPm) {
                if(val == 0) { // val = 0->AM
                    if(_timeBuffer.Hour == 12) { //midnight
                        _timeBuffer.Hour = 0;
                    }
                }
                else if(val == 1) { // val = 1->PM
                    if(_timeBuffer.Hour < 12) { //pm
                        _timeBuffer.Hour += 12;
                    }
                }
            }
        }



        template<typename T, typename M = RangeType, typename P = AccessoryType>
        void SetNextRun(T && val, M && rangeType, P && accType) {
            T t(val);
            M m(rangeType);
            P p(accType);

            if(rangeType == RangeType::Hour) {
                ClearTimeTemp();
                _timeBuffer.Hour = val;
            }
            else if(rangeType == RangeType::Minute) {
                _timeBuffer.Minute = val;
            }
            else if(rangeType == RangeType::AmPm) {

                NextRunMemory& nextRunMem = RefreshNextRunInfo(accType);

                //next run in seconds.
                long nrSecs = nextRunMem.NextRun;

                if(val == 1) { //pm
                    _timeBuffer.Hour = _timeBuffer.Hour + 12;
                }

                int y = year(nrSecs);
                _timeBuffer.Year = CalendarYrToTm(y);
                _timeBuffer.Month = month(nrSecs);
                _timeBuffer.Day = day(nrSecs);
                _timeBuffer.Second = second(nrSecs);

                //meridian is last step so update time
                time_t newNrTime = makeTime(_timeBuffer);

                nextRunMem.NextRun = newNrTime;
                nextRunMem.LastRun = -1; //force recalculate
                RefreshNextRunInfo(accType, true);
            }
            else if(rangeType == RangeType::RunNow) {
                NextRunMemory& nextRunMem = RefreshNextRunInfo(accType);

                if(!nextRunMem.Enabled) { //acc not enabled so dont run.
                    return;
                }

                nextRunMem.NextRun = RTCExt::GetRTCTime();
                nextRunMem.LastRun = -1; //force recalculate
                RefreshNextRunInfo(accType, true);
            }
            else {
                return;
            }


        }
        //template<typename P = AccessoryType>
        //void SetLastRun(P && accType) {
        //NextRunMemory& nextRunMem = FindNextRunInfo(accType);
        //nextRunMem.LastRun = GetRTCTime();
        //UpdateNextRun(accType);
        //}
        template<typename T = void>
        String GetRTCTimeString() {
            auto rtcTime = GetRTCTime();
            auto digTime = TimeHelpers::GetTimeString(rtcTime, true);
            //auto timeString = Time::FormatDigialTime(digTime.Hours, digTime.Minutes, digTime.Seconds, true);
            return digTime;
        }
        template<typename T = void>
        String GetRTCDateTimeString() {
            auto rtcTime = GetRTCTime();
            auto timeString = TimeHelpers::GetShortDateTimeString(rtcTime, false);
            return timeString;
        }

        template<typename T = void>
        bool IsDayTime() {
            time_t rtcTime = GetRTCTime();
            int theHour = hourFormat12(rtcTime);
            bool am = isAM(rtcTime);
            if(am && theHour > 8) {
                return true;
            }
            else if(theHour = 12 || theHour < 9) {
                return true;
            }
            return false;
        }
    }
    //extern MemoryContainer RTCExt::_memoryContainer;
}
//extern Models::NextRunMemory Utils::RTCExt::NextDoseInfo;
//extern Models::NextRunMemory Utils::RTCExt::NextFeedInfo;


#endif

