#include "Base_InWorld.h"

#include <stdio.h>

void Base_InWorld::start()
{
    cam = window.getView();

    //usage metrs
    Memometr mem;
    Processmetr cpu;
    ui.add_dtxt(mem.get_link_memor(),"mem:","kb");
    ui.add_dtxt(cpu.get_cpu_link(),"CPU: ","%");
    ui.add_space_dtxt();
    //perf metrs
    ui.add_dtxt(&timeDrawAverageCent,"average: ","mcs");
    ui.add_dtxt(&timeToDraw,"now: ","mcs");
    ui.add_space_dtxt();

    //cords
    ui.add_dtxt(cam.getLinkX(),"x: ");    
    ui.add_dtxt(cam.getLinkY(),"y: ");    
    sf::Clock draw_clock;
    int count = 1;

    preCycle();
    //can make only after lvl build
    ren.init();

    //finally go
    bool run = true;
    while(run)
    {
        run = event_check();
        if(time.time_to_draw())
        {
            smth_in_cycle();
            updCamera();

            draw_clock.restart();
            ren.draw();
            timeToDraw = draw_clock.getElapsedTime().asMicroseconds();

            count++;
            //это аддикция к среднему
            timeDrawAverageCent = (timeDrawAverageCent*(count-1) + timeToDraw)/count;
            if(count == 100)
                count = 1;
        }
        else if(time.time_to_rare_update())
        {
            mem.update();
            cpu.update();
        }
        else time.delay();
    }
}

bool Base_InWorld::event_check()
{
    sf::Event event;
    bool run = true;
    while(window.pollEvent(event)) 
    {
        switch (event.type)
        {
            case sf::Event::Closed:         std::exit(0);break;
            case sf::Event::LostFocus:      time.setFPSUnfocus();break;
            case sf::Event::GainedFocus:    time.setFPSFocus();break;
            case sf::Event::Resized:
                SCREEN_WIDTH = event.size.width;
                SCREEN_HEIGHT = event.size.height;
                cam.setSize(SCREEN_WIDTH,SCREEN_HEIGHT);
                window.setView(cam);break;
            
            case sf::Event::MouseButtonPressed: run = mouse_event(event);break;
            case sf::Event::KeyPressed:         run = key_event(event);break;
            case sf::Event::MouseMoved:         select_event(event);break;
        }
    }

    return run;
}

void Base_InWorld::updCamera()
{
    if(freeCam)
    {
        sf::Vector2f movement(0.f, 0.f);

        constexpr int speed = 15;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            movement.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            movement.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            movement.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            movement.x += speed;

        cam.move(movement);
    }
    
    window.setView(cam);
}