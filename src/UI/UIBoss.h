#pragma once

#include <vector>

#include "Button.h"
#include "DynamText.h"
#include "ValueSwitcher.h"
#include "GamConsole.h"

class UIBoss
{
private:
    std::vector<sf::Text> txts;

    int dtxts_count = 0;
    std::vector<DynamText<int>> dtxts_i;
    std::vector<DynamText<float>> dtxts_f;

    int panel_butts_count = 0;
    std::vector<Button> butts;
    
    int switchers_count = 0;
    std::vector<ValueSwitcher<int>> switchers_i;
    std::vector<ValueSwitcher<float>> switchers_f;
    
    sf::Font font;
    GamConsole console;
    
    sf::RectangleShape top;
    sf::RectangleShape left;
    sf::RectangleShape right;
    sf::RectangleShape bot;
    sf::RectangleShape gamefield;

    sf::RenderTexture texture;
    void build();

    template<typename T>
    void impl_dtxt( std::vector<DynamText<T>>& vec, T* link,std::string bef,std::string aft)
    {
        #define top_max_row 3
        int col = dtxts_count/top_max_row;
        int row = dtxts_count%top_max_row;
        dtxts_count++;

        #define dtxt_width 130
        #define d_txt_height 20
        #define top_top_margin 10
        #define top_left_margin 10

        vec.push_back(DynamText
            (
                font,
                link,
                col*dtxt_width+top_top_margin,
                row*d_txt_height+top_left_margin,
                bef,aft,
                0
            )
        );
    }

    template<typename T>
    void impl_switcher(std::vector<ValueSwitcher<T>>& vec,std::string name, T* link,T val)
    {
        #define swithcers_right_margin 100
        #define switchers_top_margin 150
        #define right_max_col 1
        int col = switchers_count%right_max_col;
        int row = switchers_count/right_max_col;

        switchers_count++;

        #define switcher_width 120
        #define switcher_height 50

        vec.push_back(ValueSwitcher
            (
                font,name,link,val,
                SCREEN_WIDTH-swithcers_right_margin + col*switcher_width,
                switchers_top_margin + row*switcher_height
            )
        );
    }

public:
    explicit UIBoss(bool drawField = false);

    void add_txt(std::string txt);

    inline void add_dtxt(int* link,std::string bef,std::string aft = ""){impl_dtxt(dtxts_i,link,bef,aft);}
    inline void add_dtxt(float* link,std::string bef,std::string aft = ""){impl_dtxt(dtxts_f,link,bef,aft);}

    void add_butt(int x, int y, std::string b_name, std::function<void()> b_action);
    void add_butt(float x, float y, std::string b_name, std::function<void()> b_action);
    void add_butt(std::string b_name, std::function<void()> b_action);

    void add_switcher(std::string name, int* link,int val){impl_switcher(switchers_i,name,link,val);}
    void add_switcher(std::string name, float* link,float val){impl_switcher(switchers_f,name,link,val);}
    
    void add_space_dtxt(){dtxts_count++;}
    void clear_console(){console.clear();};

    void out(std::string msg){console.out(std::move(msg));};

    bool check_buttons(int m,int mx, int my);
    sf::Sprite getSprite();

    void clear();
};

