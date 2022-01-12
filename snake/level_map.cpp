#include "snake_map.h"
#include "snake.h"
#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <fstream>


level_snake_map::level_snake_map(int player_1, char *player1_skin, int player_2, char *player2_skin, int food_num, int speed, std::pair<int, int> map_size, int *requirment,int l) : snake_map(player_1, player1_skin, player_2, player2_skin, food_num, speed, map_size)
{
    re = requirment;
    level=l;
    print_level_requirment();
}

bool level_snake_map::player_move_body()
{
    footprint++;
    print_level_requirment();
    player_erase_tail();

    if (player2 == nullptr)
    {

        bool result = player1->move_body();
        show_length();
        if (result == 0 || (footprint > re[2] && re[2] != 0))
        {
            player1->change_body_element("💀");
            //player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result=0;
        }
        if (re[1] != 0){
            
            if(player1->get_length()-3==re[1]-1 &&player1->get_eat_food()!=0)
            result = 0,width=-1;
        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            result = 0;
            width=-1;

        } 
        
        
        return result;
    }
    else
    {
        bool result1 = player1->move_body(), result2 = player2->move_body();
        show_length();
        if (result1 == 0 || result2 == 0 || (footprint > re[2]&&re[2]!=0))
        {
            player1->change_body_element("💀");
            player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result1=0;
        }

        if(re[1] != 0)
        {

            if ((player1->get_length() + player2->get_length() - 6 == re[1] - 1) && (player1->get_eat_food() != 0 || player2->get_eat_food() != 0))
            {
                result1 = 0;
                width=-1;
            }

        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            
            result1 = 0;
            width=-1;
            
        } 

        
        return result1 && result2;
    }
}

void level_snake_map::print_level_requirment()
{
    if (re[0] == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30,     "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30,     "│ - Normal                   │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30,     "│ Collect %2d fruit in total! │", re[1]);
        if (re[2] != 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d step!         │", re[2] - footprint);
        if (re[2] == 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│                            │");
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30,     "└────────────────────────────┘");
    }
    else 
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30, "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30, "│ - Normal                   │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30, "│ Survive until %3d second!  │", re[0]);
        mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d second!       │", re[0]-(int)(footprint *0.09) );
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30, "└────────────────────────────┘");
    }
}

level_unwall_map::level_unwall_map(int player_1, char *player1_skin, int player_2, char *player2_skin, int food_num, int speed, std::pair<int, int> map_size, int *requirment,int l) : unwall_map(player_1, player1_skin, player_2, player2_skin, food_num, speed, map_size)
{
    level=l;
    re = requirment;
    print_level_requirment();
}

bool level_unwall_map::player_move_body()
{
    footprint++;
    print_level_requirment();
    player_erase_tail();

    if (player2 == nullptr)
    {

        bool result = player1->move_body();
        show_length();
        if (result == 0 || (footprint > re[2] && re[2] != 0))
        {
            player1->change_body_element("💀");
            //player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result=0;
        }
        if (re[1] != 0){
            
            if(player1->get_length()-3==re[1]-1 &&player1->get_eat_food()!=0)
            result = 0,width=-1;
        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            result = 0;
            width=-1;

        } 
        
        
        return result;
    }
    else
    {
        bool result1 = player1->move_body(), result2 = player2->move_body();
        show_length();
        if (result1 == 0 || result2 == 0 || (footprint > re[2]&&re[2]!=0))
        {
            player1->change_body_element("💀");
            player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result1=0;
        }

        if(re[1] != 0)
        {

            if ((player1->get_length() + player2->get_length() - 6 == re[1] - 1) && (player1->get_eat_food() != 0 || player2->get_eat_food() != 0))
            {
                result1 = 0;
                width=-1;
            }

        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            
            result1 = 0;
            width=-1;
            
        } 

        
        return result1 && result2;
    }
}



void level_unwall_map::print_level_requirment()
{
    if (re[0] == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30,     "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30,     "│ - Unwall                   │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30,     "│ Collect %2d fruit in total! │", re[1]);
        if (re[2] != 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d step!         │", re[2] - footprint);
        if (re[2] == 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│                            │");
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30,     "└────────────────────────────┘");
    }
    else 
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30, "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30, "│ - Unwall                   │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30, "│ Survive until %3d second!  │", re[0]);
        mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d second!       │", re[0] - (int)(footprint *0.09) );
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30, "└────────────────────────────┘");
    }
}

level_barrier_map::level_barrier_map(int player_1, char *player1_skin, int player_2, char *player2_skin, int food_num, int speed, std::pair<int, int> map_size, int *requirment,int l) : barrier_map(player_1, player1_skin, player_2, player2_skin, food_num, speed, map_size)
{
    level=l;
    re = requirment;
    if(player_1==0)
    player1=new special_player_snake(this,1,player1_skin);
    else
    player1=new special_computer_snake(this,1,player1_skin);


    if(player_2==0)
    player2=nullptr;
    else if(player_2==1)
    player2=new special_player_snake(this,2,player2_skin);
    else
    player2=new special_computer_snake(this,2,player2_skin);

    print_level_requirment();
}

bool level_barrier_map::player_move_body()
{
    footprint++;
    print_level_requirment();
    player_erase_tail();

    if (player2 == nullptr)
    {

        bool result = player1->move_body();
        show_length();
        if (result == 0 || (footprint > re[2] && re[2] != 0))
        {
            player1->change_body_element("💀");
            //player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result=0;
        }
        if (re[1] != 0){
            
            if(player1->get_length()-3==re[1]-1 &&player1->get_eat_food()!=0)
            result = 0,width=-1;
        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            result = 0;
            width=-1;

        } 
        
        
        return result;
    }
    else
    {
        bool result1 = player1->move_body(), result2 = player2->move_body();
        show_length();
        if (result1 == 0 || result2 == 0 || (footprint > re[2]&&re[2]!=0))
        {
            player1->change_body_element("💀");
            player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result1=0;
        }

        if(re[1] != 0)
        {

            if ((player1->get_length() + player2->get_length() - 6 == re[1] - 1) && (player1->get_eat_food() != 0 || player2->get_eat_food() != 0))
            {
                result1 = 0;
                width=-1;
            }

        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            
            result1 = 0;
            width=-1;
            
        } 

        
        return result1 && result2;
    }
}


void level_barrier_map::print_level_requirment()
{
    //sleep(1);
    if (re[0] == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30,     "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30,     "│ - Barrier                  │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30,     "│ Collect %2d fruit in total! │", re[1]);
        if (re[2] != 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d step!         │", re[2] - footprint);
        if (re[2] == 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│                            │");
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30,     "└────────────────────────────┘");
    }
    else 
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30, "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30, "│ - Barrier                  │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30, "│ Survive until %3d second!  │", re[0]);
        mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d second!       │", re[0]-(int)(footprint*0.09) );
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30, "└────────────────────────────┘");
    }
}


level_special_food_map::level_special_food_map(int player_1, char *player1_skin, int player_2, char *player2_skin, int food_num, int speed, std::pair<int, int> map_size, int *requirment,int l) : special_food_map(player_1, player1_skin, player_2, player2_skin, food_num, speed, map_size)
{
    level=l;
    re = requirment;
    print_level_requirment();
}


bool level_special_food_map::player_move_body()
{
    footprint++;
    print_level_requirment();
    player_erase_tail();

    if (player2 == nullptr)
    {

        bool result = player1->move_body();
        show_length();
        if (result == 0 || (footprint > re[2] && re[2] != 0))
        {
            player1->change_body_element("💀");
            //player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result=0;
        }
        if (re[1] != 0){
            
            if(player1->get_length()-3==re[1]-1 &&player1->get_eat_food()!=0)
            result = 0,width=-1;
        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            result = 0;
            width=-1;

        } 
        
        
        return result;
    }
    else
    {
        bool result1 = player1->move_body(), result2 = player2->move_body();
        show_length();
        if (result1 == 0 || result2 == 0 || (footprint > re[2]&&re[2]!=0))
        {
            player1->change_body_element("💀");
            player2->change_body_element("💀");
            print_snake();
            attron(COLOR_PAIR(4));
            mvprintw(middle.first + height / 2 - 1, middle.second + 60 + width - 3, "┌────────────┐");
            mvprintw(middle.first + height / 2, middle.second + 60 + width - 3,     "│ You lose ! │");
            mvprintw(middle.first + height / 2 + 1, middle.second + 60 + width - 3, "└────────────┘");
            result1=0;
        }

        if(re[1] != 0)
        {

            if ((player1->get_length() + player2->get_length() - 6 == re[1] - 1) && (player1->get_eat_food() != 0 || player2->get_eat_food() != 0))
            {
                result1 = 0;
                width=-1;
            }

        }
        else if (re[0] != 0&&footprint*0.09>re[0])
        {
            
            result1 = 0;
            width=-1;
            
        } 

        
        return result1 && result2;
    }
}


void level_special_food_map::print_level_requirment()
{
    if (re[0] == 0)
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30,     "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30,     "│ - Special                  │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30,     "│ Collect %2d fruit in total! │", re[1]);
        if (re[2] != 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d step!         │", re[2] - footprint);
        if (re[2] == 0)
            mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│                            │");
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30,     "└────────────────────────────┘");
    }
    else
    {
        attron(COLOR_PAIR(3));
        mvprintw(middle.first + height / 2 - 7, 60 + middle.second - 30, "┌────────────────────────────┐");
        mvprintw(middle.first + height / 2 - 6, 60 + middle.second - 30, "│ LEVEL %2d                   │", level);
        mvprintw(middle.first + height / 2 - 5, 60 + middle.second - 30, "│ - Special                  │");
        mvprintw(middle.first + height / 2 - 4, 60 + middle.second - 30, "│ Survive until %3d second!  │", re[0]);
        mvprintw(middle.first + height / 2 - 3, 60 + middle.second - 30, "│ You left %3d second!       │", re[0] - (int)(footprint *0.09) );
        mvprintw(middle.first + height / 2 - 2, 60 + middle.second - 30, "└────────────────────────────┘");
    }
}