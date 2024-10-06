#pragma once

#include <SFML/System.hpp>

class Time
{
private:
    sf::Clock fps_clock;
    sf::Clock slow_clock;   
    int FPS;
    int cache_fps = 30;               
    sf::Time ms_frame;   //ms for frame    
    const sf::Time ms_slow_frame = sf::milliseconds(1000); //ms for slow frame (1fps)

public:
    Time(int  fps = 59, sf::Time slow_tick = sf::milliseconds(1000)): 
        FPS(fps), 
        ms_frame(sf::milliseconds(1000 / FPS))
        {}

    void set_FPS(int new_FPS);

    inline int get_FPS() const{return FPS;}
    void setFPSUnfocus();
    void setFPSFocus();

    bool time_to_draw();
    bool time_to_rare_update();
    void delay();

};


