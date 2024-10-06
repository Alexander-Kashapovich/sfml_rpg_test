#include "Renderer.h"

#include "SFML/OpenGL.hpp"

void Renderer::_initBuffer()
{   
    int count = level.ground.w_cell*level.ground.h_cell;
    level_VBO.create(count*4);
    level_VBO.setPrimitiveType(sf::PrimitiveType::Quads);

    sf::Vertex vertices[count*4];
    int index = 0;

    sf::Vector2f pos;
    sf::Vector2f texcord;
    //ВБО надо забивать в определенном порядке чтоб
    //можно было выбирать диапазон для отрисовки
    for (int y = 0; y < level.ground.h_chunks; y++){
    for (int x = 0; x < level.ground.w_chunks; x++){
    for (int ch_y = 0; ch_y < chunk_size; ch_y++){
    for (int ch_x = 0; ch_x < chunk_size; ch_x++){

        int tile_index = level.ground.at(x,y,ch_x,ch_y);
        
        texcord.x = tile_index*cell_size;
        texcord.y = cell_size * (rand()%4);

        pos.x = (x * chunk_size + ch_x) * cell_size;
        pos.y = (y * chunk_size + ch_y) * cell_size;
        vertices[index++] = sf::Vertex(pos, texcord);//top left

        pos.x += cell_size;
        texcord.x += cell_size;
        vertices[index++] = sf::Vertex(pos, texcord);//top right

        pos.y += cell_size;
        texcord.y += cell_size;
        vertices[index++] = sf::Vertex(pos, texcord);//bot right

        pos.x -= cell_size;
        texcord.x -= cell_size;
        vertices[index++] = sf::Vertex(pos, texcord);//bot left
    }}}}

    level_VBO.update(vertices);
}

void Renderer::_initCenter()
{
    center.setPrimitiveType(sf::PrimitiveType::Lines);
    for(int i = 0; i < 4 ; i++)
    {
        center.append(sf::Vertex());
        center[i].color = sf::Color::White;
    }        
}

void Renderer::_drawCenter()
{
    constexpr float cross_size = 5;
    auto vc = cam.getCenter();
    center[0].position = {vc.x + cross_size, vc.y - cross_size};
    center[1].position = {vc.x - cross_size, vc.y + cross_size};
    center[2].position = {vc.x + cross_size, vc.y + cross_size};
    center[3].position = {vc.x - cross_size, vc.y - cross_size};

    renderSurface.draw(center);
}

void Renderer::_drawCells()
{
    sf::VertexArray VAO{sf::PrimitiveType::Triangles};
    sf::Vertex vert;
    vert.color = sf::Color::Red;
    sf::Vector2f vec;
    constexpr int marker_cell_size = 8;

    for (int y = 0; y < level.ground.h_cell; ++y)
    {
        for (int x = 0; x < level.ground.w_cell; ++x)
        {
            vec.x = x*cell_size + marker_cell_size;
            vec.y = y*cell_size;
            vert.position = vec;
            VAO.append(vert);

            vec.x -= marker_cell_size;
            vert.position = vec;
            VAO.append(vert);

            vec.y -= marker_cell_size;
            vert.position = vec;
            VAO.append(vert);
        }
    }
    renderSurface.draw(VAO);
}

void Renderer::_drawCollis()
{
    sf::VertexArray VAO{sf::PrimitiveType::Lines};
    sf::Vertex vert;
    vert.color = sf::Color::Yellow;
    sf::Vector2f vec;

    for (int y = 0; y < level.collis.h_cell; y++)
    {
        for (int x = 0; x < level.collis.w_cell; x++)
        {
            if(level.collis.at(x,y) == Ground::Impact::WALL)
            {
                vec.x = x*cell_size;
                vec.y = y*cell_size;
                vert.position = vec;
                VAO.append(vert);

                vec.x += cell_size;
                vec.y += cell_size;
                vert.position = vec;
                VAO.append(vert);

                vec.x -= cell_size;
                vert.position = vec;
                VAO.append(vert);

                vec.y -= cell_size;
                vec.x += cell_size;
                vert.position = vec;
                VAO.append(vert);
            }
        }
    }
    renderSurface.draw(VAO);
}

void Renderer::_drawEnveroment()
{
    //update anim frame
    if(frameMeter.getElapsedTime().asMilliseconds() > 90)
    {
        frameMeter.restart();
        for(auto&& env : level.animated)
            env->upd();
    }
    
    //draw all     
    for(auto&& env : level.ents)
        renderSurface.draw(env->getSprite());

    if(drawFrameRect)
        for(auto&& env : level.ents)
        {
            renderSurface.draw(env->getRect());
            renderSurface.draw(env->getZ());
        }

}

void Renderer::_updFinalSprite()
{
    renderSurface.clear();

    renderSurface.draw(level_VBO,&groundAtlas);

    _drawEnveroment();
    if(drawCellCorner)  _drawCells();
    if(drawCollisGrid)  _drawCollis();
    if(drawCenter)      _drawCenter();

    renderSurface.display();
    finalSprite.setTexture(renderSurface.getTexture());

}

void Renderer::init()
{
    renderSurface.create(level.ground.w_cell*cell_size,level.ground.h_cell*cell_size);
    _initBuffer();
    _initCenter();
}

void Renderer::draw()
{
    window.clear(sf::Color::Black);

    _updFinalSprite();
    
    nightShader.setUniform("night",uniforms.night);

    window.draw(finalSprite,&nightShader);

    if(drawUi) 
    {
        //in default view draw only ui
        window.setView(window.getDefaultView());
        window.draw(ui.getSprite());
    }
    window.display();
}