
#ifndef _LCDBASE_h
#define _LCDBASE_h

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
using namespace std;


enum LcdKeyPress {
    Right = 0,
    Up = 1,
    Down = 2,
    Left = 3,
    Select = 4,
    None = 5
};

class LCDBase : public LiquidCrystal {


    private:
        //LiquidCrystal* _lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
        //LiquidCrystal _lcd;
        int  _keyValues[5] { 50, 200, 400, 600, 800 };
        short _numOfKeys = 5;
        int _scrollDelay = 3000;

        void Init();
        int getKey();
        int getKeyFromVal(unsigned int input);

    public:

        LCDBase();
        void ClearLine(short lineNum);
        void PrintLine(short lineNum, String text);
        void HandleScrollText(short lineNum, String text);
        LcdKeyPress DetectKeyPress();
        //template<typename T>
        //void Print(short lineNum, T&& text);
        //LCDBase& operator=(const LCDBase& c);
        //LCDBase(const LCDBase& c);
};


#endif
