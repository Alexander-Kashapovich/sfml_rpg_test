#pragma once

#include "Level.h"

namespace LevelBuilder
{
    void build(Level& lvl);

    void genBorderWalls(Level& lvl);
    void gen(Level& lvl);
};
