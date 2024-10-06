#pragma once

#include "GameCore/Masters/Renderer.h"

#include "LevelManager/LevelManager.h"
#include "ProfileManager/Profile.h"
#include "UI/UIBoss.h"

#include "UsageMetr/Memometr.h"
#include "UsageMetr/Processmetr.h"
#include "UsageMetr/Time.h"

#include "Okno.h"

class Base_InWorld
{
protected:
    UIBoss ui{1};

    Profile profile;
    Level lvl;

    LevelManager lvlMng;
    Time time;

    sf::View cam;
    sf::RenderWindow& window;
    Renderer ren;

    bool freeCam = 1;
    void updCamera();

    int timeToDraw{0};
    int timeDrawAverageCent{0};

    bool event_check();

    virtual bool key_event(sf::Event& event) = 0;
    virtual bool mouse_event(sf::Event& event) = 0;
    virtual void select_event(sf::Event& event) = 0;
    virtual void preCycle() = 0;
    virtual void smth_in_cycle() = 0;
public:
    Base_InWorld(Profile profile,sf::RenderWindow& win) :
        profile(profile),
        lvlMng(ui),
        window(win),
        ren(lvl,ui,win,cam)
        {};
    virtual ~Base_InWorld(){}
    void start();
};

