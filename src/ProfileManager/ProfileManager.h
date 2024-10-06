#pragma once

#include "Profile.h"
#include "Prof_preview.h"

#include "LoaderJSON.h"

class ProfileManager
{
private:
    I_ProfileLoader*  loader;

    //костыль чтобы не загружать все профайлы сразу, а только их превью
    int curProfileID = 0;
    std::unordered_map<int,Prof_preview> table;

public:
    ProfileManager() : loader(new LoaderJSON){loader->loadTable(table);};
    ~ProfileManager(){delete loader;}

    inline std::string getName(int profile_ID)      {return table[profile_ID].name;}
    inline int getLevelID(int profile_ID)           {return table[profile_ID].curLevel;}
    inline Profile getCurProfile()                  {return loader->load(curProfileID);}

    inline int* getLinkCurProfile()                 {return &curProfileID;}

    inline void setProfile(int profile_ID)          {curProfileID = profile_ID;}
};


