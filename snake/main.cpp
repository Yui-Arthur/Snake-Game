#include <iostream>
//#include <windows.h>
#include <cstring>
//#include <conio.h>
#include <ncurses.h>
#include <utility>
#include <ctime>
#include <unistd.h>
#include "snake_map.h"
#include "snake.h"
#include <vector>
#include "game_menu.h"

using namespace std;

int main()
{   
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr,TRUE);
    

    game_menu game;
    game.initial_menu();
    /*
    double x=3.92;
    start_color();
    init_color(COLOR_CYAN, 245*x, 245*x, 220*x);
    init_color(COLOR_BLUE, 125*x, 105*x, 255*x);
    init_pair(1,COLOR_CYAN,COLOR_BLUE);
    init_pair(2,COLOR_MAGENTA,COLOR_MAGENTA);
    //snake_map *game_map=new snake_map(1,1,100000,make_pair(50,50),1);
    //snake_map *game_map=new unwall_map(1,1,100000,make_pair(20,20),1);
    //snake_map *game_map=new barrier_map(1,1,100000,make_pair(50,50),1);
    snake_map *game_map= new special_food_map(1,1,80000,make_pair(50,50),1);
    
    //100000
    refresh();
     
    game_map->game_time();
   
    move(0,0);
    */
    endwin();
    
    return 0;
}





