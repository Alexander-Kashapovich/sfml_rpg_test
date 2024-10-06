#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <type_traits>

#include "Okno.h"

template<typename T>
class ValueSwitcher;

template<typename T>
class DynamText final : public sf::Drawable
{   
    friend class ValueSwitcher<T>;
private:
    sf::Text txt;

    T* data_link = nullptr;

    std::string text_prev;
    std::string text_next;

    //если надо перебить флот в инт
    bool need_int;
    void float_impl()
    {
        txt.setString(text_prev + std::to_string(static_cast<int>(*data_link)) + text_next);
    }

    void generic_impl()
    {
        txt.setString(text_prev + std::to_string(*data_link) + text_next);
    }

public:
    DynamText(sf::Font& font,T* link,int x,int y, std::string before,std::string after,bool need = 1):
        data_link(link),
        text_prev(before),
        text_next(after),
        need_int(need)
    {
        txt.setFont(font);
        txt.setPosition(x,y);
        txt.setCharacterSize(15);
    }

    void upd()
    {
        if(std::is_same<T,float>::value && !need_int)
            float_impl();
        else
            generic_impl();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(txt);
    }
};