#pragma once

#include "LevelManager/Level.h"

namespace LevelLoader
{
class Interface
{
public:
    //Always return. If no exist, lvl.ID = -1
    virtual Level load(int index) = 0;
    virtual void save(const Level& level) = 0;

    virtual ~Interface() = default;
};
}