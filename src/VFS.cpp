#include "VFS.h"

#include <iostream>

VFS::VFS()
{
    font.loadFromFile("res/Fonts/sample.ttf");
    groundAtlas.loadFromFile("res/Atlases/groundAtlas.png");
    envAnimAtlas.loadFromFile("res/Atlases/envAnimAtlas.png");
    envAnimAtlasTwo.loadFromFile("res/Atlases/envAnimAtlasTwo.png");
    envStatAtlas.loadFromFile("res/Atlases/envStatAtlas.png");

    shaders.night.loadFromFile
    (   
        "res/Shaders/night.vert",
        "res/Shaders/night.frag"
    );
    shaders.night.setUniform("texture", sf::Shader::CurrentTexture);
    
    units.Chel.loadFromFile("res/UnitSprites/Chel.png");
}