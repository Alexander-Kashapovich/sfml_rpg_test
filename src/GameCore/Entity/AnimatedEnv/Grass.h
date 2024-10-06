#pragma once

#include "Animated.h"

class Grass final: public Animated
{
public:
    Grass(int cell_x,int cell_y);

    void upd() override;
};