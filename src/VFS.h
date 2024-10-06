#pragma once

#include "SFML/Graphics.hpp"

#include "AssetsEnums.h"

struct Units
{
    sf::Texture Chel;
};

struct Shaders
{
    sf::Shader night;
};

class VFS
{
private:

    VFS();
public:
//ctors

    VFS(const VFS& oth) = delete;

    static VFS& g()
    {
        static VFS vfs;
        return vfs;
    }
//getters
    
    sf::Texture groundAtlas;
    sf::Texture envAnimAtlas;
    sf::Texture envAnimAtlasTwo;
    sf::Texture envStatAtlas;

    Shaders shaders;
    Units units;
    sf::Font font;
};