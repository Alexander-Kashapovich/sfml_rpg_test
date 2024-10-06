#include "UIBoss.h"
#include <string>

#include "VFS.h"

UIBoss::UIBoss(bool drawField):
    font(VFS::g().font),
    console(font,20,SCREEN_HEIGHT-GamConsole_size*15)
{

    texture.create(SCREEN_WIDTH,SCREEN_HEIGHT);
    #define panel_color sf::Color(50,50,50,150)

    top.setFillColor(panel_color);
    left.setFillColor(panel_color);
    right.setFillColor(panel_color);
    bot.setFillColor(panel_color);

    if(drawField)
        gamefield.setOutlineColor(sf::Color(255,255,255,255));
    else
        gamefield.setOutlineColor(sf::Color::Transparent);

    gamefield.setOutlineThickness(1);
    gamefield.setFillColor(sf::Color::Transparent);

    build();
}

void UIBoss::build()
{
    #define top_panel_h 80
    #define bot_panel_h 110
    #define left_panel_w 150
    #define right_panel_w 150

    top.setPosition(0,0);
    left.setPosition(0,top_panel_h);
    right.setPosition(SCREEN_WIDTH - right_panel_w,top_panel_h);
    bot.setPosition(left_panel_w,SCREEN_HEIGHT - bot_panel_h);
    gamefield.setPosition(left_panel_w,top_panel_h );


    top.setSize(sf::Vector2f(SCREEN_WIDTH,top_panel_h));
    left.setSize(sf::Vector2f(left_panel_w,SCREEN_HEIGHT - top_panel_h));
    right.setSize(sf::Vector2f(right_panel_w,SCREEN_HEIGHT - top_panel_h));
    bot.setSize(sf::Vector2f(SCREEN_WIDTH-left_panel_w-right_panel_w,SCREEN_HEIGHT-top_panel_h-bot_panel_h));
    gamefield.setSize(sf::Vector2f
    (
        SCREEN_WIDTH - left_panel_w - right_panel_w,
        SCREEN_HEIGHT - bot_panel_h - top_panel_h
    )
    );
}

bool UIBoss::check_buttons(int m,int mx, int my)
{   
    if(!butts.empty())
        for(auto& butt : butts)
        {
            if(butt.check(m,mx,my))
                return 1;
        }

    if(!switchers_i.empty())
        for(auto& switcher : switchers_i)
        {
            if(switcher.check(m,mx,my))
                return 1;
        }

    if(!switchers_f.empty())
        for(auto& switcher : switchers_f)
        {
            if(switcher.check(m,mx,my))
                return 1;
        }
    return 0;
}

sf::Sprite UIBoss::getSprite()
{
    texture.clear(sf::Color::Transparent);
    
    texture.draw(top);
    texture.draw(left);
    texture.draw(right);
    texture.draw(bot);
    texture.draw(gamefield);

    for(auto& txt : txts)             {                 texture.draw(txt);}
    for(auto& but : butts)            {but.upd();       texture.draw(but);}
    for(auto& dtxt : dtxts_i)         {dtxt.upd();      texture.draw(dtxt);}
    for(auto& dtxt : dtxts_f)         {dtxt.upd();      texture.draw(dtxt);}
    for(auto& switcher : switchers_i) {switcher.upd();  texture.draw(switcher);}
    for(auto& switcher : switchers_f) {switcher.upd();  texture.draw(switcher);}

    console.upd();
    texture.draw(console);

    texture.display();

    return sf::Sprite(texture.getTexture());
}

void UIBoss::add_txt(std::string txt)
{
    #define txt_left_magrin 20
    #define txt_h 15
    sf::Text tmp{txt,font,20};
    tmp.setPosition(sf::Vector2f(
        txt_left_magrin,
        txts.size()*txt_h + top_panel_h
        )
    );
    txts.push_back(std::move(tmp));
}

void UIBoss::add_butt(int x, int y, std::string b_name, std::function<void()> b_action)
{
    #define button_w 80
    #define button_h 40
    butts.push_back(Button(x,y,button_w,button_h,b_name,b_action,font));
}

void UIBoss::add_butt(float x, float y, std::string b_name, std::function<void()> b_action)
{
    butts.push_back(Button(x*SCREEN_WIDTH,y*SCREEN_HEIGHT,button_w,button_h,b_name,b_action,font));
}

void UIBoss::add_butt(std::string b_name, std::function<void()> b_action)
{

    #define butt_max_row 2
    int col = panel_butts_count / butt_max_row;
    int row = panel_butts_count % butt_max_row;

    #define button_cell_w 100
    #define button_cell_h 50

    #define butt_bot_margin bot_panel_h + 5
    #define butt_left_margin left_panel_w + 5

    butts.push_back(Button(
        butt_left_margin + col*button_cell_w,
        SCREEN_HEIGHT - butt_bot_margin + row*button_cell_h,
        button_w,button_h,
        b_name,b_action,font));

    panel_butts_count++;
    
}

void UIBoss::clear()
{
    txts.clear();
    dtxts_i.clear();
    dtxts_f.clear();
    butts.clear();
    switchers_i.clear();
    switchers_f.clear();
    console.clear();
}