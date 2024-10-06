#include "LevelBuilder.h"

#include "AssetsEnums.h"

#include "GameCore/Entity/Enveroment.h"

void LevelBuilder::build(Level& lvl)
{
    //индекс уже присвоен в манагере
    //8x8 max, иначе не влазит в память гпу
    lvl = Level(2,3);

    genBorderWalls(lvl);


    gen(lvl);
    lvl.upd_depths();
}

void LevelBuilder::genBorderWalls(Level& lvl)
{
        //horizontal walls
    for (int i = 0; i < lvl.ground.w_cell; i++)
    {
        lvl.ground.at(i,0) = Ground::Terra::MOOD;
        lvl.ground.at(i,lvl.ground.h_cell-1) = Ground::Terra::MOOD;

        lvl.collis.at(i,0) = Ground::Impact::WALL;
        lvl.collis.at(i,lvl.ground.h_cell-1) = Ground::Impact::WALL;
    }
    //vertical walls
    for (int i = 1; i < lvl.ground.h_cell-1; i++)
    {
        lvl.ground.at(0,i) = Ground::Terra::MOOD;
        lvl.ground.at(lvl.ground.w_cell-1,i) = Ground::Terra::MOOD;

        lvl.collis.at(0,i) = Ground::Impact::WALL;
        lvl.collis.at(lvl.ground.w_cell-1,i) = Ground::Impact::WALL;
    }
}

void LevelBuilder::gen(Level& lvl)
{
    for (size_t i = 0; i < 10; i++)
    {
        int x = (rand()%lvl.ground.w_cell) +1;
        int y = (rand()%lvl.ground.h_cell) +1;
        lvl.addAnim(new Grass{x,y});
    }

    for (size_t i = 0; i < 10; i++)
    {
        int x = (rand()%lvl.ground.w_cell) +1;
        int y = (rand()%lvl.ground.h_cell) +1;
        lvl.addAnim(new HGrass{x,y});
    }

    for (size_t i = 0; i < 4; i++)
    {
        int x = (rand()%lvl.ground.w_cell) +1;
        int y = (rand()%lvl.ground.h_cell) +1;
        lvl.add(new Stone{x,y});
    }

    for (size_t i = 0; i < 3; i++)
    {
        int x = (rand()%lvl.ground.w_cell) +1;
        int y = (rand()%lvl.ground.h_cell) +1;
        lvl.addUnit(new Chel{x,y});
    }
    
}