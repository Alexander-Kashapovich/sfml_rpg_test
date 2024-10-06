#pragma once

#include "GameCore/Entity/Entity.h"

class Stone final : public Entity
{
public:
    Stone(int x, int y);
    ~Stone() override = default;
};