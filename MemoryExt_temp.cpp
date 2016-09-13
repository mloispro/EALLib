#include "MemoryExt.h"


//using namespace Models;

//Models::NextRunMemory Utils::FeedersNextRunInfo;
//Models::NextRunMemory Utils::DosersNextRunInfo;
//Models::NextRunMemory Utils::PumpsNextRunInfo;
vector<Models::NextRunMemory> Utils::NextRunInfos;


//Models::NextRunMemory::NextRunMemory() {
////load vars from eeprom
//Mem.load();
//AccType = EnsureIsNumber(Mem.AccType);
//CountDown = EnsureIsNumber(Mem.CountDown);
//Enabled = EnsureIsNumber(Mem.Enabled);
//LastRun = EnsureIsNumber(Mem.LastRun);
//LastSave = EnsureIsNumber(Mem.LastSave);
//NextRun = EnsureIsNumber(Mem.NextRun);
//RunDurration = EnsureIsNumber(Mem.RunDurration);
//RunEvery = EnsureIsNumber(Mem.RunEvery);
//ShakesOrTurns = EnsureIsNumber(Mem.ShakesOrTurns);
//}

long Models::NextRunMemory::EnsureIsNumber(long num) {
    if(isnan(num)) {
        num = 0;
    }
    return num;
}

//vector<Models::NextRunMemory> Utils::MemoryContainer::NextRunInfos;
//use RefreshNextRunInfo not FindNextRunInfo to get NextRunInfo
//template<typename T = Globals::AccessoryType>
NextRunMemory & Utils::MemoryContainer::FindNextRunInfo(AccessoryType accType) {
    //int sizev = NextRunInfos.size();
    for(NextRunMemory& mem : NextRunInfos) {
        if(mem.AccType == accType) {
            return mem;
        }
    }
}

bool Utils::MemoryContainer::NextRunInfoExists(AccessoryType accType) {
    for(NextRunMemory& mem : NextRunInfos) {
        if(mem.AccType == accType) {
            return true;
        }
    }
    return false;
}

NextRunMemory& Utils::MemoryContainer::AddNextRunInfo(NextRunMemory & mem) {
    NextRunInfos.push_back(mem);
    //NextRunMemory& newMem = FindNextRunInfo((AccessoryType)mem.AccType);
    return mem;
}

void Utils::MemoryContainer::ClearNextRunInfos() {
    NextRunInfos.clear();
}



