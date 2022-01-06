#include "snake.h"
#include "snake_map.h"
#include <cstring>

player_snake::player_snake(snake_map*ptr,int player,char *s):snake(ptr,player,s){}

void player_snake::change_direction(int n)
{
    if(n==-1)
    return;

    int move_xy[4][2]={{-1,0},
                        {0,1},
                        {1,0},
                        {0,-1}};
    
    pair<int,int> tmp=head->position;
    tmp.first+=move_xy[n][0];
    tmp.second+=move_xy[n][1];

    if(head->next->position!=tmp&&direction!=n)
    direction=n;
}


unwall_player_snake::unwall_player_snake(snake_map*ptr,int player,char * s):player_snake(ptr,player,s){};


bool unwall_player_snake::move_body()
{
            
    int move_xy[4][2]={{-1,0},
                        {0,1},
                        {1,0},
                        {0,-1}};
    
    if(eat_food_type==0)
    {   

        snake_body *current=tail;

        while(current->previous!=nullptr)
        {
            //printw("( %d,%d ) ",current->position.first,current->position.second);
            //refresh();
            //sleep(1);
            current->position=current->previous->position;
            current=current->previous;
        }


        

        head->position.first+=move_xy[direction][0];
        head->position.second+=move_xy[direction][1];

    }
    else
    eat_point();

    
    int head_point=map_ptr->get_point(head->position.first,head->position.second);

    if(head_point==1)
    {
        int width=map_ptr->get_width(),height=map_ptr->get_height();
        if(head->position.first==1)
        head->position.first=height-1;
        else if(head->position.first==height)
        head->position.first=2;
        else if(head->position.second==1)
        head->position.second=width-1;
        else if(head->position.second==width)
        head->position.second=2;

        head_point=map_ptr->get_point(head->position.first,head->position.second);
    }
    
    if(head_point!=0&&head_point<5)
    return 0;

    if(head_point>=5)
    eat_food_type=head_point;

    map_ptr->map_change_point(head->position.first,head->position.second,2);
    

    
    if((head->position.first+head->position.second)%2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"%s",body_element);
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"%s",body_element);
        attroff(COLOR_PAIR(2));
    }

    return 1;

}


special_player_snake::special_player_snake(snake_map*ptr,int player,char * s):player_snake(ptr,player,s){};


void special_player_snake::eat_point()
{

    int move_xy[4][2]={{-1,0},
                        {0,1},
                        {1,0},
                        {0,-1}};


    if(eat_food_type!=30)
    map_ptr->random_food();     
    length++;
    

    switch (eat_food_type-6)
    {
        case 1:
            invincible+=20;
            eat_food_type=0;
            
            if(body_element!="⭐")
            tmp_element=body_element;

            change_body_element("⭐");
            map_ptr->print_snake();

            break;
        case 2:
            eat_food_type=30;
            break;
        case 4:
            eat_food_type=0;
            random_new_pos();
            break;
        case 5:
            transparent+=10;

            eat_food_type=0;
            break;
        default:
            eat_food_type=0;
    }

    
    
    snake_body *tmp=head;
    head=new snake_body(head->position.first+move_xy[direction][0],head->position.second+move_xy[direction][1]);
    head->next=tmp;
    tmp->previous=head;
    
    return;



}


void special_player_snake::random_new_pos()
{

    int height=map_ptr->get_height();
    int width=map_ptr->get_width();
    // 4~height-4
    int x=random()%((height-9))+5;
    // 4~width-4
    int y=(random()%(width-9))+5;


    bool can_move=0;
    while(!can_move)
    {
        can_move=1;
        x=(random()%(height-6))+4;
        y=(random()%(width-6))+4;

        for(int i=x-3;i<=x+3;i++)
        {
            for(int j=y-3;j<=y+3;j++)
            {
                if(map_ptr->get_point(i,j)!=0)//&&map_ptr->get_point(i,j)<5);
                can_move=0;
                //mvprintw(i,50+2*j,"XX");
                
            }
        }
        
        refresh();

        //break;
        
    }
    
    if((head->position.first+head->position.second)%2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"  ");
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"  ");
        attroff(COLOR_PAIR(2));
    }
    map_ptr->map_change_point(head->position.first,head->position.second,0);
    head->position=make_pair(x,y);
    //mvprintw(head->position.first,50+2*head->position.second,"🌀");


}


bool special_player_snake::move_body()
{
            
    int move_xy[4][2]={{-1,0},
                        {0,1},
                        {1,0},
                        {0,-1}};
    
    
    if(transparent!=0)
    transparent--;

    if(eat_food_type==0)
    {    

        snake_body *current=tail;

        while(current->previous!=nullptr)
        {
            current->position=current->previous->position;
            current=current->previous;
        }

        head->position.first+=move_xy[direction][0];
        head->position.second+=move_xy[direction][1];

    }
    else
    eat_point();

    
    int head_point=map_ptr->get_point(head->position.first,head->position.second);

    if(invincible==0&&head_point!=0&&head_point<5)
    return 0;

    if(head_point>=5)
    eat_food_type=head_point;


    if(head_point==1)
    {
        int width=map_ptr->get_width(),height=map_ptr->get_height();
        if(head->position.first==1)
        head->position.first=height-1;
        else if(head->position.first==height)
        head->position.first=2;
        else if(head->position.second==1)
        head->position.second=width-1;
        else if(head->position.second==width)
        head->position.second=2;

        head_point=map_ptr->get_point(head->position.first,head->position.second);
    }



    map_ptr->map_change_point(head->position.first,head->position.second,2);

    if((head->position.first+head->position.second)%2)
    {
        attron(COLOR_PAIR(1));
        if(transparent==0)
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"%s",body_element);
        else
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"  ");
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        if(transparent==0)
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"%s",body_element);
        else
        mvprintw(map_ptr->middle.first+head->position.first,map_ptr->middle.second+60+2*head->position.second,"  ");
        attroff(COLOR_PAIR(2));
    }
    
    if(invincible!=0)
    {
        invincible--;
        if(invincible==0)
        body_element=tmp_element,map_ptr->print_snake();
        
    }


    return 1;

}

