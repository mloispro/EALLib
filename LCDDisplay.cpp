

#include "LCDDisplay.h"

using namespace LCD;

void LCDDisplay::Init() {

    pinMode(10, INPUT); //keep lcd from shorting out.
    RTCExt::Init();
    _lcd.begin(16, 2);
    _lcd.clear();
    _lcd.setCursor(0, 0);
    CreateMenus();
    if(!RTCExt::IsRTCTimeSet())
        SelectMainMenu();

}
void LCDDisplay::CreateMenus() {

    _mainMenuText = F("Menu: [>] Exit");
    const String feedMenuText = F("Feeder: [<] Back");
    const String doserMenuText = F("Doser: [<] Back");
    const String clockMenuText = F("Clock: [<] Back");
    const String settingsMenuText = F("Settings: [<] Back");

    if(_menus.size() > 0)
        _menus.clear();

    //menus
    AddMenu(mainMenu, _menuIndex++, clockMenu, mainMenu, _mainMenuText, F("Clock"), LCDMenu::RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, feedMenu, mainMenu, _mainMenuText, F("Feeder"), LCDMenu::RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, doserMenu, mainMenu, _mainMenuText, F("Doser"), LCDMenu::RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, settingsMenu, mainMenu, _mainMenuText, F("Settings"), LCDMenu::RangeType::Nav);

    int subMenuIndex = 0;

    //feed menus
    AddMenu(feedMenu, subMenuIndex++, feedEnableMenu, mainMenu, feedMenuText, F("Feeder Enable"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedTimeMenu, mainMenu, feedMenuText, F("Feed Time"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedFreqMenu, mainMenu, feedMenuText, F("Set Feed Time"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedShakesMenu, mainMenu, feedMenuText, F("Set Feed Shakes"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);

    //feed on/off
    AddMenu(feedEnableMenu, 0, feedEnableMenu, feedMenu, F("Feeder Set: [<] Back"), F(""), LCDMenu::RangeType::OnOff, AccessoryType::Feeder);

    //feed time
    AddMenu(feedTimeMenu, 0, feedTimeMenu, feedMenu, F("Feed Time: [<] Back"), F(""), LCDMenu::RangeType::TimeFrequency, AccessoryType::Feeder);
    AddMenu(feedFreqMenu, 0, feedHourMenu, feedMenu, F("Feed Frequency: [<] Back"), F(""), LCDMenu::RangeType::Frequency, AccessoryType::Feeder);
    AddMenu(feedHourMenu, 0, feedMinMenu, feedFreqMenu, F("Feed Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::Feeder);
    AddMenu(feedMinMenu, 0, feedAmPmMenu, feedHourMenu, F("Feed Minute: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::Feeder);
    AddMenu(feedAmPmMenu, 0, feedTimeMenu, feedMinMenu, F("Feed AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::Feeder);

    //feed shakes
    AddMenu(feedShakesMenu, 0, feedShakesMenu, feedMenu, F("Feed Shakes: [<] Back"), F("Not Set"), LCDMenu::RangeType::ShakesOrTurns, AccessoryType::Feeder);
    AddMenu(feedShakesMenu, 1, feedSetShakesMenu, feedShakesMenu, F("Feed Shakes: [<] Back"), F("Set Feed Shakes"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedSetShakesMenu, 0, feedShakesMenu, feedShakesMenu, F("Set Feed Shakes: [<] Back"), F("Not Set"), LCDMenu::RangeType::SetShakesOrTurns, AccessoryType::Feeder);

    //doser menus
    AddMenu(doserMenu, subMenuIndex++, doserEnableMenu, mainMenu, doserMenuText, F("Doser Enable"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserTimeMenu, mainMenu, doserMenuText, F("Doser Time"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserFreqMenu, mainMenu, doserMenuText, F("Set Doser Time"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserShakesMenu, mainMenu, doserMenuText, F("Set Doser Shakes"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);

    //doser on/off
    AddMenu(doserEnableMenu, 0, doserEnableMenu, doserMenu, F("Doser Set: [<] Back"), F(""), LCDMenu::RangeType::OnOff, AccessoryType::DryDoser);

    //dose time
    AddMenu(doserTimeMenu, 0, doserTimeMenu, doserMenu, F("Doser Time: [<] Back"), F(""), LCDMenu::RangeType::TimeFrequency, AccessoryType::DryDoser);
    AddMenu(doserFreqMenu, 0, doserHourMenu, doserMenu, F("Doser Frequency: [<] Back"), F(""), LCDMenu::RangeType::Frequency, AccessoryType::DryDoser);
    AddMenu(doserHourMenu, 0, doserMinMenu, doserFreqMenu, F("Doser Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::DryDoser);
    AddMenu(doserMinMenu, 0, doserAmPmMenu, doserHourMenu, F("Doser Minute: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::DryDoser);
    AddMenu(doserAmPmMenu, 0, doserTimeMenu, doserMinMenu, F("Doser AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::DryDoser);

    //doser shakes
    AddMenu(doserShakesMenu, 0, doserShakesMenu, doserMenu, F("Doser Shakes: [<] Back"), F(""), LCDMenu::RangeType::ShakesOrTurns, AccessoryType::DryDoser);
    AddMenu(doserShakesMenu, 1, doserSetShakesMenu, doserShakesMenu, F("Doser Shakes: [<] Back"), F("Set Doser Shakes"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserSetShakesMenu, 0, doserShakesMenu, doserShakesMenu, F("Set Doser Shakes: [<] Back"), F(""), LCDMenu::RangeType::SetShakesOrTurns, AccessoryType::DryDoser);

    //clock menus
    AddMenu(clockMenu, 0, clockMenu, mainMenu, clockMenuText, F("Time"), LCDMenu::RangeType::TimeLong, AccessoryType::Clock);
    AddMenu(clockMenu, 1, clockYearMenu, clockMenu, clockMenuText, F("Set Clock Time"), LCDMenu::RangeType::Nav, AccessoryType::Clock);
    AddMenu(clockYearMenu, 0, clockMonthMenu, clockMenu, F("Clock Year: [<] Back"), F(""), LCDMenu::RangeType::Year, AccessoryType::Clock);
    AddMenu(clockMonthMenu, 0, clockDayMenu, clockYearMenu, F("Clock Month: [<] Back"), F(""), LCDMenu::RangeType::Month, AccessoryType::Clock);
    AddMenu(clockDayMenu, 0, clockHourMenu, clockMonthMenu, F("Clock Day: [<] Back"), F(""), LCDMenu::RangeType::Day, AccessoryType::Clock);
    AddMenu(clockHourMenu, 0, clockMinMenu, clockDayMenu, F("Clock Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::Clock);
    AddMenu(clockMinMenu, 0, clockAmPmMenu, clockHourMenu, F("Clock Min: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::Clock);
    AddMenu(clockAmPmMenu, 0, clockMenu, clockMinMenu, F("Clock AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::Clock);

    //settings
    AddMenu(settingsMenu, subMenuIndex++, settingsMenu, mainMenu, settingsMenuText, F("??"), LCDMenu::RangeType::ControllerType, AccessoryType::Lcd);
    //AddMenu(settingsMenu, subMenuIndex++, settingsDoserMenu, settingsMenu, settingsMenuText, F("Change Settings"), LCDMenu::RangeType::Nav, AccessoryType::Lcd);


}
String LCDDisplay::GetRangeOption(LCDMenu::RangeType rangeType, Globals::AccessoryType accType) {

    if(rangeType == LCDMenu::RangeType::Frequency) {
        LimitRange(0, 1);
        if(_optionCount <= _lowerLimit)
            return F("Daily");
        else if(_optionCount >= _upperLimit)
            return F("Every Other Day");

    } else if(rangeType == LCDMenu::RangeType::Hour) {
        LimitRange(1, 12);
        String hour = GetOptionAsNumber(F("01"), true);
        //SerialExt::Debug("feed hour", hour);
        return hour.c_str();
    } else if(rangeType == LCDMenu::RangeType::Minute) {
        LimitRange(0, 59);
        String minute = GetOptionAsNumber(F("01"), true);
        return minute.c_str();
    } else if(rangeType == LCDMenu::RangeType::AmPm) {
        LimitRange(0, 1);
        if(_optionCount <= _lowerLimit)
            return F("AM");
        else if(_optionCount >= _upperLimit)
            return F("PM");
    } else if(rangeType == LCDMenu::RangeType::TimeFrequency) {
        //Daily, 08:30AM
        String freq = GetTimeFrequency(accType);
        return freq.c_str();
    } else if(rangeType == LCDMenu::RangeType::TimeLong) {
        // 03/04/2016 08:30AM
        String time = GetTimeLong(accType);
        return time.c_str();
    } else if(rangeType == LCDMenu::RangeType::Year) {
        LimitRange(2016, 2050);
        String txt = GetOptionAsNumber(F("2016"));

        return txt.c_str();
    } else if(rangeType == LCDMenu::RangeType::Month) {
        LimitRange(1, 12);
        String txt = GetOptionAsNumber(F("01"), true);
        return txt.c_str();
    } else if(rangeType == LCDMenu::RangeType::Day) {
        LimitRange(1, 31);
        String txt = GetOptionAsNumber(F("01"), true);
        return txt.c_str();
    } else if(rangeType == LCDMenu::RangeType::ShakesOrTurns) {
        int shakes = RTCExt::GetShakesOrTurns(accType);
        return String(shakes).c_str();
    } else if(rangeType == LCDMenu::RangeType::SetShakesOrTurns) {
        LimitRange(0, 13);

        String txt = GetOptionAsNumber(F("0"));
        return txt.c_str();
    } else if(rangeType == LCDMenu::RangeType::OnOff) {

        LimitRange(0, 1);

        String txt = GetOnOff(accType);
        return txt.c_str();
    }
    //else if (rangeType == LCDMenu::RangeType::OutPin)
    //{
    //	//pin 14-19 are analog pins but can be used for digital output with SoftPWM
    //	//14 cant be used because it is used by lcd A0
    //	LimitRange(2, 19);
    //	if (_optionCount == 14)
    //		_optionCount++;

    //	String txt = String txt = GetOptionAsNumber("2");
    //	return txt;
    //}
    //else if (rangeType == LCDMenu::RangeType::InPin)
    //{
    //	//pin A0 is used by lcd.
    //	LimitRange(1, 5);

    //	String txt = String txt = GetOptionAsNumber("1");
    //	return txt;
    //}
    else
        return "";
    //
    //return "";

}

void LCDDisplay::SaveRangeOption(LCDMenu::RangeType rangeType, AccessoryType accType) {
    //SerialExt::Debug("save", selectedMenu.OptionText);

    if(rangeType == LCDMenu::RangeType::Frequency &&
            (accType == AccessoryType::Feeder ||
             accType == AccessoryType::DryDoser)) {
        if(_optionCount == 0)  //Daily
            RTCExt::SetRunEvery(24, accType);
        else // ot day
            RTCExt::SetRunEvery(48, accType);
    } else if((rangeType == LCDMenu::RangeType::Hour ||
               rangeType == LCDMenu::RangeType::Minute ||
               rangeType == LCDMenu::RangeType::AmPm) &&
              (accType == AccessoryType::Feeder ||
               accType == AccessoryType::DryDoser)) {
        RTCExt::SetNextRun(_optionCount, rangeType, accType);
    } else if(rangeType == LCDMenu::RangeType::TimeFrequency) {
        //Daily, 08:30AM
    } else if((rangeType == LCDMenu::RangeType::Year ||
               rangeType == LCDMenu::RangeType::Month ||
               rangeType == LCDMenu::RangeType::Day ||
               rangeType == LCDMenu::RangeType::Hour ||
               rangeType == LCDMenu::RangeType::Minute) &&
              (accType == AccessoryType::Clock)) {
        RTCExt::SetTimeTemp(_optionCount, rangeType);
    } else if(rangeType == LCDMenu::RangeType::AmPm &&
              accType == AccessoryType::Clock) {
        RTCExt::SetTimeTemp(_optionCount, rangeType);
        RTCExt::SetRTCTimeFromTemp();
    } else if(rangeType == LCDMenu::RangeType::SetShakesOrTurns &&
              (accType == AccessoryType::Feeder ||
               accType == AccessoryType::DryDoser)) {
        RTCExt::SetShakesOrTurns(accType, _optionCount);
        //_lcdValCallBack(_optionCount);
    } else if(rangeType == LCDMenu::RangeType::OnOff &&
              (accType == AccessoryType::Feeder ||
               accType == AccessoryType::DryDoser)) {
        SetOnOff(accType);
    }
    //else if (rangeType == LCDMenu::RangeType::OutPin &&
    //	(accType == AccessoryType::Feeder ||
    //	accType == AccessoryType::DryDoser))
    //{
    //	//_lcdValCallBack(_optionCount);
    //}

}
//--Menu functions
void LCDDisplay::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, LCDMenu::RangeType rangeType, AccessoryType accType) {
    LCDMenu menu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, accType);
    _menus.push_back(menu);
}
void LCDDisplay::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, String text, String optionText, LCDMenu::RangeType rangeType) {
    AddMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, AccessoryType::None);
}

template<typename T>
String LCDDisplay::GetOptionAsNumber(T&& defaultNumber, bool isTwoDigits) {
    String txt = defaultNumber;
    if(_optionCount <= _upperLimit && _optionCount >= _lowerLimit) {
        String oc = String(_optionCount);
        txt = oc;
        if(_optionCount < 10 && isTwoDigits)
            txt = "0" + txt;
    }
    return txt;
}

template<typename T>
String LCDDisplay::GetOptionAsNumber(T&& defaultNumber) {
    String optnum = GetOptionAsNumber(defaultNumber, false);
    return optnum;
}



//get by ref example
//auto& menu = GetMenu(5);
//LCDMenu& operator=(const LCDMenu& c);
LCDMenu LCDDisplay::GetMenu(short id, short optionId) {
    auto selectedMenu = _menus[0];
    for(auto menu : _menus) {
        if(menu.Id == id && menu.OptionId == optionId)
            return menu;
    }

    return selectedMenu;
}
LCDMenu LCDDisplay::GetSelectedMenu() {
    auto selectedMenu = GetMenu(_selectedMenuId, _selectedOptionId);
    return selectedMenu;
}
void LCDDisplay::SetSelectedMenu(LCDMenu menu) {
    _selectedMenuId = menu.Id;
    _selectedOptionId = menu.OptionId;

}

String LCDDisplay::GetOnOff(AccessoryType accType) {

    if(!_optionChanged) {
        NextRunMemory& mem = RTCExt::FindNextRunInfo(accType);
        _optionCount = mem.Enabled;
    }

    if(_optionCount == 0)
        return F("Off");
    else if(_optionCount == 1)
        return F("On");
}
void LCDDisplay::SetOnOff(AccessoryType accType) {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(accType);

    if(mem.Enabled == (bool)_optionCount)
        return;

    mem.Enabled = (bool)_optionCount;
    RTCExt::RefreshNextRunInfo(accType, true);

    //if(_optionCount == 0)
    //_menuIndex--;

    //AddMenu(accType);
}

void LCDDisplay::SetClockMenu() {
    //SelectMainMenu();

    _selectedMenuId = clockYearMenu;
    _selectedOptionId = 0;
    _optionCount = 0;

    auto setClockMenu = GetSelectedMenu();
    //SerialExt::Debug("_selectedMenuId", _selectedMenuId);

    PrintMenu(setClockMenu);
    delay(_selectDelay);

    while(_selectedMenuId > -1) {
        DetectKeyPress();
        delay(200);
    }
}
void LCDDisplay::SelectMainMenu() {

    _selectedMenuId = 0;
    _selectedOptionId = 0;

    auto menu = GetSelectedMenu();

    PrintMenu(menu);

    delay(_selectDelay);

    //timeout menu after 15min, 900
    long menuTimeout = RTCExt::GetRTCTime() + 900;
    while(_selectedMenuId > -1) {
        if(RTCExt::GetRTCTime() > menuTimeout)
            ExitMainMenu();

        DetectKeyPress();
        delay(200);
    }
}

void LCDDisplay::ExitMainMenu() {
    _selectedMenuId = -1;
    _selectedOptionId = -1;
}

void LCDDisplay::LimitRange(int lower, int upper) {
    _lowerLimit = lower;
    _upperLimit = upper;
    if(_optionCount <= lower) {
        _optionCount = lower; //limit
    } else if(_optionCount >= upper) {
        _optionCount = upper; //limit
    }
}

void LCDDisplay::NextOption() {

    if(_selectedOptionId >= 0) {
        short nextOptionId = _selectedOptionId + 1;
        auto nextMenu = GetMenu(_selectedMenuId, nextOptionId);
        if(nextMenu.Id == _selectedMenuId && nextMenu.OptionId == nextOptionId)
            _selectedOptionId = nextOptionId;

        _optionChanged = true;
    }

    auto selectedMenu = GetSelectedMenu();

    _optionCount++;
    PrintMenu(selectedMenu);
}

void LCDDisplay::PreviousOption() {

    if(_selectedOptionId > 0) {
        short prevOptionId = _selectedOptionId - 1;
        auto prevMenu = GetMenu(_selectedMenuId, prevOptionId);
        if(prevMenu.Id == _selectedMenuId && prevMenu.OptionId == prevOptionId)
            _selectedOptionId = prevOptionId;

        _optionChanged = true;
    }

    auto selectedMenu = GetSelectedMenu();

    _optionCount--;
    PrintMenu(selectedMenu);
}

void LCDDisplay::LeftButton() {
    //navigates back
    _optionCount = 0;
    auto selectedMenu = GetSelectedMenu();
    auto prevMenu = GetMenu(selectedMenu.PrevMenuId, 0);
    SetSelectedMenu(prevMenu);
    PrintMenu(prevMenu);
}

void LCDDisplay::SelectButton() {

    auto selectedMenu = GetSelectedMenu();
    SaveRangeOption(selectedMenu.TheRangeType, selectedMenu.AccType);
    _optionCount = 0;

    auto nextMenu = GetMenu(selectedMenu.NextMenuId, 0);
    SetSelectedMenu(nextMenu);
    PrintMenu(nextMenu);
    _optionChanged = false;
    delay(_selectDelay);

}

void LCDDisplay::DetectKeyPress() {
    int key = GetKey();
    //SerialExt::Debug("key_dkp:", key);

    switch(key) {
        case 0: //right
            ExitMainMenu();
            break;
        case 1: //up
            NextOption();
            break;
        case 2: //down
            PreviousOption();
            break;
        case 3: //left
            LeftButton();
            break;
        case 4: //select
            SelectButton();
            break;
        default:
            break;

    }

}

void LCDDisplay::PrintMenu(LCDMenu menu) {
    /*SerialExt::Debug("menu", menu.Text);
    SerialExt::Debug("option", menu.OptionText);
    */

    String optionText = menu.OptionText;

    String rangeOptionText = GetRangeOption(menu.TheRangeType, menu.AccType);

    if(rangeOptionText != "") {
        optionText = rangeOptionText;
        //optionText = StaticUtils::ParseString(rangeOptionText);
    }

    _lcd.clear();

    //_lcd.setCursor(0, 0);
    PrintLine(0, menu.Text);
    PrintLine(1, optionText);
    _lcd.noAutoscroll();
    if(menu.Text.length() > 16) {
        _lcd.autoscroll();
    }
}

void LCDDisplay::PrintLine(short lineNum, String text) {
    _lcd.setCursor(0, lineNum);
    _lcd.print(text);
}
void LCDDisplay::PrintTime() {

    auto rtcTime = RTCExt::GetRTCTime();
    //auto theMonth = month(time);

    auto dateTimeString = TimeHelpers::GetShortDateTimeString(rtcTime, false);

    //SerialExt::Debug("dtStringp", dateTimeString);
    _lcd.clear();
    PrintLine(0, F("Clock:"));
    PrintLine(1, dateTimeString);

    delay(_scrollDelay);
}

void LCDDisplay::PrintRunInfo(NextRunMemory& nextRunMem) {

    String label;
    if(nextRunMem.AccType == AccessoryType::Feeder)
        label = F("Feed");
    else if(nextRunMem.AccType == AccessoryType::DryDoser)
        label = F("Doser");

    if(nextRunMem.RunEvery <= 0) {
        _lcd.clear();
        PrintLine(0, label);
        PrintLine(1, F("Not Set"));
        delay(_scrollDelay);
        return;
    }

    String lastRun = TimeHelpers::GetShortDateTimeString(nextRunMem.LastRun, false);
    String countDown = TimeHelpers::GetTimeRemainingString(nextRunMem.CountDown, false);
    String nextRun = TimeHelpers::GetShortDateTimeString(nextRunMem.NextRun, false);


    for(int i = 0; i <= 3; i++) {

        switch(i) {
            case 0:
                _lcd.clear();
                PrintLine(0, label + " Last Run:");
                PrintLine(1, lastRun);
                break;
            case 1:
                _lcd.clear();
                PrintLine(0, label + " Count Down:");
                PrintLine(1, countDown);
                break;
            case 2:
                _lcd.clear();
                PrintLine(0, label + " Next Run:");
                PrintLine(1, nextRun);
                break;
            default:
                break;
        }

        //_lcd.clear();
        delay(_scrollDelay);
        //_lcd.clear();
    }
}
void LCDDisplay::PrintInstructions() {
    _lcd.clear();
    PrintLine(0, F("Hold [Select]"));
    PrintLine(1, F("for Menu"));
    delay(_scrollDelay);
}

void LCDDisplay::Scroll() {
    static bool scrolling; //= (_scrollIndex < 3);

    if(scrolling)  //dont scroll if already scrolling
        return;

    scrolling = true;

    NextRunMemory& feederNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    NextRunMemory& doserNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);

    while(scrolling) {

        //SerialExt::Debug("_scrollIndex", _scrollIndex);
        //SerialExt::Debug("scrolling_time_beg", RTCExt::GetRTCTimeString());

        switch(_scrollIndex) {
            case 0:
                PrintInstructions();
                break;
            case 1:
                if(feederNextRunMem.Enabled)
                    PrintRunInfo(feederNextRunMem);
                break;
            case 2:
                if(doserNextRunMem.Enabled)
                    PrintRunInfo(doserNextRunMem);
                break;
            default:
                PrintTime();
                _scrollIndex = 0;
                scrolling = false;
                return;
        }
        _scrollIndex++;
    }//scrolling
}

String LCDDisplay::GetTimeLong(AccessoryType accType) {
    long time;

    if(accType == AccessoryType::Clock) {
        time = RTCExt::GetRTCTime();
    }

    String timeString = TimeHelpers::GetShortDateTimeString(time, false);
    return timeString;

}

String LCDDisplay::GetTimeFrequency(AccessoryType accType) {
    long runEvery;
    long nextRun;

    NextRunMemory& nextRunMem = RTCExt::RefreshNextRunInfo(accType);

    runEvery = nextRunMem.RunEvery;
    nextRun = nextRunMem.NextRun;

    if(runEvery <= 0)
        return F("Not Set");

    String freqTime = RTCExt::GetTimeFrequencyString(runEvery, nextRun);
    return freqTime.c_str();

}

//--key press
int LCDDisplay::GetKeyFromVal(unsigned int input) {
    int k;
    for(k = 0; k < _numOfKeys; k++) {
        if(input < _keyValues[k]) {
            return k;
        }
    }
    if(k >= _numOfKeys) k = -1;
    return k;
}

int LCDDisplay::GetKey() {
    int keyVal = analogRead(0);
    //SerialExt::Debug(F("keyVal"), keyVal);
    int key = GetKeyFromVal(keyVal);
    //SerialExt::Debug(F("key"), key);
    //_lastKey = key;
    return key;
}


