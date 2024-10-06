#include "Player.h"

Player::Player(int x, int y, sf::View &_cam) : Unit(x, y, frame_width, frame_height), cam(_cam)
{
    sprite.setTextureRect(frame);
    sprite.setTexture(VFS::g().units.Chel);

    hp = 33;
    exp = 0;

    dir = d;
    velocity = 4;
}

void Player::act()
{
}

void Player::upd()
{
    frame.top = order[curFrame];
    sprite.setTextureRect(frame);

    curFrame++;
    if (curFrame == 4)
        curFrame = 0;
}

void Player::inputUpdate()
{
    static sf::Vector2f offset;
    offset = {0,0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dir = u;
        offset.y -= velocity;
        z -= velocity;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dir = d;
        offset.y += velocity;
        z += velocity;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dir = l;
        offset.x -= velocity;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dir = r;
        offset.x += velocity;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        cam.setCenter({cord.x + frame_width / 2, cord.y + frame_height});
    }

    cam.move(offset);
    frame.left = frame_width * dir;
    cord += offset;
    sprite.setPosition(cord);
}