#pragma once

#include "I_ProfileLoader.h"


struct LoaderJSON final : public I_ProfileLoader
{
    void loadTable(std::unordered_map<int,Prof_preview> &table) override;

    Profile load(int profile_ID) override;
    void save(int profile_ID) override;
};


