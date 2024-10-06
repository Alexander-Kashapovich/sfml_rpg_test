#include "MenuStateSwitcher.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Editor.h"
#include "Game.h"

#include "Okno.h"

void MenuStateSwitcher::event_check()
{
    sf::Event event;

    while(window.pollEvent(event)) 
    {   
        if (event.type == sf::Event::Closed) {state  = quit;}
        else if (event.type == sf::Event::LostFocus){time->setFPSUnfocus();}
        else if (event.type == sf::Event::GainedFocus){time->setFPSFocus();}
        else if (event.type == sf::Event::Resized)
        {
            SCREEN_WIDTH = event.size.width; 
            SCREEN_HEIGHT = event.size.height;
            sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
            window.setView(view);
        }

        else if(event.type ==::sf::Event::MouseButtonPressed)
        {   
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                ui->check_buttons(1,event.mouseButton.x,event.mouseButton.y);
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                state = menu;
            }
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            ui->check_buttons(0,event.mouseMove.x,event.mouseMove.y);
        }
        else if (event.type == sf::Event::KeyPressed)
        {

        }
    }
}

void MenuStateSwitcher::State_Switcher()
{
    bool run = true;
    while(run)
    {
        switch (state)
        {
        case menu:          state = go_menu();break;
        case prof_choose:   state = go_profile_choose();break;
        case extras:        state = go_extras();break;
        case settings:      state = go_settings();break;
        case game:          state = go_in_world();break;
        case editor:        state = go_in_world();break;
        case quit:          run = false;break;
        }
    }
    
}

int MenuStateSwitcher::go_extras()
{
    state = menu;
    return state;
}

int MenuStateSwitcher::go_settings()
{
    state = menu;
    return state;
}

int MenuStateSwitcher::go_menu()
{
    //PRE_CYCLE
    ui->add_txt("menu");
    ui->add_butt(50,200,"go_profile",[&](){state = prof_choose;});
    ui->add_butt(50,250,"go_settings",[&](){state = settings;});
    ui->add_butt(50,300,"go_extras",[&](){state = extras;});
    ui->add_butt(50,350,"quit",[&](){state = quit;});

    //CYCLE
    while(state == menu)
    {
        event_check();
        if(time->time_to_draw())
        {
            window.clear(sf::Color{50,50,50,50});
            window.draw(ui->getSprite());
            
            window.display();
        }
        else
            time->delay();
    }
    ui->clear();
    return state;
}

int MenuStateSwitcher::go_profile_choose()
{
    //PRE_INIT_CYCLE
    ui->add_txt("profile");
    ui->add_butt(50,350,"start",[&](){state = game;});
    ui->add_butt(50,400,"editor",[&](){state = editor;});
    ui->add_butt(50,450,"go_menu",[&](){state = menu;});
    ui->add_butt(50,500,"quit",[&](){state = quit;});

    ui->add_butt(SCREEN_WIDTH-200,100,prof_Mng->getName(0),[&](){prof_Mng->setProfile(0);});
    ui->add_butt(SCREEN_WIDTH-200,200,prof_Mng->getName(1),[&](){prof_Mng->setProfile(1);});
    ui->add_butt(SCREEN_WIDTH-200,300,prof_Mng->getName(2),[&](){prof_Mng->setProfile(2);});
    ui->add_butt(SCREEN_WIDTH-200,400,prof_Mng->getName(3),[&](){prof_Mng->setProfile(3);});

    ui->add_dtxt(prof_Mng->getLinkCurProfile(),"cur prof: ");

    //CYCLE
     while(state == prof_choose)
    {
        event_check();
        if(time->time_to_draw())
        {
            window.clear(sf::Color::Black);
            window.draw(ui->getSprite());
            window.display();
        }
        else
            time->delay();
    }
    ui->clear();
    return state;
};

void MenuStateSwitcher::clear_menu()
{
    delete time;
    delete ui;
    delete prof_Mng;
}

void MenuStateSwitcher::rebuild_menu()
{
    time = new Time;
    ui = new UIBoss{0};
    prof_Mng = new ProfileManager;
}

int MenuStateSwitcher::go_in_world()
{
    Base_InWorld* game_obj;
    if(state == editor)
        game_obj = new Editor{prof_Mng->getCurProfile(),window};
    else
        game_obj = new Game{prof_Mng->getCurProfile(),window};

    clear_menu();

    game_obj->start();
    delete game_obj;
    state = menu;

    window.setView(window.getDefaultView());
    rebuild_menu();
    return state;
}