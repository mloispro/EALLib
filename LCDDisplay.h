/*
* DumbFucker.h
*
* Created: 5/27/2016 1:02:33 PM
* Author: lenovo
*/


#ifndef __LCDDISPLAY_H__
#define __LCDDISPLAY_H__
#include <Arduino.h>

#include <StandardCplusplus.h>
#include <vector>
#include <string>
using namespace std;

#include <Wire.h>
#include <TimeLib.h>
#include <Time.h>
#include <DS3232RTC.h>
#include <LiquidCrystal.h>
#include <SimpleTimer.h>

#include "_globals.h"
using namespace Globals;
#include "SerialExt.h"
#include "LCDMenu.h"
#include "DigitalTime.h"
#include "RTCExt.h"
using namespace Utils;
using namespace TimeHelpers;
using namespace Globals;

#define MENUITEMS 100

namespace LCD {

    class LCDDisplay {

        public:
        protected:
        private:
            const int mainMenu = 0;
            const int feedMenu = 1;
            const int feedFreqMenu = 2;
            const int feedHourMenu = 3;
            const int feedMinMenu = 4;
            const int feedAmPmMenu = 5;
            const int clockMenu = 6;
            const int clockYearMenu = 7;
            const int clockMonthMenu = 8;
            const int clockDayMenu = 9;
            const int feedTimeMenu = 10;
            const int clockHourMenu = 11;
            const int clockMinMenu = 12;
            const int clockAmPmMenu = 13;
            const int doserMenu = 14;
            const int doserFreqMenu = 15;
            const int doserHourMenu = 16;
            const int doserMinMenu = 17;
            const int doserAmPmMenu = 18;
            const int doserTimeMenu = 19;
            const int feedShakesMenu = 20;
            // const int feedSetShakesMenu = 21; open
            const int doserShakesMenu = 22;
            // const int doserSetShakesMenu = 23; open
            // const int settingsMenu = 24; open
            const int feedEnableMenu = 25;
            const int doserEnableMenu = 26;
            const int feedNowMenu = 27;
            const int doseNowMenu = 29;
            const int pumpMenu = 30;
            const int pumpEnableMenu = 31;
            const int pumpFreqMenu = 32;
            const int pumpHourMenu = 33;
            const int pumpMinMenu = 34;
            const int pumpAmPmMenu = 35;
            const int pumpTimeMenu = 36;
            const int pumpNowMenu = 37;
            const int pumpRunMinutesMenu = 38;
            const int microsMenu = 39;
            const int microsEnableMenu = 40;
            const int microsFreqMenu = 41;
            const int microsHourMenu = 42;
            const int microsMinMenu = 43;
            const int microsAmPmMenu = 44;
            const int microsTimeMenu = 45;
            const int microsNowMenu = 46;
            const int microsRunMinutesMenu = 47;

            short _menuIndex = 0;
            char* _mainMenuText = "";

            //lcd text scroll left
            short _scrollIndex;
            int _scrollDelay = 3000;

            int _selectDelay = 2000;

            int _menusIndex = 0;
            //vector<LCDMenu> _menus;
            LCDMenu _menus[MENUITEMS];

            //String _selectedText;
            short _selectedMenuId = -1;
            short _selectedOptionId = -1;
            int _optionCount;
            short _prevMenuId;

            int _lowerLimit;
            int _upperLimit;

            //--key press
            // int _keyValues[5] = { 50, 200, 400, 600, 800 };
            static int  _keyValues[5];
            static short _numOfKeys;

            bool _optionChanged;
            //static String _menuText;
            String _optionText;
            String _menuText;
            long _menuTimeout = 0;
            bool _loadedOptionFromMem;
            //char const n[3]{'a', 'b', 'c'};
            //LiquidCrystal _lcd;
            //bool _optionChanged = false;

            //SimpleTimer _scrollRightTimer;
            //int _scrollRightTimerId = 0;
            LiquidCrystal _lcd;
        public:

            LCDDisplay(): _lcd(8, 9, 4, 5, 6, 7) {};

            void Init();

            String GetRangeOption(RangeType rangeType, Globals::AccessoryType accType);
            //template<typename R = RangeType, typename A = Globals::AccessoryType>
            //String GetRangeOption(R& rangeType, A& accType);
            void SaveRangeOption(RangeType rangeType, AccessoryType accType);

            static int GetKey();
            void SelectMainMenu();
            void ExitMainMenu();

            void PrintRunInfo(NextRunMemory& nextRunMem);
            void PrintTime();
            void Scroll();

            String GetTimeFrequency(AccessoryType accType);
            String GetTimeLong(AccessoryType accType);

        protected:
        private:
            LCDDisplay(const LCDDisplay& c);
            LCDDisplay& operator=(const LCDDisplay& c);

            static int GetKeyFromVal(unsigned int input);
            void NextOption();
            void PreviousOption();
            void LeftButton();
            void SelectButton();
            void LimitRange(int lower, int upper);
            void DetectKeyPress();

            LCDMenu GetMenu(short id, short optionId);
            void PrintMenu(LCDMenu menu);
            void PrintLine(short lineNum, String text);
            void SetSelectedMenu(LCDMenu menu);
            //
            void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, char* text, char* optionText, RangeType rangeType);
            void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, char* text, char* optionText, RangeType rangeType, AccessoryType accType);
            void CreateMenus();
            LCDMenu GetSelectedMenu();
            void SetClockMenu();

            template<typename T>
            String GetOptionAsNumber(T&& defaultNumber, bool isTwoDigits);
            template<typename T>
            String GetOptionAsNumber(T&& defaultNumber);

            String GetOnOff(AccessoryType accType);
            void SetOnOff(AccessoryType accType);
            String GetRunDurration(AccessoryType accType);
            void SetRunDurration(AccessoryType accType);

            void AddMenu(AccessoryType accType);
            void PrintInstructions();
            void IsKeyPressed();
            void HandleScrollText(short lineNum, String text);
            String LoadAccOption(LCDMenu menu);
            String loadShakesTurnsOption(LCDMenu menu);
            String loadRunNowOption(LCDMenu menu);
            void PrintDisabledAcc(NextRunMemory& feederNextRunMem, NextRunMemory& doserNextRunMem, NextRunMemory& pumpNextRunMem, NextRunMemory& microsNextRunMem);

    }; //LCDDisplay

}
#endif
