
#ifndef _LCDBASE_h
#define _LCDBASE_h

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include <erom.h>

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>
using namespace std;


class LCDBase : public LiquidCrystal {

    private:
        //LiquidCrystal* _lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
        //LiquidCrystal _lcd;

        void Init();
    public:

        LCDBase();
        void ClearLine(short lineNum);
        //template<typename T>
        //void Print(short lineNum, T&& text);
};


#endif
