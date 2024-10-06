#pragma once

#include <unordered_map>

#include "Prof_preview.h"
#include "Profile.h"

struct I_ProfileLoader
{
    virtual void loadTable(std::unordered_map<int, Prof_preview> &table) = 0;

    virtual Profile load(int profile_ID) = 0;
    virtual void save(int profile_ID) = 0;

    virtual ~I_ProfileLoader() = default;
};

