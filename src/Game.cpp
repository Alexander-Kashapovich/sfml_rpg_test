#include "Game.h"

#include "Okno.h"

Game::Game(Profile prof,sf::RenderWindow& window): 
    Base_InWorld(prof,window),
    pl(new Player{1,1,cam})
{
    lvlMng.goLevel(lvl,profile.curLevelID);

    lvl.addUnit(pl);
}

void Game::select_event(sf::Event& event)
{
    ui.check_buttons(0,event.mouseMove.x,event.mouseMove.y);
}

bool Game::mouse_event(sf::Event& event)
{
    ui.check_buttons(1,event.mouseButton.x,event.mouseButton.y);
    return true;
}

bool Game::key_event(sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Escape: return false;
        case sf::Keyboard::R: ren.drawUi = !ren.drawUi;break;
    }
    return true;
}

void Game::preCycle()
{
    ui.add_txt("ECS to exit");
    ui.add_txt("cam WASD");
    ui.add_txt("R toogle UI");

    ui.add_butt("pops",[this](){ui.out("pops");});
    ui.add_butt("cls",[this](){ui.clear_console();});
    ui.add_butt("toggle cell",[this](){ren.drawCellCorner = !ren.drawCellCorner;});
    ui.add_butt("toggle coll",[this](){ren.drawCollisGrid = !ren.drawCollisGrid;});
    ui.add_butt("toggle frame",[this](){ren.drawFrameRect = !ren.drawFrameRect;});

    ui.add_butt("save",[this](){lvlMng.save(lvl);});

    ui.add_switcher("night",&ren.uniforms.night,0.1);

    ui.out("pognali");

    cam.setCenter(pl->getCenter());

}

void Game::smth_in_cycle()
{
    pl->inputUpdate();
}
