#pragma once

#include "Base_InWorld.h"
#include "GameCore/Player.h"

class Game final : public Base_InWorld
{
    bool key_event(sf::Event& event) override final;
    bool mouse_event(sf::Event& event) override final;
    void select_event(sf::Event& event) override final;
    void preCycle() override final;
    void smth_in_cycle() override final;

    Player* pl;

public: 
    Game(Profile prof,sf::RenderWindow& window);
};
