#include "Stone.h"

static constexpr int frame_width = 32;
static constexpr int frame_height = 32;
static constexpr int start_x = 0;

Stone::Stone(int x, int y) : Entity(x,y)
{
    id = EntType::Stone;

    z += frame_height;
    int frame = rand()%2;
    sprite.setTextureRect({start_x,frame*frame_width,frame_width,frame_height});
    sprite.setTexture(VFS::g().envStatAtlas);
}