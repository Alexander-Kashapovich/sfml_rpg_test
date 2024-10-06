#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

#include "Okno.h"

enum{norm, hover, press};

struct But_Col
{
    inline static const sf::Color norm = sf::Color(170, 120, 120, 255);
    inline static const sf::Color hover = sf::Color(220, 170, 170, 255);
    inline static const sf::Color click = sf::Color(255, 220, 220, 255);
};

class Button final : public sf::Drawable
{
private:
    sf::Rect<int> b_rect;
    float fl_x;
    float fl_y;

    sf::VertexArray VAO{sf::Quads,4};
    int b_state = norm;
    int cache_b_state = -1;

    sf::Color cur_color;
    sf::Text name;
    sf::Font& font;

    std::function<void()> action;
    
    void build(int x,int y,int w,int h);

public:
    Button(int x, int y,int w, int h, std::string b_name, std::function<void()> b_action,sf::Font& ext_font);
    
    bool check(const int m, const int& m_x, const int& m_y);
    void upd();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

