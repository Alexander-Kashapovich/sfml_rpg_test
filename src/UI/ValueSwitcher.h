#pragma once

#include <SFML/Graphics.hpp>

#include "Button.h"
#include "DynamText.h"

template<typename T>
class ValueSwitcher final : public sf::Drawable
{
private:
    DynamText<T> val;
    Button incr;
    Button decr;

public:
    ValueSwitcher(sf::Font& font,std::string name, T* link,T val,int x, int y) : 
        val(font,link,x,y,name,"",1),
        incr(x + 50,y+30,40,20,"++",

        [link,val](){(*link) += val;},

        font),
        decr(x,y+30,40,20,"--",
        
        [link,val](){(*link) -= val;},
        
        font)
        {}

    void upd()
    {
        val.upd();
        incr.upd();
        decr.upd();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(val);
        target.draw(incr);
        target.draw(decr);
    }

    inline bool check(int m,int mx, int my){return 
        (   
            incr.check(m,mx,my) || decr.check(m,mx,my)
        );}
};
