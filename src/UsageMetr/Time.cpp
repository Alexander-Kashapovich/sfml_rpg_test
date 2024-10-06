#include "Time.h"

#include <iostream>

bool Time::time_to_draw()
{
    if(ms_frame < fps_clock.getElapsedTime())
    {
        fps_clock.restart();
        return true;
    }
    else return false;
}

bool Time::time_to_rare_update()
{
    if(ms_slow_frame < slow_clock.getElapsedTime())
    {
        slow_clock.restart();
        return true;
    }
    else return false;

}

void Time::delay()
{
    sf::sleep(ms_frame - fps_clock.getElapsedTime());
}

void Time::set_FPS(int new_FPS)
{
    FPS = new_FPS;
    ms_frame = sf::milliseconds(1000/FPS);
}

void Time::setFPSUnfocus()
{
    cache_fps = FPS;
    set_FPS(5);
}

void Time::setFPSFocus()
{
    set_FPS(cache_fps);
}