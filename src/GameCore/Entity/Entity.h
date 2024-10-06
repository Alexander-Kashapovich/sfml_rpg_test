#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsEnums.h"
#include "VFS.h"

constexpr int cell_size = 32;

class Entity
{
protected:
    sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::CircleShape z_shape{3,4};

public:
    float z;
    EntType id = EntType::Zero;

    Entity(int x, int y)
    {
        sprite.setPosition({(float)(x*cell_size),(float)(y*cell_size)});
        z = y*cell_size;
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1);
        z_shape.setFillColor(sf::Color::Red);
    }
    virtual ~Entity(){};
    inline sf::Sprite& getSprite(){return sprite;}

    sf::RectangleShape& getRect()
    {
        rect.setPosition(sprite.getPosition());
        rect.setSize(sprite.getGlobalBounds().getSize());
        return rect;
    }
    sf::CircleShape& getZ()
    {
        z_shape.setPosition({sprite.getPosition().x,z});
        return z_shape;
    }

};