// SerialExt.h

#ifndef LCDMENU_h
#define LCDMENU_h

#include <Arduino.h>

//#include <StandardCplusplus.h>
//#include <string>
//#include <vector>
using namespace std;
#include "_globals.h"
#include "SerialExt.h"
using namespace Utils;
using namespace Globals;

namespace LCD {



    class LCDMenu {

      public:
        enum RangeType {
            Nav,
            Year,
            Month,
            Day,
            Hour,
            Minute,
            AmPm,
            Frequency,
            TimeLong,
            TimeShort,
            TimeFrequency,
            ShakesOrTurns,
            RunDurration,
            OnOff,
            RunNow
            //DoserOnOff,
            //FeederOnOff
        }; //extern RangeTypeEnum;


        //typedef RangeTypeEnum RangeType;
        //extern RangeTypeEnum RangeTypeEx;

        //RangeType& operator=(RangeType& r);
        short Id;
        short OptionId;
        short NextMenuId;
        short  PrevMenuId;
        String Text;
        String  OptionText;
        RangeType  TheRangeType;
        AccessoryType AccType;

        //vector<LCDMenu> MenuItems; //dont work, fuck it!!!!!!!!!!

        LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, RangeType rangeType, AccessoryType accType) :
            Id(id), OptionId(optionId), NextMenuId(nextMenuId), PrevMenuId(prevMenuId), Text(text), OptionText(optionText), TheRangeType(rangeType), AccType(accType) {
            //MenuItems();
        }
        LCDMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, RangeType rangeType) :
            LCDMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, AccessoryType::None) {
        }

      private:
        LCDMenu& operator=(const LCDMenu& c);


    };
}

#endif

