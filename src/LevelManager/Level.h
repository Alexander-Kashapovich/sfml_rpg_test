#pragma once

#include <vector>

#include "AssetsEnums.h"

#include "GameCore/Entity/Entity.h"
#include "GameCore/Entity/AnimatedEnv/Animated.h"
#include "GameCore/Entity/Unit/Unit.h"

constexpr int chunk_size = 16;
constexpr int BUILD_NEW_LVL = -1;

//bottom layer of lvl. Storage of indexes;
struct Grid
{
    int w_chunks,h_chunks;
    int w_cell,h_cell;
    std::vector<int> _data;

    Grid(int chunk_col, int chunk_row);
    Grid(Grid&& oth);
    Grid& operator=(Grid&& r);

    Grid(const Grid& oth) = delete;
    Grid& operator=(const Grid& r) = delete;

    //access throw all layer
    int& at(int x, int y,int ch_x, int ch_y);
    //vec-like access
    int& at(int x,int y);
};

struct Level
{
    int ID = BUILD_NEW_LVL;
    Grid ground;
    Grid collis;

    std::vector<Entity*> ents;
    std::vector<Animated*> animated;
    std::vector<Unit*> units;

    inline void add(Entity* ent)        {ents.push_back(ent);}
    inline void addAnim(Animated* ent)  {ents.push_back(ent); animated.push_back(ent);}
    inline void addUnit(Unit* ent)       {ents.push_back(ent); animated.push_back(ent); units.push_back(ent);}

    inline void upd_depths()
    {
        std::sort(ents.begin(),ents.end(),[](Entity* a, Entity* b){return a->z < b->z;});
    }
//tors
    Level();
    //@brief zero filled 
    //@param w  width in chunks 
    //@param h  height in chunks 
    Level(int w,int h);
    Level(Level&& oth);
    Level& operator=(Level&& r);

    Level(const Level& oth) = delete;
    Level& operator=(const Level& r) = delete;

    ~Level();
};

