#pragma once

#include "Base_InWorld.h"

class Editor final: public Base_InWorld
{
    bool key_event(sf::Event& event) override final{return true;};
    bool mouse_event(sf::Event& event) override final{return false;};
    void select_event(sf::Event& event) override final{};
    void preCycle() override final{};
    void smth_in_cycle() override final{};
public:
    Editor(Profile prof,sf::RenderWindow& window) : Base_InWorld(prof,window){}
};

