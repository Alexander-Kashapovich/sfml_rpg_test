#pragma once

#include "GameCore/Entity/Entity.h"

class Animated : public Entity
{
protected:
    int curFrame = 0;
    sf::IntRect frame{0,0,32,32};
    
public:
    Animated(int x, int  y,int start_x,int frame_w,int frame_h) : Entity(x,y)
    {
        z += frame_h;
        frame.left = start_x;
        frame.width = frame_w;
        frame.height = frame_h;
        sprite.setTextureRect(frame);
    }
    virtual ~Animated(){};

    virtual void upd() = 0;
};