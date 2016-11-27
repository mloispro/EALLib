// SerialExt.h

#ifndef EEPROMMEM_h
#define EEPROMMEM_h

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <string>
#include <vector>
using namespace std;

//#include <TimeLib.h>
#include <Time.h>
#include <EEPROM.h>
//#include <EEPROMVar.h>
//#include <EEPROMex.h>
#include <MemoryFree.h>

#include "_globals.h"
#include "SerialExt.h"
//#include "RTCExt.h"
using namespace Utils;
//using namespace Models;
using namespace Globals;

namespace Models {

    struct NextRunMemory {
        //short Pin = -1;
        int AccType = 0; //id
        long LastRun = 0;
        long NextRun = 0;
        long CountDown = 0;
        long RunEvery = 0;
        short ShakesOrTurns = -1;
        long LastSave = 0;
        bool Enabled = false;
        long RunDurration = 0;
        int RunDurrationOption = -1;
    };
    struct MemAddress {
        int AccType; //id
        int EndIndex;
    };
}
namespace Utils {
    using namespace Models;

    class MemoryContainer {
        private:

        public:
            //extern vector<Models::NextRunMemory> _nextRunInfos;
            MemoryContainer() {};

            bool NextRunInfoExists(AccessoryType accType);
            //template<typename T = Globals::AccessoryType>
            NextRunMemory& FindNextRunInfo(AccessoryType accType);
            NextRunMemory& AddNextRunInfo(NextRunMemory& mem);
            void ClearNextRunInfos();
    };
    extern vector<Models::NextRunMemory> NextRunInfos;


    namespace MemoryExt {
        static vector<MemAddress> _memAddresses;

        template<typename T = String, typename M = NextRunMemory>
        void PrintNextRunMemory(T && label, M && mem) {
            //SerialExt::Debug(F("mem"), label);
            //SerialExt::Debug(F("Pin"), mem.Pin);
            //SerialExt::Debug(F("AccType"), mem.AccType);
            //SerialExt::Debug(F("CountDown"), mem.CountDown);
            //SerialExt::Debug(F("LastRun"), mem.LastRun);
            //SerialExt::Debug(F("LastSave"), mem.LastSave);
            //SerialExt::Debug(F("NextRun"), mem.NextRun);
            //SerialExt::Debug(F("RunEvery"), mem.RunEvery);
            //SerialExt::Debug(F("ShakesOrTurns"), mem.ShakesOrTurns);
        }

        template<typename T = void>
        int GetUpdateIndex(NextRunMemory mem) {

            int index = 0;
            int memSize = sizeof(NextRunMemory);

            if(_memAddresses.size() <= 0)
                _memAddresses.push_back(MemAddress{ mem.AccType, memSize });

            //auto& memAddress = _memAddresses[0];
            bool foundMem = false;
            int agregateMemSize = 0;
            for(auto& memAddr : _memAddresses) {
                agregateMemSize += memAddr.EndIndex; //totals incase we have to add a new one
                if(memAddr.AccType == mem.AccType) {
                    index = memAddr.EndIndex - memSize;
                    foundMem = true;
                    break;
                }
            }

            if(!foundMem) { //if added, dont re-add
                agregateMemSize += memSize;
                _memAddresses.push_back(MemAddress{ mem.AccType, agregateMemSize });
                index = agregateMemSize - memSize;
            }

            return index;

        }

        template<typename T = void>
        NextRunMemory SaveNextRunMem(NextRunMemory mem) {
            SerialExt::Debug("--SaveNextRunMem--");

            int index = GetUpdateIndex(mem);
            mem.LastSave = now();

            EEPROM.put(index, mem);

            delay(200); //wait for save to complete

            PrintNextRunMemory("eEEPROMmem_Save", mem);

            return mem;
        }
        template<typename T = void>
        NextRunMemory GetNextRunMem(NextRunMemory mem) {
            //T t(mem);

            SerialExt::Debug("--GetNextRunMem--");

            int index = GetUpdateIndex(mem); //Move address to the next byte.

            NextRunMemory eEEPROMmem; //Variable to store custom object read from EEPROM.
            EEPROM.get(index, eEEPROMmem);
            eEEPROMmem.AccType = mem.AccType;

            PrintNextRunMemory("eEEPROMmem_Get", eEEPROMmem);

            return eEEPROMmem;
        }
        template<typename T = void>
        void Erase() {
            for(int i = 0 ; i < EEPROM.length() ; i++) {
                EEPROM.write(i, 0);
            }
        }

        //todo: these eeprom methods need to replace the ones above.
        //http://playground.arduino.cc/Code/EEPROMWriteAnything
        template <class T> int EEPROM_writeAnything(int ee, const T& value) {
            const byte* p = (const byte*)(const void*)&value;
            unsigned int i;
            for (i = 0; i < sizeof(value); i++) {
                EEPROM.write(ee++, *p++);
            }
            return i;
        }

        template <class T> int EEPROM_readAnything(int ee, T& value) {
            byte* p = (byte*)(void*)&value;
            unsigned int i;
            for (i = 0; i < sizeof(value); i++) {
                *p++ = EEPROM.read(ee++);
            }
            return i;
        }
        //retuns first if none have been saved.
        //MemAddress& MemoryController::FindAddress(AccessoryType accType){
        //
        //	if (_memAddresses.size() <= 0)
        //		_memAddresses.push_back(MemAddress{ accType, 0 });
        //
        //	auto& memAddress = _memAddresses[0];
        //	for (auto& mem : _memAddresses)
        //	{
        //		if (mem.AccType == accType)
        //			return mem;
        //	}
        //
        //	return memAddress;
        //}


        template<typename T>
        extern void PrintFreeMemory(T&& text) {
            T t(text);

            String msg = String(" - ") + text;
            int mem = freeMemory();
            Serial.print(msg);
            Serial.print(F("Free Mem : "));
            Serial.println(mem);

        }
        template<typename T = void>
        extern String GetFreeMemory() {
            int totalMem = 256; //mega has 256kb or 256000b
            int mem = freeMemory();
            int memKB = mem / 1000;
            String total = String(memKB) + "kb out of " + String(totalMem) + "kb";

            return total;

        }

        //static String GetFreeRam() {
        //
        //extern int __heap_start, *__brkval;
        //int v;
        //int freeRam = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
        //
        //String total = String(freeRam);
        //
        //return total;
        //
        //}

    }

}

#endif

