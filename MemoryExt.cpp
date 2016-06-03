#include "MemoryExt.h"


vector<Models::NextRunMemory> Utils::NextRunInfos;

//vector<Models::NextRunMemory> Utils::MemoryContainer::NextRunInfos;
//use RefreshNextRunInfo not FindNextRunInfo to get NextRunInfo
//template<typename T = Globals::AccessoryType>
NextRunMemory& Utils::MemoryContainer::FindNextRunInfo(AccessoryType accType) {
    //int sizev = NextRunInfos.size();
    for(NextRunMemory& mem : NextRunInfos) {
        if(mem.AccType == accType)
            return mem;
    }
}

bool Utils::MemoryContainer::NextRunInfoExists(AccessoryType accType) {
    for(NextRunMemory& mem : NextRunInfos) {
        if(mem.AccType == accType)
            return true;
    }
    return false;
}

NextRunMemory& Utils::MemoryContainer::AddNextRunInfo(NextRunMemory& mem) {
    NextRunInfos.push_back(mem);
    //NextRunMemory& newMem = FindNextRunInfo((AccessoryType)mem.AccType);
    return mem;
}

//extern Models::NextRunMemory Globals::FindNextRunInfo(Globals::AccessoryType accType) {
//int sizev = Globals::NextRunInfos.size();
//for(NextRunMemory& mem : Globals::NextRunInfos) {
//if(mem.AccType == accType)
//return mem;
//}
//
//}

