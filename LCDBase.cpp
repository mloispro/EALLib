
#include "LCDBase.h"


//LCDBase::LCDBase(): _lcd(8, 9, 4, 5, 6, 7) {
//Init();
//}

LCDBase::LCDBase(): LiquidCrystal(8, 9, 4, 5, 6, 7) {
    Init();
}

void LCDBase::Init() {
    begin(16, 2);
    clear();
    setCursor(0, 0);

}
void LCDBase::ClearLine(short lineNum) {
    setCursor(0, lineNum);
    print(F("                "));
}
void LCDBase::PrintLine(short lineNum, String text) {
    ClearLine(lineNum);
    setCursor(0, lineNum);
    print(text);
}
//template<typename T>
//void LCDBase::Print(short lineNum, T&& text) {
//_lcd.setCursor(0, lineNum);
//_lcd.print(text);
//}
void LCDBase::HandleScrollText(short lineNum, String text) {
    delay(200);
    if(text.length() > 16) {

        static unsigned long printTime = millis();
        if(millis() - printTime > _scrollDelay) {

            int pos = (text.length() * -1) - 12;
            for(int i = 0; i < text.length() - 12; i++) {
                pos += 1;
                setCursor(0, lineNum);
                print("                 ");
                setCursor(pos, lineNum);
                print(text);
                //IsKeyPressed();
                //if(_optionChanged && _selectedMenuId > -1) {
                //PrintLine(0, _menuText);
                //PrintLine(1, _optionText);
                //return;
                //}

                delay(300);
            }
            setCursor(0, lineNum);
            print(text);
            //delay(500);
            //delay(_scrollDelay);
            printTime = millis();
        }
    }
    else {
        PrintLine(lineNum, text);
    }
    //delay(_scrollDelay);
}
LcdKeyPress LCDBase::DetectKeyPress() {
    int key = getKey();
    //SerialExt::Debug("key_dkp:", key);

    if(key == 0 || key == 1 || key == 2 || key == 3 || key == 4) {
        //_optionChanged = true;
    }


    switch(key) {
        case 0: //right
            return LcdKeyPress::Right;
        case 1: //up
            return LcdKeyPress::Up;
        case 2: //down
            return LcdKeyPress::Down;
        case 3: //left
            return LcdKeyPress::Left;
        case 4: //select
            return LcdKeyPress::Select;
        default:
            return LcdKeyPress::None;

    }
}

//--key press
int LCDBase::getKeyFromVal(unsigned int input) {
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

int LCDBase::getKey() {
    int keyVal = analogRead(0);
    //SerialExt::Debug(F("keyVal"), keyVal);
    int key = getKeyFromVal(keyVal);
    //SerialExt::Debug(F("key"), key);
    //_lastKey = key;
    return key;
}


