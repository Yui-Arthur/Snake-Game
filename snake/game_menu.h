#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "snake_map.h"


class snake_map;
class game_menu{

    public:
    game_menu(){};
    void initial_menu();
    void print_initail_menu();
    void game_setting();
    void print_game_setting_menu();
    void game_change_setting(int,int);
    void into_game(int,int,int,int,int,int);

    private:
    snake_map *ptr;

};




#endif 