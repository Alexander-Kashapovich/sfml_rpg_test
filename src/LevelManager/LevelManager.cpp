#include "LevelManager.h"

LevelManager::LevelManager(UIBoss& ui): 
    ui(ui),
    loader(new LevelLoader::TextLoader)
    {}

void LevelManager::goLevel(Level& lvl, int index)
{
    //same check
    if(index == lvl.ID)
        ui.out("this is same");
    else
    {
        if(lvl.ID != BUILD_NEW_LVL)
        {
            //save prev lvl
            loader->save(lvl);
            ui.out("lvl " + std::to_string(lvl.ID) + " saved");
        }
        
        ui.out("go level "+std::to_string(index));
        Level next_lvl = loader->load(index);
        //if loader ret no-exist lvl
        if(next_lvl.ID == BUILD_NEW_LVL)
        {
            next_lvl.ID = index;
            ui.out("build new level "+std::to_string(next_lvl.ID));
            LevelBuilder::build(next_lvl);
        }
        ////////safe_line//////////
        lvl = std::move(next_lvl);
    }
}

    