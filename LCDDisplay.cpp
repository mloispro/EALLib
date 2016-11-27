

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
    if(!RTCExt::IsRTCTimeSet()) {
        SelectMainMenu();
    }

}

void LCDDisplay::CreateMenus() {

    _mainMenuText = "Menu: [>] Exit";
    char* feedMenuText = "Feeder: [<] Back";
    char* doserMenuText = "Doser: [<] Back";
    char* clockMenuText = "Clock: [<] Back";
    char* pumpMenuText = "Pump: [<] Back";
    char* microsMenuText = "Micros Doser: [<] Back";


    //if(_menus.size() > 0) {
    //_menus.clear();
    //}
    //_menus.resize(60);

    //menus
    AddMenu(mainMenu, _menuIndex++, clockMenu, mainMenu, _mainMenuText, "Clock", RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, feedMenu, mainMenu, _mainMenuText, "Feeders", RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, doserMenu, mainMenu, _mainMenuText, "Dosers", RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, pumpMenu, mainMenu, _mainMenuText, "Pump", RangeType::Nav);
    AddMenu(mainMenu, _menuIndex++, microsMenu, mainMenu, _mainMenuText, "Micros Doser", RangeType::Nav);

    int subMenuIndex = 0;

    //feed menus
    AddMenu(feedMenu, subMenuIndex++, feedNowMenu, mainMenu, feedMenuText, "Feed Now", RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedEnableMenu, mainMenu, feedMenuText, "Feeders", RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedTimeMenu, mainMenu, feedMenuText, "Feed Time", RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedFreqMenu, mainMenu, feedMenuText, "Set Feed Time", RangeType::Nav, AccessoryType::Feeder);
    AddMenu(feedMenu, subMenuIndex++, feedShakesMenu, mainMenu, feedMenuText, "Shakes", RangeType::Nav, AccessoryType::Feeder);

    //feed on/off
    AddMenu(feedEnableMenu, 0, feedMenu, feedMenu, "Feeder On/Off: [<] Back", "", RangeType::OnOff, AccessoryType::Feeder);

    //feed now
    AddMenu(feedNowMenu, 0, feedMenu, feedMenu, "Feed Now: [<] Back", "Press [Select]", RangeType::RunNow, AccessoryType::Feeder);

    //feed time
    AddMenu(feedTimeMenu, 0, feedTimeMenu, feedMenu, "Feed Time: [<] Back", "", RangeType::TimeFrequency, AccessoryType::Feeder);
    AddMenu(feedFreqMenu, 0, feedHourMenu, feedMenu, "Feed Frequency: [<] Back", "", RangeType::Frequency, AccessoryType::Feeder);
    AddMenu(feedHourMenu, 0, feedMinMenu, feedFreqMenu, "Feed Hour: [<] Back", "", RangeType::Hour, AccessoryType::Feeder);
    AddMenu(feedMinMenu, 0, feedAmPmMenu, feedHourMenu, "Feed Minute: [<] Back", "", RangeType::Minute, AccessoryType::Feeder);
    AddMenu(feedAmPmMenu, 0, feedTimeMenu, feedMinMenu, "Feed AM-PM: [<] Back", "", RangeType::AmPm, AccessoryType::Feeder);

    //feed shakes
    AddMenu(feedShakesMenu, 0, feedMenu, feedMenu, "Feed Shakes: [<] Back", "0", RangeType::ShakesOrTurns, AccessoryType::Feeder);
    //AddMenu(feedShakesMenu, 1, feedSetShakesMenu, feedShakesMenu, "Feed Shakes: [<] Back", "Set Feed Shakes", RangeType::Nav, AccessoryType::Feeder);
    //AddMenu(feedSetShakesMenu, 0, feedMenu, feedShakesMenu, "Feed Shakes: [<] Back", "Not Set", RangeType::SetShakesOrTurns, AccessoryType::Feeder);

    subMenuIndex = 0;

    //doser menus
    AddMenu(doserMenu, subMenuIndex++, doseNowMenu, mainMenu, doserMenuText, "Dose Now", RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserEnableMenu, mainMenu, doserMenuText, "Dosers", RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserTimeMenu, mainMenu, doserMenuText, "Doser Time", RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserFreqMenu, mainMenu, doserMenuText, "Set Doser Time", RangeType::Nav, AccessoryType::DryDoser);
    AddMenu(doserMenu, subMenuIndex++, doserShakesMenu, mainMenu, doserMenuText, "Set Doser Shakes", RangeType::Nav, AccessoryType::DryDoser);

    //doser on/off
    AddMenu(doserEnableMenu, 0, doserMenu, doserMenu, "Doser On/Off: [<] Back", "", RangeType::OnOff, AccessoryType::DryDoser);

    //dose now
    AddMenu(doseNowMenu, 0, doserMenu, doserMenu, "Dose Now: [<] Back", "Press [Select]", RangeType::RunNow, AccessoryType::DryDoser);

    //dose time
    AddMenu(doserTimeMenu, 0, doserTimeMenu, doserMenu, "Doser Time: [<] Back", "", RangeType::TimeFrequency, AccessoryType::DryDoser);
    AddMenu(doserFreqMenu, 0, doserHourMenu, doserMenu, "Doser Frequency: [<] Back", "", RangeType::Frequency, AccessoryType::DryDoser);
    AddMenu(doserHourMenu, 0, doserMinMenu, doserFreqMenu, "Doser Hour: [<] Back", "", RangeType::Hour, AccessoryType::DryDoser);
    AddMenu(doserMinMenu, 0, doserAmPmMenu, doserHourMenu, "Doser Minute: [<] Back", "", RangeType::Minute, AccessoryType::DryDoser);
    AddMenu(doserAmPmMenu, 0, doserTimeMenu, doserMinMenu, "Doser AM-PM: [<] Back", "", RangeType::AmPm, AccessoryType::DryDoser);

    //doser shakes
    AddMenu(doserShakesMenu, 0, doserMenu, doserMenu, "Doser Shakes: [<] Back", "0", RangeType::ShakesOrTurns, AccessoryType::DryDoser);

    subMenuIndex = 0;

    //pump
    AddMenu(pumpMenu, subMenuIndex++, pumpNowMenu, mainMenu, pumpMenuText, "Pump Now", RangeType::Nav, AccessoryType::WaterPump);
    AddMenu(pumpMenu, subMenuIndex++, pumpEnableMenu, mainMenu, pumpMenuText, "Pump", RangeType::Nav, AccessoryType::WaterPump);
    AddMenu(pumpMenu, subMenuIndex++, pumpTimeMenu, mainMenu, pumpMenuText, "Pump Time", RangeType::Nav, AccessoryType::WaterPump);
    AddMenu(pumpMenu, subMenuIndex++, pumpFreqMenu, mainMenu, pumpMenuText, "Set Pump Time", RangeType::Nav, AccessoryType::WaterPump);
    AddMenu(pumpMenu, subMenuIndex++, pumpRunMinutesMenu, mainMenu, pumpMenuText, "Pump Durration", RangeType::Nav, AccessoryType::WaterPump);

    //pump on/off
    AddMenu(pumpEnableMenu, 0, pumpMenu, pumpMenu, "Pump On/Off: [<] Back", "", RangeType::OnOff, AccessoryType::WaterPump);

    //pump now
    AddMenu(pumpNowMenu, 0, pumpMenu, pumpMenu, "Pump Now: [<] Back", "Press [Select]", RangeType::RunNow, AccessoryType::WaterPump);

    //pump time
    AddMenu(pumpTimeMenu, 0, pumpTimeMenu, pumpMenu, "Pump Time: [<] Back", "", RangeType::TimeFrequency, AccessoryType::WaterPump);
    AddMenu(pumpFreqMenu, 0, pumpHourMenu, pumpMenu, "Pump Frequency: [<] Back", "", RangeType::Frequency, AccessoryType::WaterPump);
    AddMenu(pumpHourMenu, 0, pumpMinMenu, pumpFreqMenu, "Pump Hour: [<] Back", "", RangeType::Hour, AccessoryType::WaterPump);
    AddMenu(pumpMinMenu, 0, pumpAmPmMenu, pumpHourMenu, "Pump Minute: [<] Back", "", RangeType::Minute, AccessoryType::WaterPump);
    AddMenu(pumpAmPmMenu, 0, pumpTimeMenu, pumpMinMenu, "Pump AM-PM: [<] Back", "", RangeType::AmPm, AccessoryType::WaterPump);

    //pump durration
    AddMenu(pumpRunMinutesMenu, 0, pumpMenu, pumpMenu, "Pump Durration: [<] Back", "0", RangeType::RunDurration, AccessoryType::WaterPump);

    subMenuIndex = 0;

    //micros
    AddMenu(microsMenu, subMenuIndex++, microsNowMenu, mainMenu, microsMenuText, "Dose Now", RangeType::Nav, AccessoryType::MicrosDoser);
    AddMenu(microsMenu, subMenuIndex++, microsEnableMenu, mainMenu, microsMenuText, "Micros", RangeType::Nav, AccessoryType::MicrosDoser);
    AddMenu(microsMenu, subMenuIndex++, microsTimeMenu, mainMenu, microsMenuText, "Dose Time", RangeType::Nav, AccessoryType::MicrosDoser);
    AddMenu(microsMenu, subMenuIndex++, microsFreqMenu, mainMenu, microsMenuText, "Set Dose Time", RangeType::Nav, AccessoryType::MicrosDoser);
    AddMenu(microsMenu, subMenuIndex++, microsRunMinutesMenu, mainMenu, microsMenuText, "Dose Durration", RangeType::Nav, AccessoryType::MicrosDoser);

    //micros on/off
    AddMenu(microsEnableMenu, 0, microsMenu, microsMenu, "Micros On/Off: [<] Back", "", RangeType::OnOff, AccessoryType::MicrosDoser);

    //micros now
    AddMenu(microsNowMenu, 0, microsMenu, microsMenu, "Dose Now: [<] Back", "Press [Select]", RangeType::RunNow, AccessoryType::MicrosDoser);

    //micros time
    AddMenu(microsTimeMenu, 0, microsTimeMenu, microsMenu, "Dose Time: [<] Back", "", RangeType::TimeFrequency, AccessoryType::MicrosDoser);
    AddMenu(microsFreqMenu, 0, microsHourMenu, microsMenu, "Dose Frequency: [<] Back", "", RangeType::Frequency, AccessoryType::MicrosDoser);
    AddMenu(microsHourMenu, 0, microsMinMenu, microsFreqMenu, "Dose Hour: [<] Back", "", RangeType::Hour, AccessoryType::MicrosDoser);
    AddMenu(microsMinMenu, 0, microsAmPmMenu, microsHourMenu, "Dose Minute: [<] Back", "", RangeType::Minute, AccessoryType::MicrosDoser);
    AddMenu(microsAmPmMenu, 0, microsTimeMenu, microsMinMenu, "Dose AM-PM: [<] Back", "", RangeType::AmPm, AccessoryType::MicrosDoser);

    //micros durration
    AddMenu(microsRunMinutesMenu, 0, microsMenu, microsMenu, "Dose Durration: [<] Back", "0", RangeType::RunDurration, AccessoryType::MicrosDoser);

    subMenuIndex = 0;

    //clock menus
    AddMenu(clockMenu, 0, clockMenu, mainMenu, clockMenuText, "Time", RangeType::TimeLong, AccessoryType::Clock);
    AddMenu(clockMenu, 1, clockYearMenu, clockMenu, clockMenuText, "Set Clock Time", RangeType::Nav, AccessoryType::Clock);
    AddMenu(clockYearMenu, 0, clockMonthMenu, clockMenu, "Clock Year: [<] Back", "", RangeType::Year, AccessoryType::Clock);
    AddMenu(clockMonthMenu, 0, clockDayMenu, clockYearMenu, "Clock Month: [<] Back", "", RangeType::Month, AccessoryType::Clock);
    AddMenu(clockDayMenu, 0, clockHourMenu, clockMonthMenu, "Clock Day: [<] Back", "", RangeType::Day, AccessoryType::Clock);
    AddMenu(clockHourMenu, 0, clockMinMenu, clockDayMenu, "Clock Hour: [<] Back", "", RangeType::Hour, AccessoryType::Clock);
    AddMenu(clockMinMenu, 0, clockAmPmMenu, clockHourMenu, "Clock Min: [<] Back", "", RangeType::Minute, AccessoryType::Clock);
    AddMenu(clockAmPmMenu, 0, clockMenu, clockMinMenu, "Clock AM-PM: [<] Back", "", RangeType::AmPm, AccessoryType::Clock);

    subMenuIndex = 0;

}

String LCDDisplay::GetRangeOption(LCD::RangeType rangeType, Globals::AccessoryType accType) {

    if(rangeType == RangeType::Frequency &&
            accType != AccessoryType::WaterPump) {
        LimitRange(0, 1);
        if(_optionCount <= _lowerLimit) {
            return F("Daily");
        }
        else if(_optionCount >= _upperLimit) {
            return F("Every Other Day");
        }
    }
    else if(rangeType == RangeType::Frequency &&
            accType == AccessoryType::WaterPump) {
        LimitRange(0, 3);
        if(_optionCount == 0) { //Weekly
            return F("Weekly");
        }
        else if(_optionCount == 1) { // ot week
            return F("Every 2 Weeks");
        }
        else if(_optionCount == 2) { // every three weeks
            return F("Every 3 Weeks");
        }
        else if(_optionCount == 3) { // monthly
            return F("Monthly");
        }
    }
    else if(rangeType == RangeType::Hour) {
        LimitRange(1, 12);
        String hour = GetOptionAsNumber(F("01"), true);
        //SerialExt::Debug("feed hour", hour);
        return hour.c_str();
    }
    else if(rangeType == RangeType::Minute) {
        LimitRange(0, 59);
        String minute = GetOptionAsNumber(F("01"), true);
        return minute.c_str();
    }
    else if(rangeType == RangeType::AmPm) {
        LimitRange(0, 1);
        if(_optionCount <= _lowerLimit) {
            return F("AM");
        }
        else if(_optionCount >= _upperLimit) {
            return F("PM");
        }
    }
    else if(rangeType == RangeType::TimeFrequency) {
        //Daily, 08:30AM
        String freq = GetTimeFrequency(accType);
        return freq.c_str();
    }
    else if(rangeType == RangeType::TimeLong) {
        // 03/04/2016 08:30AM
        String time = GetTimeLong(accType);
        return time.c_str();
    }
    else if(rangeType == RangeType::Year) {
        LimitRange(2016, 2050);
        String txt = GetOptionAsNumber(F("2016"));

        return txt.c_str();
    }
    else if(rangeType == RangeType::Month) {
        LimitRange(1, 12);
        String txt = GetOptionAsNumber(F("01"), true);
        return txt.c_str();
    }
    else if(rangeType == RangeType::Day) {
        LimitRange(1, 31);
        String txt = GetOptionAsNumber(F("01"), true);
        return txt.c_str();
    }
    else if(rangeType == RangeType::ShakesOrTurns) {
        LimitRange(0, 13);

        String txt = GetOptionAsNumber(F("0"));
        return txt.c_str();
    }
    else if(rangeType == RangeType::OnOff) {

        LimitRange(0, 1);

        String txt = GetOnOff(accType);
        return txt.c_str();
    }
    else if(rangeType == RangeType::RunDurration) {

        LimitRange(0, 3);

        String txt = GetRunDurration(accType);
        return txt.c_str();
    }
    //else if (rangeType == RangeType::OutPin)
    //{
    //	//pin 14-19 are analog pins but can be used for digital output with SoftPWM
    //	//14 cant be used because it is used by lcd A0
    //	LimitRange(2, 19);
    //	if (_optionCount == 14)
    //		_optionCount++;

    //	String txt = String txt = GetOptionAsNumber("2");
    //	return txt;
    //}
    //else if (rangeType == RangeType::InPin)
    //{
    //	//pin A0 is used by lcd.
    //	LimitRange(1, 5);

    //	String txt = String txt = GetOptionAsNumber("1");
    //	return txt;
    //}
    else {
        return "";
    }
    //
    //return "";

}

void LCDDisplay::SaveRangeOption(RangeType rangeType, AccessoryType accType) {
    //SerialExt::Debug("save", selectedMenu.OptionText);

    if(rangeType == RangeType::Frequency &&
            (accType == AccessoryType::Feeder ||
             accType == AccessoryType::DryDoser ||
             accType == AccessoryType::MicrosDoser)) {
        if(_optionCount == 0) { //Daily
            RTCExt::SetRunEvery(24, accType);
        }
        else { // ot day
            RTCExt::SetRunEvery(48, accType);
        }
    }
    else if(rangeType == RangeType::Frequency &&
            accType == AccessoryType::WaterPump) {
        if(_optionCount == 0) { //Weekly
            RTCExt::SetRunEvery(168, accType);
        }
        else if(_optionCount == 1) { // ot week
            RTCExt::SetRunEvery(336, accType);
        }
        else if(_optionCount == 2) { // every three weeks
            RTCExt::SetRunEvery(504, accType);
        }
        else if(_optionCount == 3) { // monthly
            RTCExt::SetRunEvery(672, accType);
        }
    }
    else if((rangeType == RangeType::Hour ||
             rangeType == RangeType::Minute ||
             rangeType == RangeType::AmPm ||
             rangeType == RangeType::RunNow) &&
            (accType == AccessoryType::Feeder ||
             accType == AccessoryType::DryDoser ||
             accType == AccessoryType::WaterPump ||
             accType == AccessoryType::MicrosDoser)) {
        RTCExt::SetNextRun(_optionCount, rangeType, accType);
        if(rangeType == RangeType::RunNow) {
            ExitMainMenu(); //exit after run now, so run can execute.
        }
    }
    else if(rangeType == RangeType::TimeFrequency) {
        //Daily, 08:30AM
    }
    else if((rangeType == RangeType::Year ||
             rangeType == RangeType::Month ||
             rangeType == RangeType::Day ||
             rangeType == RangeType::Hour ||
             rangeType == RangeType::Minute) &&
            (accType == AccessoryType::Clock)) {
        RTCExt::SetTimeTemp(_optionCount, rangeType);
    }
    else if(rangeType == RangeType::AmPm &&
            accType == AccessoryType::Clock) {
        RTCExt::SetTimeTemp(_optionCount, rangeType);
        RTCExt::SetRTCTimeFromTemp();
    }
    else if(rangeType == RangeType::ShakesOrTurns &&
            (accType == AccessoryType::Feeder ||
             accType == AccessoryType::DryDoser)) {
        RTCExt::SetMotorShakesOrTurns(_optionCount, accType);
        //_lcdValCallBack(_optionCount);
    }
    else if(rangeType == RangeType::OnOff &&
            (accType == AccessoryType::Feeder ||
             accType == AccessoryType::DryDoser ||
             accType == AccessoryType::WaterPump ||
             accType == AccessoryType::MicrosDoser)) {
        SetOnOff(accType);
    }
    else if(rangeType == RangeType::RunDurration &&
            (accType == AccessoryType::WaterPump ||
             accType == AccessoryType::MicrosDoser)) {
        SetRunDurration(accType);
    }
    //else if (rangeType == RangeType::OutPin &&
    //	(accType == AccessoryType::Feeder ||
    //	accType == AccessoryType::DryDoser))
    //{
    //	//_lcdValCallBack(_optionCount);
    //}

}
//--Menu functions
void LCDDisplay::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, char* text, char* optionText, RangeType rangeType, AccessoryType accType) {
    LCDMenu menu{id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, accType};
    //_menus.push_back(menu);
    _menus[_menusIndex++] = menu;
}
void LCDDisplay::AddMenu(short id, short optionId, short nextMenuId, short prevMenuId, char* text, char* optionText, RangeType rangeType) {
    AddMenu(id, optionId, nextMenuId, prevMenuId, text, optionText, rangeType, AccessoryType::None);
}

template<typename T>
String LCDDisplay::GetOptionAsNumber(T&& defaultNumber, bool isTwoDigits) {
    String txt = defaultNumber;
    if(_optionCount <= _upperLimit && _optionCount >= _lowerLimit) {
        String oc = String(_optionCount);
        txt = oc;
        if(_optionCount < 10 && isTwoDigits) {
            txt = "0" + txt;
        }
    }
    return txt;
}

template<typename T>
String LCDDisplay::GetOptionAsNumber(T&& defaultNumber) {
    String optnum = GetOptionAsNumber(defaultNumber, false);
    return optnum;
}


String LCDDisplay::loadShakesTurnsOption(LCDMenu menu) {

    int nextMenuId = feedShakesMenu;
    String accMenuOptionText = String(menu.OptionText);

    NextRunMemory mem;

    bool isFeederOption = ((menu.Id == feedMenu && menu.NextMenuId == feedShakesMenu) || menu.Id == feedShakesMenu || menu.Id == feedShakesMenu);
    bool isDoserOption = ((menu.Id == doserMenu && menu.NextMenuId == doserShakesMenu) || menu.Id == doserShakesMenu || menu.Id == doserShakesMenu);

    if(isFeederOption) {
        nextMenuId = feedShakesMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    }
    else if(isDoserOption) {
        nextMenuId = doserShakesMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    }
    else {
        //got to next options
        accMenuOptionText = loadRunNowOption(menu).c_str();
        return accMenuOptionText;
    }

    String shakes = String(mem.ShakesOrTurns);
    //if(!mem.Enabled)
    //accMenuOptionText += F(" (Off)");
    if(menu.NextMenuId == nextMenuId) {
        accMenuOptionText += " (" + shakes + ")";
    }
    if(menu.Id == nextMenuId && menu.Id != _prevMenuId) { //alert: example: load from memoroy
        accMenuOptionText = shakes;
        _optionCount = mem.ShakesOrTurns;
    }
    return accMenuOptionText;
}
String LCDDisplay::loadRunNowOption(LCDMenu menu) {

    int nextMenuId = feedNowMenu;
    String accMenuOptionText = String(menu.OptionText);

    NextRunMemory mem;

    bool isFeederOption = ((menu.Id == feedMenu && menu.NextMenuId == feedNowMenu) || menu.Id == feedNowMenu || menu.Id == feedNowMenu);
    bool isDoserOption = ((menu.Id == doserMenu && menu.NextMenuId == doseNowMenu) || menu.Id == doseNowMenu || menu.Id == doseNowMenu);
    bool isPumpOption = ((menu.Id == pumpMenu && menu.NextMenuId == pumpNowMenu) || menu.Id == pumpNowMenu || menu.Id == pumpNowMenu);
    bool isMicrosOption = ((menu.Id == mainMenu && menu.NextMenuId == microsMenu) || menu.NextMenuId == microsEnableMenu || menu.Id == microsEnableMenu);

    if(isFeederOption) {
        nextMenuId = feedNowMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    }
    else if(isDoserOption) {
        nextMenuId = doseNowMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    }
    else if(isPumpOption) {
        nextMenuId = pumpNowMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::WaterPump);
    }
    else if(isMicrosOption) {
        nextMenuId = microsNowMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::MicrosDoser);
    }
    else {
        //got to next options
        //accMenuOptionText = LoadShakesTurnsOption(menu).c_str();
        return accMenuOptionText;
    }

    if(!mem.Enabled) {
        accMenuOptionText += F(" (Acc is Off)");
        if(menu.Id == nextMenuId) {
            accMenuOptionText = F(" (Acc is Off)");
        }
    }

    return accMenuOptionText;
}

String LCDDisplay::LoadAccOption(LCDMenu menu) {
    int nextMenuId = feedEnableMenu;
    String accMenuOptionText = String(menu.OptionText);

    NextRunMemory mem;

    bool isFeederOption = ((menu.Id == mainMenu && menu.NextMenuId == feedMenu) || menu.NextMenuId == feedEnableMenu || menu.Id == feedEnableMenu);
    bool isDoserOption = ((menu.Id == mainMenu && menu.NextMenuId == doserMenu) || menu.NextMenuId == doserEnableMenu || menu.Id == doserEnableMenu);
    bool isPumpOption = ((menu.Id == mainMenu && menu.NextMenuId == pumpMenu) || menu.NextMenuId == pumpEnableMenu || menu.Id == pumpEnableMenu);
    bool isMicrosOption = ((menu.Id == mainMenu && menu.NextMenuId == microsMenu) || menu.NextMenuId == microsEnableMenu || menu.Id == microsEnableMenu);

    if(isFeederOption) {
        nextMenuId = feedEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    }
    else if(isDoserOption) {
        nextMenuId = doserEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    }
    else if(isPumpOption) {
        nextMenuId = pumpEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::WaterPump);
    }
    else if(isMicrosOption) {
        nextMenuId = microsEnableMenu;
        mem = RTCExt::RefreshNextRunInfo(AccessoryType::MicrosDoser);
    }
    else {
        //got to next options
        accMenuOptionText = loadShakesTurnsOption(menu).c_str();
        return accMenuOptionText;
    }

    if(!mem.Enabled) {
        accMenuOptionText += F(" (Off)");
    }
    else if(menu.NextMenuId == nextMenuId) {
        accMenuOptionText += F(" On/Off");
    }
    if(menu.Id == nextMenuId && menu.Id != _prevMenuId) { //load from memoroy
        accMenuOptionText = String(mem.Enabled).c_str();
        _optionCount = mem.Enabled;
    }

    return accMenuOptionText;
}



//get by ref example
//auto& menu = GetMenu(5);
LCDMenu LCDDisplay::GetMenu(short id, short optionId) {
    LCDMenu selectedMenu = _menus[0];
    //for(auto menu : _menus) {
    //if(menu.Id == id && menu.OptionId == optionId) {
    //return menu;
    //}
    //}
    for(int i = 0; i < MENUITEMS; i++) {
        LCDMenu menu = _menus[i];
        if(menu.Id == id && menu.OptionId == optionId) {
            return menu;
        }
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

String LCDDisplay::GetRunDurration(AccessoryType accType) {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(accType); //alert: example get option from mem.

    if(mem.RunDurrationOption > -1 && !_loadedOptionFromMem) {
        _optionCount = mem.RunDurrationOption;
        _loadedOptionFromMem = true;
    }

    if(accType == AccessoryType::WaterPump) {
        if(_optionCount == 0) {
            return F("1/2 Min");
        }
        else if(_optionCount == 1) {
            return F("1 Min");
        }
        else if(_optionCount == 2) {
            return F("1 1/2 Min");
        }
        else if(_optionCount == 3) {
            return F("2 Min");
        }
    }
    else if(accType == AccessoryType::MicrosDoser) {
        if(_optionCount == 0) {
            return F("2 Seconds");
        }
        else if(_optionCount == 1) {
            return F("5 Seconds");
        }
        else if(_optionCount == 2) {
            return F("10 Seconds");
        }
        else if(_optionCount == 3) {
            return F("20 Seconds");
        }
    }
}
void LCDDisplay::SetRunDurration(AccessoryType accType) {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(accType);

    long secs = 0;

    if(accType == AccessoryType::WaterPump) {
        if(_optionCount == 0) {
            secs = 30;
        }
        else if(_optionCount == 1) {
            secs = 60;
        }
        else if(_optionCount == 2) {
            secs = 90;
        }
        else if(_optionCount == 3) {
            secs = 120;
        }
    }
    else if(accType == AccessoryType::MicrosDoser) {
        if(_optionCount == 0) {
            secs = 2;
        }
        else if(_optionCount == 1) {
            secs = 5;
        }
        else if(_optionCount == 2) {
            secs = 10;
        }
        else if(_optionCount == 3) {
            secs = 20;
        }
    }

    mem.RunDurration = secs;
    mem.RunDurrationOption = _optionCount; //alert: example save option to mem.
    _loadedOptionFromMem = false;

    RTCExt::RefreshNextRunInfo(accType, true);
}
String LCDDisplay::GetOnOff(AccessoryType accType) {

    if(_optionCount == 0) {
        return F("Off");
    }
    else if(_optionCount == 1) {
        return F("On");
    }
}
void LCDDisplay::SetOnOff(AccessoryType accType) {
    NextRunMemory& mem = RTCExt::RefreshNextRunInfo(accType);

    mem.Enabled = (bool)_optionCount;
    RTCExt::RefreshNextRunInfo(accType, true);
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
        if(RTCExt::GetRTCTime() > _menuTimeout) {
            ExitMainMenu();
        }

        DetectKeyPress();
        delay(200);
    }
}

void LCDDisplay::ExitMainMenu() {
    // _scrollRightTimer.deleteTimer(_scrollRightTimerId);
    _menuTimeout = 0;
    _selectedMenuId = -1;
    _selectedOptionId = -1;
    PrintLine(0, "Please Wait..");
    PrintLine(1, "");
}

void LCDDisplay::LimitRange(int lower, int upper) {
    _lowerLimit = lower;
    _upperLimit = upper;
    if(_optionCount <= lower) {
        _optionCount = lower; //limit
    }
    else if(_optionCount >= upper) {
        _optionCount = upper; //limit
    }
}

void LCDDisplay::NextOption() {

    if(_selectedOptionId >= 0) {
        short nextOptionId = _selectedOptionId + 1;
        auto nextMenu = GetMenu(_selectedMenuId, nextOptionId);
        if(nextMenu.Id == _selectedMenuId && nextMenu.OptionId == nextOptionId) {
            _selectedOptionId = nextOptionId;
        }

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
        if(prevMenu.Id == _selectedMenuId && prevMenu.OptionId == prevOptionId) {
            _selectedOptionId = prevOptionId;
        }

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
    if(key == 0 || key == 1 || key == 2 || key == 3 || key == 4) {
        _optionChanged = true;
    }
}

void LCDDisplay::DetectKeyPress() {
    int key = GetKey();
    //SerialExt::Debug("key_dkp:", key);

    if(key == 0 || key == 1 || key == 2 || key == 3 || key == 4) {
        _optionChanged = true;
    }

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

    _optionText = LoadAccOption(menu).c_str();
    _menuText = String(menu.Text).c_str();

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
    //todo: replace with if printtime=millis()...
    delay(_scrollDelay);
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

void LCDDisplay::Scroll() {
    static bool scrolling; //= (_scrollIndex < 3);

    if(scrolling) { //dont scroll if already scrolling
        return;
    }

    scrolling = true;

    NextRunMemory& feederNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::Feeder);
    NextRunMemory& doserNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::DryDoser);
    NextRunMemory& pumpNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::WaterPump);
    NextRunMemory& microsNextRunMem = RTCExt::RefreshNextRunInfo(AccessoryType::MicrosDoser);

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
            case 3:
                PrintRunInfo(pumpNextRunMem);
                break;
            case 4:
                PrintRunInfo(microsNextRunMem);
                break;
            case 5:
                PrintDisabledAcc(feederNextRunMem,  doserNextRunMem,  pumpNextRunMem, microsNextRunMem);
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
void LCDDisplay::PrintDisabledAcc(NextRunMemory& feederNextRunMem, NextRunMemory& doserNextRunMem, NextRunMemory& pumpNextRunMem, NextRunMemory& microsNextRunMem) {
    int key = GetKey();
    if(key == 4) {
        _scrollIndex = 0;
        //scrolling = false;
        return;
    }

    String label = F("Acc Disabled:");
    String accsBuf = F("");
    if(!feederNextRunMem.Enabled) {
        accsBuf += F("Feeders, ");
    }
    if(!doserNextRunMem.Enabled) {
        accsBuf += F("Dry Doser, ");
    }
    if(!pumpNextRunMem.Enabled) {
        accsBuf += F("Pump, ");
    }
    if(!microsNextRunMem.Enabled) {
        accsBuf += F("Micros, ");
    }
    String accs = accsBuf.substring(0, accsBuf.length() - 2);

    if(accs != "") {
        _lcd.clear();
        PrintLine(0, label);
        PrintLine(1, accs);
        HandleScrollText(1, accs);
        return;
    }

}

void LCDDisplay::PrintRunInfo(NextRunMemory& nextRunMem) {

    int key = GetKey();
    if(key == 4) {
        _scrollIndex = 0;
        //scrolling = false;
        return;
    }

    if(!nextRunMem.Enabled) { //dont print if not enabled.
        return;
    }

    String label;
    if(nextRunMem.AccType == AccessoryType::Feeder) {
        label = F("Feeders");
    }
    else if(nextRunMem.AccType == AccessoryType::DryDoser) {
        label = F("Dosers");
    }
    else if(nextRunMem.AccType == AccessoryType::WaterPump) {
        label = F("Pump");
    }
    else if(nextRunMem.AccType == AccessoryType::MicrosDoser) {
        label = F("Micros");
    }

    //if(!nextRunMem.Enabled) {
    //_lcd.clear();
    //PrintLine(0, label);
    //PrintLine(1, F("(Disabled)"));
    //delay(_scrollDelay);
    //return;
    //}

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

    for(int i = 0; i <= 4; i++) {

        switch(i) {
            //case 0:
            //_lcd.clear();
            //PrintLine(0, nextRunText);
            //PrintLine(1, lastRun);
            //HandleScrollText(0, nextRunText);
            //break;
            //case 1:
            //_lcd.clear();
            //PrintLine(0, countDownText);
            //PrintLine(1, countDown);
            //HandleScrollText(0, countDownText);
            //break;
            case 0:
                _lcd.clear();
                PrintLine(0, runEveryText);
                PrintLine(1, nextRun);
                HandleScrollText(0, runEveryText);
                break;
            case 1:
                if(nextRunMem.AccType == AccessoryType::WaterPump) {
                    String runDurration =  F("(Not Set)");
                    if(nextRunMem.RunDurration > 0) {
                        runDurration = TimeHelpers::GetMinutesSecondsString(nextRunMem.RunDurration).c_str();
                    }

                    String runDurrationText = label + F(" Run Durration:");
                    _lcd.clear();
                    PrintLine(0, runDurrationText);
                    PrintLine(1, runDurration);
                    HandleScrollText(0, runDurrationText);
                }
                break;
            default:
                break;
        }


        //_lcd.clear();
        //delay(_scrollDelay);
        //_lcd.clear();
    }
}
void LCDDisplay::PrintInstructions() {
    _lcd.clear();
    PrintLine(0, F("Hold [Select]"));
    PrintLine(1, F("for Menu"));
    delay(_scrollDelay);
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

    if(runEvery <= 0) {
        return F("Not Set");
    }

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
    if(k >= _numOfKeys) {
        k = -1;
    }
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


