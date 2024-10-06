#include "LoaderJSON.h"

void LoaderJSON::loadTable(std::unordered_map<int,Prof_preview> &table)
{
    #define max_profile 3
    
    for(int i = 0;i <= max_profile;++i)
    {
        table[i].name = "prof " + std::to_string(i+1);
        table[i].curLevel = 0;
    }
}

Profile LoaderJSON::load(int profile_ID)
{
    Profile tmp;

    tmp.ID = profile_ID;
    
    return tmp;
}

void LoaderJSON::save(int profile_ID)
{

}