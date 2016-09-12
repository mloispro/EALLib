
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
//template<typename T>
//void LCDBase::Print(short lineNum, T&& text) {
//_lcd.setCursor(0, lineNum);
//_lcd.print(text);
//}



