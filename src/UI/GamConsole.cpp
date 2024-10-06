#include "GamConsole.h"

GamConsole::GamConsole(sf::Font& font,int x,int y)
{
    txt.setFont(font);
    txt.setCharacterSize(15);
    txt.setPosition(sf::Vector2f(x,y));

    it = buff.begin();
}

void GamConsole::out(std::string&& msg)
{
    isChange = 1;
    if(msg.size()  > max_str_len){msg ="too large";}
    
    if(it == buff.end()){it = buff.begin();}

    *it = msg;
    ++it;
}

std::string GamConsole::getStr()
{
    isChange = 0;
    //в дюбом случае надо будет переписать всю строку
    std::string tmp;
    //а может и не надо

    //!надо покрутить итераторы стринга

#if 0
    //не удалось обнаружить вляния на перфоманс
    tmp.reserve(max_str_len*GamConsole_size);
#endif

    for(int i = 0; i < GamConsole_size; ++i)
    {
        if(it == buff.end()){it = buff.begin();}

        tmp += *it;
        tmp += "\n";
        ++it;
    }

    return tmp;
}

void GamConsole::upd()
{
    if(isChange)
     txt.setString(getStr());
}

void GamConsole::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(txt);
}

void GamConsole::clear()
{
    buff.fill("");
    isChange = true;
}