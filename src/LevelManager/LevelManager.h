#pragma once

#include <SFML/Graphics.hpp>

#include "Loaders/TextLoader.h"
#include "LevelBuilder.h"
#include "Level.h"
#include "UI/UIBoss.h"

class LevelManager
{
private:
    UIBoss& ui;
    LevelLoader::Interface* loader;
    
public:
    explicit LevelManager(UIBoss& ui);
    ~LevelManager(){delete loader;}

    void  goLevel(Level& lvl,int index);
    inline void save(const Level& lvl){loader->save(lvl);};
};



