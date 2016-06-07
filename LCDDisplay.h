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

namespace LCD {

    class LCDDisplay {

      public:
      protected:
      private:
        static const short mainMenu = 0;
        static const short feedMenu = 1;
        static const short feedFreqMenu = 2;
        static const short feedHourMenu = 3;
        static const short feedMinMenu = 4;
        static const short feedAmPmMenu = 5;
        static const short clockMenu = 6;
        static const short clockYearMenu = 7;
        static const short clockMonthMenu = 8;
        static const short clockDayMenu = 9;
        static const short feedTimeMenu = 10;
        static const short clockHourMenu = 11;
        static const short clockMinMenu = 12;
        static const short clockAmPmMenu = 13;
        static const short doserMenu = 14;
        static const short doserFreqMenu = 15;
        static const short doserHourMenu = 16;
        static const short doserMinMenu = 17;
        static const short doserAmPmMenu = 18;
        static const short doserTimeMenu = 19;
        static const short feedShakesMenu = 20;
        static const short feedSetShakesMenu = 21;
        static const short doserShakesMenu = 22;
        static const short doserSetShakesMenu = 23;
        static const short settingsMenu = 24;
        static const short feedEnableMenu = 25;
        static const short doserEnableMenu = 26;
        static const short feedNowMenu = 27;
        static const short doseNowMenu = 29;
        static const short pumpMenu = 30;
        static const short pumpEnableMenu = 31;

        short _menuIndex = 0;
        String _mainMenuText = "";

        short _scrollIndex;
        int _scrollDelay = 3000;

        int _selectDelay = 2000;

        vector<LCDMenu> _menus;
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
        //char const n[3]{'a', 'b', 'c'};
        //LiquidCrystal _lcd;
        //bool _optionChanged = false;

        //SimpleTimer _scrollRightTimer;
        //int _scrollRightTimerId = 0;
        LiquidCrystal _lcd;
      public:

        LCDDisplay(): _lcd(8, 9, 4, 5, 6, 7) {};

        void Init();

        String GetRangeOption(LCDMenu::RangeType rangeType, AccessoryType accType);
        void SaveRangeOption(LCDMenu::RangeType rangeType, AccessoryType accType);

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
        void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, LCDMenu::RangeType rangeType);
        void AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, LCDMenu::RangeType rangeType, AccessoryType accType);
        void CreateMenus();
        LCDMenu GetSelectedMenu();
        void SetClockMenu();

        template<typename T>
        String GetOptionAsNumber(T&& defaultNumber, bool isTwoDigits);
        template<typename T>
        String GetOptionAsNumber(T&& defaultNumber);

        String GetOnOff(AccessoryType accType);
        void SetOnOff(AccessoryType accType);

        void AddMenu(AccessoryType accType);
        void PrintInstructions();
        void IsKeyPressed();
        void HandleScrollText(short lineNum, String text);
        String GetAccMenuOptionText(LCDMenu& menu);

    }; //LCDDisplay

}
#endif
