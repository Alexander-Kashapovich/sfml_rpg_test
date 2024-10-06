#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <array>

#include "Okno.h"

#define GamConsole_size 20
#define max_str_len 30

class GamConsole final : public sf::Drawable
{
private:
    sf::Text txt;
    std::string* it;
    std::array<std::string,GamConsole_size> buff;

    std::string getStr();
    bool isChange = 0;
    
public:
    GamConsole(sf::Font& font,int x,int y);

    void out(std::string&& msg);
    void upd();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void clear();
};

