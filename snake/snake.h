
#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <utility>
#include <ncurses.h>
#include "snake_map.h"

using namespace std;


class snake_map;

class snake_body{

    public:
    snake_body(int ,int );
    snake_body(int ,int ,snake_body*);
    void new_body(int x,int y);
    void snake_eat_point();
    snake_body *next;
    snake_body *previous;
    pair<int,int> position;


};

class snake{
    

    public:
        snake(snake_map *ptr,int player,char *);
        virtual void eat_point();
        virtual bool move_body();
        void erase_tail();
        virtual void change_direction(int n)=0;
        int get_length();
        pair<int,int>get_head_pos();
        snake_body* get_head();
        int get_eat_food();
        char * get_body_element();
        void change_body_element(char*);
        

    protected:

        snake_body *head;
        snake_body *tail;
        int length;
        int eat_food_type=0;
        int direction;
        snake_map *map_ptr;
        char * body_element;
        
    
};

class player_snake:public snake{
    
    public:
        player_snake(snake_map*,int,char *);
        void change_direction(int n);
};


class unwall_player_snake:public player_snake{
    
    public:
        unwall_player_snake(snake_map*,int,char *);
        bool move_body();
};

class special_player_snake:public player_snake{
    
    public:  
        special_player_snake(snake_map*,int,char *);
        void eat_point();
        void random_new_pos();
        bool move_body();

    private:
        int invincible=0;
        int transparent=0;
        char * tmp_element;
        
};

class computer_snake:public snake{

    public:
        computer_snake(snake_map*,int,char *);
        virtual void change_direction(int n);
        virtual int direction_score(pair<int,int>,int);
        virtual void dfs(pair<int,int>);
        int accept_point;
        int check[55][55];
};

class unwall_computer_snake:public computer_snake{
    
    public:
        unwall_computer_snake(snake_map*,int,char *);
        void change_direction(int n);
        bool move_body();
        int direction_score(pair<int,int>,int);
        void dfs(pair<int,int>);

};

class special_computer_snake:public computer_snake{

    public:  
        special_computer_snake(snake_map*,int,char *);
        void eat_point();
        void random_new_pos();
        bool move_body();

    private:
        int invincible=0;
        int transparent=0;
        char * tmp_element;

};


#endif