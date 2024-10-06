#pragma once

#include "Unit.h"

class Chel final : public Unit
{
private:
public:
    Chel(int x, int y);
    ~Chel() override {};
    void upd() override final;
    void act() override final;
};

