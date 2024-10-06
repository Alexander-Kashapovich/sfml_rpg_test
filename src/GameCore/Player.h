#pragma once

#include "Entity/Unit/Unit.h"
static constexpr int frame_width = 128;
static constexpr int frame_height = 128;

class Player final : public Unit
{
private:
    sf::View& cam;

    static constexpr int order[4]{0,1*frame_height,0,2*frame_height};

public:
    Player(int x, int y,sf::View& _cam);

    void inputUpdate();
    void upd() override final;
    void act() override final;

    inline sf::Vector2f getCenter(){return {cord.x + frame_width / 2, cord.y + frame_height};}
};
