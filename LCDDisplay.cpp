

#include "LCDDisplay.h"

using namespace LCD;

//static vars
extern int  LCDDisplay::_keyValues[5] = { 50, 200, 400, 600, 800 };
extern short LCDDisplay::_numOfKeys = 5;

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
    AddMenu(mainMenu, _menuIndex++, feedMenu, mainMenu, _mainMenuText, F("Feeders"), LCDMenu::RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, doserMenu, mainMenu, _mainMenuText, F("Dosers"), LCDMenu::RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, settingsMenu, mainMenu, _mainMenuText, F("Settings"), LCDMenu::RangeType::Nav);

    int subMenuIndex = 0;

    //feed menus
    AddMenu(feedMenu, subMenuIndex++, feedNowMenu, mainMenu, feedMenuText, F("Feed Now"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedEnableMenu, mainMenu, feedMenuText, F("Feeders"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedTimeMenu, mainMenu, feedMenuText, F("Feed Time"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedFreqMenu, mainMenu, feedMenuText, F("Set Feed Time"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedShakesMenu, mainMenu, feedMenuText, F("Shakes"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);

    //feed on/off
    AddMenu(feedEnableMenu, 0, feedMenu, feedMenu, F("Feeder On/Off: [<] Back"), F(""), LCDMenu::RangeType::OnOff, AccessoryType::Feeder);

    //feed now
    AddMenu(feedNowMenu, 0, feedMenu, feedMenu, F("Feed Now: [<] Back"), F("Press [Select]"), LCDMenu::RangeType::RunNow, AccessoryType::Feeder);

    //feed time
    AddMenu(feedTimeMenu, 0, feedTimeMenu, feedMenu, F("Feed Time: [<] Back"), F(""), LCDMenu::RangeType::TimeFrequency, AccessoryType::Feeder);
    AddMenu(feedFreqMenu, 0, feedHourMenu, feedMenu, F("Feed Frequency: [<] Back"), F(""), LCDMenu::RangeType::Frequency, AccessoryType::Feeder);
    AddMenu(feedHourMenu, 0, feedMinMenu, feedFreqMenu, F("Feed Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::Feeder);
    AddMenu(feedMinMenu, 0, feedAmPmMenu, feedHourMenu, F("Feed Minute: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::Feeder);
    AddMenu(feedAmPmMenu, 0, feedTimeMenu, feedMinMenu, F("Feed AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::Feeder);

    //feed shakes
    AddMenu(feedShakesMenu, 0, feedMenu, feedMenu, F("Feed Shakes: [<] Back"), F("0"), LCDMenu::RangeType::ShakesOrTurns, AccessoryType::Feeder);
    //AddMenu(feedShakesMenu, 1, feedSetShakesMenu, feedShakesMenu, F("Feed Shakes: [<] Back"), F("Set Feed Shakes"), LCDMenu::RangeType::Nav, AccessoryType::Feeder);
    //AddMenu(feedSetShakesMenu, 0, feedMenu, feedShakesMenu, F("Feed Shakes: [<] Back"), F("Not Set"), LCDMenu::RangeType::SetShakesOrTurns, AccessoryType::Feeder);

    subMenuIndex = 0;

    //doser menus
    AddMenu(doserMenu, subMenuIndex++, doseNowMenu, mainMenu, doserMenuText, F("Dose Now"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserEnableMenu, mainMenu, doserMenuText, F("Dosers"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserTimeMenu, mainMenu, doserMenuText, F("Doser Time"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserFreqMenu, mainMenu, doserMenuText, F("Set Doser Time"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserShakesMenu, mainMenu, doserMenuText, F("Set Doser Shakes"), LCDMenu::RangeType::Nav, AccessoryType::DryDoser);

    //doser on/off
    AddMenu(doserEnableMenu, 0, doserMenu, doserMenu, F("Doser On/Off: [<] Back"), F(""), LCDMenu::RangeType::OnOff, AccessoryType::DryDoser);

    //dose now
    AddMenu(doseNowMenu, 0, doserMenu, doserMenu, F("Dose Now: [<] Back"), F("Press [Select]"), LCDMenu::RangeType::RunNow, AccessoryType::DryDoser);

    //dose time
    AddMenu(doserTimeMenu, 0, doserTimeMenu, doserMenu, F("Doser Time: [<] Back"), F(""), LCDMenu::RangeType::TimeFrequency, AccessoryType::DryDoser);
    AddMenu(doserFreqMenu, 0, doserHourMenu, doserMenu, F("Doser Frequency: [<] Back"), F(""), LCDMenu::RangeType::Frequency, AccessoryType::DryDoser);
    AddMenu(doserHourMenu, 0, doserMinMenu, doserFreqMenu, F("Doser Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::DryDoser);
    AddMenu(doserMinMenu, 0, doserAmPmMenu, doserHourMenu, F("Doser Minute: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::DryDoser);
    AddMenu(doserAmPmMenu, 0, doserTimeMenu, doserMinMenu, F("Doser AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::DryDoser);

    //doser shakes
    AddMenu(doserShakesMenu, 0, doserMenu, doserMenu, F("Doser Shakes: [<] Back"), F("0"), LCDMenu::RangeType::ShakesOrTurns, AccessoryType::DryDoser);

    subMenuIndex = 0;

    //clock menus
    AddMenu(clockMenu, 0, clockMenu, mainMenu, clockMenuText, F("Time"), LCDMenu::RangeType::TimeLong, AccessoryType::Clock);
    AddMenu(clockMenu, 1, clockYearMenu, clockMenu, clockMenuText, F("Set Clock Time"), LCDMenu::RangeType::Nav, AccessoryType::Clock);
    AddMenu(clockYearMenu, 0, clockMonthMenu, clockMenu, F("Clock Year: [<] Back"), F(""), LCDMenu::RangeType::Year, AccessoryType::Clock);
    AddMenu(clockMonthMenu, 0, clockDayMenu, clockYearMenu, F("Clock Month: [<] Back"), F(""), LCDMenu::RangeType::Month, AccessoryType::Clock);
    AddMenu(clockDayMenu, 0, clockHourMenu, clockMonthMenu, F("Clock Day: [<] Back"), F(""), LCDMenu::RangeType::Day, AccessoryType::Clock);
    AddMenu(clockHourMenu, 0, clockMinMenu, clockDayMenu, F("Clock Hour: [<] Back"), F(""), LCDMenu::RangeType::Hour, AccessoryType::Clock);
    AddMenu(clockMinMenu, 0, clockAmPmMenu, clockHourMenu, F("Clock Min: [<] Back"), F(""), LCDMenu::RangeType::Minute, AccessoryType::Clock);
    AddMenu(clockAmPmMenu, 0, clockMenu, clockMinMenu, F("Clock AM-PM: [<] Back"), F(""), LCDMenu::RangeType::AmPm, AccessoryType::Clock);

    subMenuIndex = 0;

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
               rangeType == LCDMenu::RangeType::AmPm ||
               rangeType == LCDMenu::RangeType::RunNow) &&
              (accType == AccessoryType::Feeder ||
               accType == AccessoryType::DryDoser)) {
        RTCExt::SetNextRun(_optionCount, rangeType, accType);
        if(rangeType == LCDMenu::RangeType::RunNow)
            ExitMainMenu(); //exit after run now, so run can execute.
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
    } else if(rangeType == LCDMenu::RangeType::ShakesOrTurns &&
              (accType == AccessoryType::Feeder ||
               accType == AccessoryType::DryDoser)) {
        RTCExt::SetMotorShakesOrTurns(_optionCount, accType);
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


String LCDDisplay::LoadShakesTurnsOption(LCDMenu& menu) {

    int nextMenuId = feedShakesMenu;
    String accMenuOptionText = menu.OptionText;

    NextRunMemory mem;

    bool isFeederOption = ((menu.Id == feedMenu && menu.NextMenuId == feedShakesMenu) || menu.Id == feedShakesMenu || menu.Id == feedShakesMenu);
    bool isDoserOption = ((menu.Id == doserMenu && menu.NextMenuId == doserShakesMenu) || menu.Id == doserShakesMenu || menu.Id == doserShakesMenu);

    if(isFeederOption) {
        nextMenuId = feedShakesMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    } else if(isDoserOption) {
        nextMenuId = doserShakesMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    } else {
        //got to next options
        //accMenuOptionText = LoadShakesTurnsOption(menu).c_str();
        return accMenuOptionText;
    }

    String shakes = String(mem.ShakesOrTurns);
    //if(!mem.Enabled)
    //accMenuOptionText += F(" (Off)");
    if(menu.NextMenuId == nextMenuId)
        accMenuOptionText += " (" + shakes + ")";
    if(menu.Id == nextMenuId && menu.Id != _prevMenuId) { //load from memoroy
        accMenuOptionText = shakes;
        _optionCount = mem.ShakesOrTurns;
    }
    return accMenuOptionText;


    //if(isFeederMainMenuOption) {
    //foundOption = true;
    //NextRunMemory& mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    //String shakes = String(mem.ShakesOrTurns);
    //accMenuOptionText += " (" + shakes + ")";
    ////alert: example: load range val from mem
    //if(menu.Id == feedNextMenu && _prevMenuId != feedNextMenu) {
    //accMenuOptionText = shakes;
    //_optionCount = mem.ShakesOrTurns;
    //}
    //} else if(isDoserMainMenuOption) {
    //foundOption = true;
    //NextRunMemory& mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    //String shakes = String(mem.ShakesOrTurns);
    //accMenuOptionText += " (" + shakes + ")";
    //if(menu.Id == doseNextMenu && _prevMenuId != doseNextMenu) {
    //accMenuOptionText = shakes;
    //_optionCount = mem.ShakesOrTurns;
    //}
    //}
    //
    ////if(!foundOption)
    ////accMenuOptionText = nextMethod...(menu);


}

String LCDDisplay::LoadAccOption(LCDMenu& menu) {
    int nextMenuId = feedEnableMenu;
    String accMenuOptionText = menu.OptionText;

    NextRunMemory mem;

    bool isFeederOption = ((menu.Id == mainMenu && menu.NextMenuId == feedMenu) || menu.NextMenuId == feedEnableMenu || menu.Id == feedEnableMenu);
    bool isDoserOption = ((menu.Id == mainMenu && menu.NextMenuId == doserMenu) || menu.NextMenuId == doserEnableMenu || menu.Id == feedEnableMenu);

    if(isFeederOption) {
        nextMenuId = feedEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    } else if(isDoserOption) {
        nextMenuId = doserEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    } else {
        //got to next options
        accMenuOptionText = LoadShakesTurnsOption(menu).c_str();
        return accMenuOptionText;
    }

    if(!mem.Enabled)
        accMenuOptionText += F(" (Off)");
    else if(menu.NextMenuId == nextMenuId)
        accMenuOptionText += F(" On/Off");
    if(menu.Id == nextMenuId && menu.Id != _prevMenuId) { //load from memoroy
        accMenuOptionText = String(mem.Enabled).c_str();
        _optionCount = mem.Enabled;
    }

    return accMenuOptionText;
}



//get by ref example
//auto& menu = GetMenu(5);
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

    //if(!_optionChanged) {
    //NextRunMemory& mem = RTCExt::FindNextRunInfo(accType);
    //_optionCount = mem.Enabled;
    //}

    if(_optionCount == 0)
        return F("Off");
    else if(_optionCount == 1)
        return F("On");
}
void LCDDisplay::SetOnOff(AccessoryType accType) {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(accType);

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
    _menuTimeout = RTCExt::GetRTCTime() + 900;
    while(_selectedMenuId > -1) {
        if(RTCExt::GetRTCTime() > _menuTimeout)
            ExitMainMenu();

        DetectKeyPress();
        delay(200);
    }
}

void LCDDisplay::ExitMainMenu() {
    // _scrollRightTimer.deleteTimer(_scrollRightTimerId);
    _menuTimeout = 0;
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

        // _optionChanged = true;
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

        //_optionChanged = true;
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
    // _optionChanged = false;
    delay(_selectDelay);

}

void LCDDisplay::IsKeyPressed() {
    int key = GetKey();
    if(key == 0 || key == 1 || key == 2 || key == 3 || key == 4)
        _optionChanged = true;
}

void LCDDisplay::DetectKeyPress() {
    int key = GetKey();
    //SerialExt::Debug("key_dkp:", key);

    if(key == 0 || key == 1 || key == 2 || key == 3 || key == 4)
        _optionChanged = true;

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

void LCDDisplay::PrintMenu(LCDMenu& menu) {
    /*SerialExt::Debug("menu", menu.Text);
    SerialExt::Debug("option", menu.OptionText);
    */

    _optionText = LoadAccOption(menu).c_str();
    _menuText = menu.Text;

    String rangeOptionText = GetRangeOption(menu.TheRangeType, menu.AccType);

    if(rangeOptionText != "") {
        _optionText = rangeOptionText;
        //optionText = StaticUtils::ParseString(rangeOptionText);
    }

    _lcd.clear();

    //_lcd.home();
    //_lcd.noAutoscroll();
    //if(_menuText.length() > 16) {
    //_lcd.autoscroll();
    //}
    _optionChanged = false;

    PrintLine(0, _menuText);
    PrintLine(1, _optionText);

    if(_prevMenuId != _selectedMenuId) {
        HandleScrollText(0, _menuText);
        HandleScrollText(1, _optionText);
    }

    _prevMenuId = _selectedMenuId;

}
void LCDDisplay::HandleScrollText(short lineNum, String text) {
    delay(200);
    if(text.length() > 16) {
        int pos = (text.length() * -1) - 12;
        for(int i = 0; i < text.length() - 12; i++) {
            pos += 1;
            _lcd.setCursor(0, lineNum);
            _lcd.print("                 ");
            _lcd.setCursor(pos, lineNum);
            _lcd.print(text);
            IsKeyPressed();
            if(_optionChanged && _selectedMenuId > -1) {
                PrintLine(0, _menuText);
                PrintLine(1, _optionText);
                return;
            }

            delay(300);
        }
        _lcd.setCursor(0, lineNum);
        _lcd.print(text);
        //delay(500);
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
        label = F("Feeders");
    else if(nextRunMem.AccType == AccessoryType::DryDoser)
        label = F("Dosers");

    if(!nextRunMem.Enabled) {
        _lcd.clear();
        PrintLine(0, label);
        PrintLine(1, F("(Disabled)"));
        delay(_scrollDelay);
        return;
    }

    if(nextRunMem.RunEvery <= 0) {
        _lcd.clear();
        PrintLine(0, label);
        PrintLine(1, F("(Not Set)"));
        delay(_scrollDelay);
        return;
    }

    String lastRun = TimeHelpers::GetShortDateTimeString(nextRunMem.LastRun, false);
    String countDown = TimeHelpers::GetTimeRemainingString(nextRunMem.CountDown, false);
    String nextRun = TimeHelpers::GetShortDateTimeString(nextRunMem.NextRun, false);

    String nextRunText = label + " Last Run:";
    String countDownText = label + " Count Down:";
    String runEveryText = label + " Next Run:";

    for(int i = 0; i <= 3; i++) {

        switch(i) {
            case 0:
                _lcd.clear();
                PrintLine(0, nextRunText);
                PrintLine(1, lastRun);
                HandleScrollText(0, nextRunText);
                break;
            case 1:
                _lcd.clear();
                PrintLine(0, countDownText);
                PrintLine(1, countDown);
                HandleScrollText(0, countDownText);
                break;
            case 2:
                _lcd.clear();
                PrintLine(0, runEveryText);
                PrintLine(1, nextRun);
                HandleScrollText(0, runEveryText);
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

        int key = GetKey();
        if(key == 4) {
            _scrollIndex = 0;
            scrolling = false;
            return;
        }

        switch(_scrollIndex) {
            case 0:
                PrintInstructions();
                break;
            case 1:

                PrintRunInfo(feederNextRunMem);
                break;
            case 2:

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


