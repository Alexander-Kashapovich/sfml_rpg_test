#pragma once

#include <SFML/Graphics.hpp>

#include "LevelManager/Level.h"
#include "UI/UIBoss.h"
#include "Okno.h"

#include "VFS.h"

struct Uniforms
{
    float night = 0.5;
};

class Renderer
{
private:
    Level& level;
    UIBoss& ui;
    sf::View& cam;
    sf::Clock frameMeter;

    sf::VertexArray center;
    sf::VertexBuffer level_VBO;
    sf::VertexBuffer statObjVBO;
    sf::RenderTexture renderSurface;
    sf::Sprite finalSprite;
    
    sf::Texture& groundAtlas;
    sf::RenderWindow& window;

    sf::Shader& nightShader;

    public:
    Uniforms uniforms;
    private:

    void _drawCells();
    void _drawCollis();
    void _drawCenter();


    void _drawEnveroment();

    void _updFinalSprite();

    void _initBuffer();

    void _initCenter();
public:
    Renderer(Level& lvl,UIBoss& _ui,sf::RenderWindow& win,sf::View& _cam) : 
        level(lvl),
        ui(_ui),
        cam(_cam),
        window(win),
        groundAtlas(VFS::g().groundAtlas),
        nightShader(VFS::g().shaders.night)
        {
            nightShader.setUniform("night",uniforms.night);
        }

    void init();

    void draw();
//flags
    bool drawUi = true;
    bool drawCenter = true;

    bool drawCellCorner = false;
    bool drawCollisGrid = false;
    bool drawFrameRect = false;
};

