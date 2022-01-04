#ifndef _SNAKE_MAP_
#define _SNAKE_MAP_

#include <random>
#include <utility>
class snake;
class snake_map{

    public:
        snake_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        virtual void print();
        void reset();
        int get_point(int,int);
        void map_change_point(int,int,int);
        virtual void random_food();
        virtual bool player_move_body();
        void player_erase_tail();
        void player_change_direction(int,int);
        void game_time();
        virtual void player_control();
        int get_width();
        int get_height();
        int kbhit();
        bool pause();
        void game_over(int);
        void show_length();
        void print_snake();
        snake* get_player(int);
        std::pair<int,int> middle;
        void down_counter();
     
        

    protected:
        int Map[100][100];
        int width;
        int height;
        int time_interval;
        snake *player1;
        snake *player2;
        
};

class connection_map:public snake_map{
    public:
        connection_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void player_control();
};

class unwall_map:public snake_map{
    public:
        unwall_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void print();

};

class connection_unwall_map:public unwall_map{
    public:
        connection_unwall_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void player_control();
};

class special_food_map:public snake_map{

    public:
        special_food_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void random_food();
        bool player_move_body();
        void player_control();
        void reverse_control();
        void check_food_type();

    private:
        int reverse_num=0;

};

class connection_special_map:public unwall_map{
    public:
        connection_special_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void player_control();
};

class barrier_map:public snake_map{
    public:
        barrier_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void random_food();
};

class connection_barrier_map:public unwall_map{
    public:
        connection_barrier_map(int player1,int player2,int food_num,int speed,std::pair<int,int> map_size);
        void player_control();
};

#endif