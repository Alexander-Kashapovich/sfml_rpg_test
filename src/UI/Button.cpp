#include "Button.h"

Button::Button(int x, int y,int w, int h, std::string b_name, std::function<void()> b_action,sf::Font& ext_font) :
    font(ext_font),
    action(b_action)
{
    name.setFont(font);
    name.setFillColor(sf::Color{255,255,255,255});
    name.setString(b_name);
    name.setCharacterSize(15);

    build(x,y,w,h);
}

void Button::build(int x,int y,int w,int h)
{
    VAO[0] = sf::Vertex(sf::Vector2f(x,y),But_Col::norm);
    VAO[1] = sf::Vertex(sf::Vector2f(x+w,y),But_Col::norm);
    VAO[2] = sf::Vertex(sf::Vector2f(x+w,y+h),But_Col::norm);
    VAO[3] = sf::Vertex(sf::Vector2f(x,y+h),But_Col::norm);

    b_rect = {x,y,w,h};

    name.setPosition
    (
        x + w/2 - name.getGlobalBounds().width/2,
        y + h/2 - name.getGlobalBounds().height
    );

    fl_x = (float)x/SCREEN_WIDTH;
    fl_y = (float)y/SCREEN_HEIGHT;

}

bool Button::check(const int m,const int& m_x, const int& m_y)
{

    if
    (
        m_x > b_rect.left &&
        m_x < b_rect.left + b_rect.width &&
        m_y > b_rect.top &&
        m_y < b_rect.top + b_rect.height
    )
    {
        if (m) 
        {
            action();
            b_state = press;
            return 1;
        }
        else b_state = hover;
        return 1;
    }
    else b_state = norm;
    return 0;
}

void Button::upd()
{
    if (cache_b_state != b_state)
    {
        if (b_state == norm)        {cur_color = But_Col::norm;}
        else if (b_state == hover)  {cur_color = But_Col::hover;}
        else if (b_state ==  press) {cur_color = But_Col::click;}

        cache_b_state = b_state;

        VAO[1].color = cur_color;
        VAO[2].color = cur_color;
        VAO[3].color = cur_color;

    }
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(VAO);
    target.draw(name);
}