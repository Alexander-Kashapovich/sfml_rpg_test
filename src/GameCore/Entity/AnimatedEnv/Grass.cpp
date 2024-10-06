#include "Grass.h"

static constexpr int frame_width = 32;
static constexpr int frame_height = 32;
static constexpr int start_x = 0;

static constexpr int order[4]{0,1*frame_height,2*frame_height,1*frame_height};

Grass::Grass(int cell_x,int cell_y) : Animated(cell_x,cell_y,start_x,frame_width,frame_height)
{
    id = EntType::Grass;

    curFrame = rand()%4;
    sprite.setTexture(VFS::g().envAnimAtlas);
}

void Grass::upd()
{
    frame.top = order[curFrame];
    sprite.setTextureRect(frame);

    curFrame++;
    if(curFrame == 4)
        curFrame = 0;
}
