#ifndef _SNAKE_MAP_
#define _SNAKE_MAP_

#include <random>
#include <utility>
class snake;
class snake_map{

    public:
        snake_map(int player_1,char * player1_skin,int player_2,char* player_2_skin,int food_num,int speed,std::pair<int,int> map_size);
        virtual void print();
        void reset();
        int get_point(int,int);
        void map_change_point(int,int,int);
        virtual void random_food();
        virtual bool player_move_body();
        void player_erase_tail();
        void player_change_direction(int,int);
        virtual void game_time();
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
        //void input_binary_data(int digit,int data,std::ofstream &file);
        //int binary_to_decimal(std::vector<unsigned char> data);
        //void save_data();
        virtual void save_snake_head_data();
        virtual bool load_game(int);
        void load_player_move(std::pair<int,int>,int);
     
        

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
        connection_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my);
        void game_time();
        void player_control();
        void recv_player_control();

    private:
        int sock;
        int my_snake;
        int connector_snake;
};

class unwall_map:public snake_map{
    public:
        unwall_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size);
        void print();
        //bool load_game(int);

};

class connection_unwall_map:public unwall_map{
    public:
        connection_unwall_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my);
        void game_time();
        void player_control();
        void recv_player_control();

    private:
        int sock;
        int my_snake;
        int connector_snake;
};

class special_food_map:public snake_map{

    public:
        special_food_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size);
        void random_food();
        bool player_move_body();
        void player_control();
        void reverse_control();
        void check_food_type();
        void save_snake_head_data();
        bool load_game(int);

    private:
        int reverse_num=0;

};

class connection_special_map:public special_food_map{
    public:
        connection_special_map(int player_1,char * player1_skin,int player_2,char* player_2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my);
        void game_time();
        void player_control();
        void recv_player_control();

    private:
        int sock;
        int my_snake;
        int connector_snake;
};

class barrier_map:public snake_map{
    public:
        barrier_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size);
        void random_food();
        void save_snake_head_data();
        bool load_game(int);

    private:
        std::pair<int,int> barrier;
};

class connection_barrier_map:public barrier_map{
    public:
        connection_barrier_map(int player_1,char * player1_skin,int player2,char* player_2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my);
        void game_time();
        void player_control();
        void recv_player_control();

    private:
        int sock;
        int my_snake;
        int connector_snake;
};



class level_snake_map:public snake_map{
    public:
        level_snake_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size, int *requirment,int l);
        bool player_move_body() override;
        void print_level_requirment() ;
    private:
        int *re;
        int footprint=0;
        int level;
};
class level_unwall_map:public unwall_map{
    public:
        level_unwall_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size, int *requirment,int l);
        bool player_move_body() override;
        void print_level_requirment() ;
    private:
        int *re;
        int footprint=0;
        int level;
};

class level_barrier_map:public barrier_map{
    public:
        level_barrier_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size, int *requirment,int l);
        bool player_move_body() override;
        void print_level_requirment() ;
    private:
        int *re;
        int footprint=0;
        int level;
};

class level_special_food_map:public special_food_map{
    public:
        level_special_food_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size, int *requirment,int l);
        bool player_move_body() override;
        void print_level_requirment();
    private:
        int *re;
        int footprint=0;
        int level;
};

#endif