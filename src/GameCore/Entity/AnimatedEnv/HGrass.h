#pragma once

#include "Animated.h"

class HGrass final: public Animated
{
public:
    HGrass(int cell_x,int cell_y);

    void upd() override;
};