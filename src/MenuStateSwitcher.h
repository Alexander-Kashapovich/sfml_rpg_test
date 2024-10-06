#pragma once

#include "UsageMetr/Time.h"
#include "UsageMetr/Memometr.h"
#include "UsageMetr/Processmetr.h"

#include "UI/UIBoss.h"

#include "ProfileManager/ProfileManager.h"

enum game_state
{
    quit,
    menu,
    settings,
    extras,
    prof_choose,
    game,
    editor
};

class MenuStateSwitcher
{
private:
    int state;

    Time* time = new Time;
    ProfileManager* prof_Mng = new ProfileManager;
    UIBoss* ui = new UIBoss;

    sf::RenderWindow& window;
    int go_in_world();
    int go_menu();
    int go_extras();
    int go_settings();
    int go_profile_choose();

    void event_check();

    void clear_menu();
    void rebuild_menu();

public:
    MenuStateSwitcher(sf::RenderWindow& win):state(game), window(win){}
    ~MenuStateSwitcher(){clear_menu();}

    void State_Switcher();
};