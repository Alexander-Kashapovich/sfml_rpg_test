#pragma once

#include "GameCore/Entity/AnimatedEnv/Animated.h"

enum Dir {d,u,l,r};

//maual deep control required
class Unit : public Animated
{
protected:
    int hp;
    int exp;

    sf::Vector2f cord;
    int dir;
    float velocity;

    int collide_radius;
public:
    Unit(int x, int y,int frame_w, int frame_h) : Animated(x,y,0,frame_w,frame_h)
    {
        cord.x = x*cell_size; 
        cord.y = y*cell_size;
    };
    virtual void act() = 0;
    ~Unit() override{};
};