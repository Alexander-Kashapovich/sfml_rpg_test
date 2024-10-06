#include "Chel.h"

static constexpr int frame_width = 128;
static constexpr int frame_height = 128;
static constexpr int order[4]{0,1*frame_height,0,2*frame_height};

Chel::Chel(int x, int y) : Unit(x,y,frame_width,frame_height)
{
    sprite.setTexture(VFS::g().units.Chel);

    id = EntType::Chel;
    
    hp = 50;
    exp = 0;

    dir = d;
    velocity = 20;
}

void Chel::upd()
{
    frame.top = order[curFrame];
    sprite.setTextureRect(frame);

    curFrame++;
    if(curFrame == 4)
        curFrame = 0;
}

void Chel::act()
{
    dir = rand()%10;

    if (dir < 4)
    {
        frame.left = frame_width*dir;
        sf::Vector2f offset{0,0};
        switch (dir)
        {
            case u: offset.y -= velocity; z -= velocity; break;
            case d: offset.y += velocity; z += velocity; break;
            case r: offset.x += velocity; break;
            case l: offset.x -= velocity; break;
        }
        sprite.move(offset);
    }
}