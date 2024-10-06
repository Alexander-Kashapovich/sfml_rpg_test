#include "Okno.h"
#include "MenuStateSwitcher.h"

#include <iostream>

int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width-100;
int SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height-100;

int main()
{  
    std::srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "test", sf::Style::Default);

    std::cout << "OpenGL version: " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << std::endl;
    
    //герцовка не позволяет выше 60фпс.причем цифры отладки начинают сходить с ума
    //хотя фактически в нём те же 60фпс и 500мкс на отрисовку
    #if 0
    window.setVerticalSyncEnabled(true);
    #endif

    MenuStateSwitcher* Main_Menu = new MenuStateSwitcher{window};
    Main_Menu->State_Switcher();
    return 0;
}