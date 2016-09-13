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
#include <erom.h>
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

    // Define a 'Storage' class that will manage EEPROM related data
    class NextRunMemoryStorage : public erom::Storage {
        protected:
            // Define rules for loading storage into RAM
            virtual void OnLoad() {
                AccType.load();
                LastRun.load();
                NextRun.load();
                CountDown.load();
                RunEvery.load();
                ShakesOrTurns.load();
                LastSave.load();
                Enabled.load();
                RunDurration.load();

            }
            // Define rules for saving storage into EEPROM
            virtual void OnSave() {
                AccType.save();
                LastRun.save();
                NextRun.save();
                CountDown.save();
                RunEvery.save();
                ShakesOrTurns.save();
                LastSave.save();
                Enabled.save();
                RunDurration.save();
            }

        public:
            // Storage data/variables
            erom::Entry<int> AccType;
            erom::Entry<long> LastRun;
            erom::Entry<long> NextRun;
            erom::Entry<long> CountDown;
            erom::Entry<long> RunEvery;
            erom::Entry<short> ShakesOrTurns;
            erom::Entry<long> LastSave;
            erom::Entry<bool> Enabled;
            erom::Entry<long> RunDurration;

            // Binding/allocating variable to EEPROM memory addresses
            NextRunMemoryStorage() {
                issue(AccType);
                issue(LastRun);
                issue(NextRun);
                issue(CountDown);
                issue(RunEvery);
                issue(ShakesOrTurns);
                issue(LastSave);
                issue(Enabled);
                issue(RunDurration);
            }
    };

    class NextRunMemory {
        private:
            long EnsureIsNumber(long num);

        public:
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
            NextRunMemoryStorage Mem;
            NextRunMemory() {
                Mem.load();
                AccType = EnsureIsNumber(Mem.AccType);
                CountDown = EnsureIsNumber(Mem.CountDown);
                Enabled = EnsureIsNumber(Mem.Enabled);
                LastRun = EnsureIsNumber(Mem.LastRun);
                LastSave = EnsureIsNumber(Mem.LastSave);
                NextRun = EnsureIsNumber(Mem.NextRun);
                RunDurration = EnsureIsNumber(Mem.RunDurration);
                RunEvery = EnsureIsNumber(Mem.RunEvery);
                ShakesOrTurns = EnsureIsNumber(Mem.ShakesOrTurns);
            }


    };
    //struct MemAddress {
    //int AccType; //id
    //int EndIndex;
    //};
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
            NextRunMemory& FindNextRunInfo(Globals::AccessoryType accType);
            NextRunMemory& AddNextRunInfo(NextRunMemory& mem);
            void ClearNextRunInfos();
    };
    extern vector<Models::NextRunMemory> NextRunInfos;
    //extern Models::NextRunMemory FeedersNextRunInfo;
    //extern Models::NextRunMemory DosersNextRunInfo;
    //extern Models::NextRunMemory PumpsNextRunInfo;


    namespace MemoryExt {
        //static vector<MemAddress> _memAddresses;

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
        NextRunMemory SaveNextRunMem(NextRunMemory mem) {
            SerialExt::Debug("--SaveNextRunMem--");

            //int index = GetUpdateIndex(mem);
            mem.Mem.LastSave = now();
            mem.Mem.save();
            //EEPROM.put(index, mem);

            delay(200); //wait for save to complete

            PrintNextRunMemory("mem.Mem_Save", mem);

            return mem;
        }
        template<typename T = void>
        NextRunMemory GetNextRunMem(NextRunMemory mem) {
            //T t(mem);

            SerialExt::Debug("--GetNextRunMem--");

            //NextRunMemory& nextRun = FindNextRunInfo(mem);

            mem.Mem.load(); //Variable to store custom object read from EEPROM.
            //nextRun.AccType = mem.Mem.AccType;

            PrintNextRunMemory("mem.Mem_Load", mem);

            return mem;
        }
        template<typename T = void>
        void Erase() {
            for(int i = 0 ; i < EEPROM.length() ; i++) {
                EEPROM.write(i, 0);
            }
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

        #pragma region OLD_STUFF
        //template<typename T = void>
        //int GetUpdateIndex(NextRunMemory mem) {
        //
        //int index = 0;
        //int memSize = sizeof(NextRunMemory);
        //
        //if(_memAddresses.size() <= 0)
        //_memAddresses.push_back(MemAddress{ mem.AccType, memSize });
        //
        ////auto& memAddress = _memAddresses[0];
        //bool foundMem = false;
        //int agregateMemSize = 0;
        //for(auto& memAddr : _memAddresses) {
        //agregateMemSize += memAddr.EndIndex; //totals incase we have to add a new one
        //if(memAddr.AccType == mem.AccType) {
        //index = memAddr.EndIndex - memSize;
        //foundMem = true;
        //break;
        //}
        //}
        //
        //if(!foundMem) { //if added, dont re-add
        //agregateMemSize += memSize;
        //_memAddresses.push_back(MemAddress{ mem.AccType, agregateMemSize });
        //index = agregateMemSize - memSize;
        //}
        //
        //return index;
        //
        //}
        #pragma endregion OLD_STUFF

    }

}

#endif

