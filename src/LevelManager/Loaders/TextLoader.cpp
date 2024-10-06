#include "TextLoader.h"

#include <iostream>
namespace LevelLoader
{

Level TextLoader::load(int index)
{
    Level level;

    fs::path load_path = fs::path("levels") / ("level_" + std::to_string(index) + ".lvl");

    std::ifstream inFile(load_path, std::ios::binary);
    
    if (!inFile)
    {
        level.ID = BUILD_NEW_LVL;
        return level;
    }

    //start load
    level.ID = index;

    inFile.close();
    return level;
}

void TextLoader::save(const Level& level)
{
    fs::path save_path = fs::path("levels") / ("level_" + std::to_string(level.ID) + ".lvl");

    std::ofstream outFile(save_path);

    if (!outFile) {return;}
    
    //start save

    for (Entity* ent : level.ents)
    {
        if (Unit* unit = dynamic_cast<Unit*>(ent))
        {
            EntType entityType = unit->id;
            outFile.write(reinterpret_cast<const char*>(&entityType), sizeof(entityType));
            outFile.write(reinterpret_cast<const char*>(unit), sizeof(Unit));
        }
        else if (Animated* anim = dynamic_cast<Animated*>(ent))
        {
            EntType entityType = anim->id;
            outFile.write(reinterpret_cast<const char*>(&entityType), sizeof(entityType));
            outFile.write(reinterpret_cast<const char*>(anim), sizeof(Animated));
        }
        else
        {
            EntType entityType = ent->id;
            outFile.write(reinterpret_cast<const char*>(&entityType), sizeof(entityType));
            outFile.write(reinterpret_cast<const char*>(ent), sizeof(Entity));
        }
    }

    outFile.close();
    std::cout<<"lvl "<<std::to_string(level.ID)<< " save"<<std::endl;
}
}