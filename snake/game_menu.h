#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "snake_map.h"
#include <fstream>


class snake_map;
class game_menu{

    public:
        game_menu(){initial_menu();};
        void initial_menu();
        void print_initail_menu();
        void game_setting();
        void print_game_setting_menu();
        void game_change_setting(int,int);
        void into_game(int,int,int,int,int,int,int,int,int);
        void github();
        char* get_local_ipAddr();
        void server_connection();
        void client_connection();
        void connect_play();
        int socket_connect(std::vector<char>);
        //void input_binary_data(int ,int,std::ofstream&);
        //int binary_to_decimal(std::vector<unsigned char>);
        void load_game_setting();
        bool play_again(snake_map*);
        void switch_picture(int choice);

        int thread_func(int &sock);
        void game_server_setting(int);
        void game_client_setting(int);
        void online_into_game(int,int,int,int,int,int,int,int,int,int);
        void level_into_game(int,int,int,int);
        void into_next_level();
    

};




#endif 
