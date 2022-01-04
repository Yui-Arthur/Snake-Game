#include "snake.h"
#include "snake_map.h"
#include <cstring>

snake_body::snake_body(int x,int y)
{
    position=make_pair(x,y);
    next=nullptr;
    previous=nullptr;
}

snake_body::snake_body(int x,int y,snake_body *ptr)
{
    position=make_pair(x,y);
    next=nullptr;
    previous=ptr;
};

void snake_body::new_body(int x,int y)
{
    next=new snake_body(x,y,this);
};


snake::snake(snake_map*ptr,int player,char * s)
{
    int x,y;
    map_ptr=ptr;
    if(player==1)
    x=map_ptr->get_height()/2,y=map_ptr->get_width()/2;
    else if(player==2)
    x=map_ptr->get_height()/4,y=map_ptr->get_width()/4;
    else
    x=map_ptr->get_height()/4*3,y=map_ptr->get_width()/4*3;

    if((x+y)%2==1)
    y++;

    length=3;
    body_element=s;
    head=new snake_body(x,y);
    tail=head;
    tail->new_body(x,y-1);
    tail=tail->next;
    tail->new_body(x,y-2);
    tail=tail->next;
    tail->new_body(x,y-3);
    tail=tail->next;
    
    // 0 up 
    // 1 right 
    // 2 down 
    // 3 left
    if(player==1)
    direction=0;
    else
    direction=2;

    map_ptr->map_change_point(x,y,2);
    map_ptr->map_change_point(x,y-1,2);
    map_ptr->map_change_point(x,y-2,2);
    map_ptr->map_change_point(x,y-3,2);

    //25-height/2+i,60+(50-width)+2*j
    
    attron(COLOR_PAIR(2));
    mvprintw(map_ptr->middle.first+x,map_ptr->middle.second+60+(y)*2,"%s",body_element);
    mvprintw(map_ptr->middle.first+x,map_ptr->middle.second+60+(y-2)*2,"%s",body_element);
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(map_ptr->middle.first+x,map_ptr->middle.second+60+(y-1)*2,"%s",body_element);
    mvprintw(map_ptr->middle.first+x,map_ptr->middle.second+60+(y-3)*2,"%s",body_element);
    attroff(COLOR_PAIR(1));


    move(0,0);
    

}



bool snake::move_body()
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
            current->position=current->previous->position;
            current=current->previous;
        }

        head->position.first+=move_xy[direction][0];
        head->position.second+=move_xy[direction][1];

    }
    else
    eat_point();

    
    int head_point=map_ptr->get_point(head->position.first,head->position.second);

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

void snake::erase_tail()
{
    if((tail->position.first+tail->position.second)%2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(map_ptr->middle.first+tail->position.first,map_ptr->middle.second+60+2*tail->position.second,"  ");
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        mvprintw(map_ptr->middle.first+tail->position.first,map_ptr->middle.second+60+2*tail->position.second,"  ");
        attroff(COLOR_PAIR(2));
    }
    map_ptr->map_change_point(tail->position.first,tail->position.second,0);
}

void snake::eat_point()
{
    int move_xy[4][2]={{-1,0},
                        {0,1},
                        {1,0},
                        {0,-1}};

    eat_food_type=0;
    length++;
    map_ptr->random_food();
    
    snake_body *tmp=head;
    head=new snake_body(head->position.first+move_xy[direction][0],head->position.second+move_xy[direction][1]);
    head->next=tmp;
    tmp->previous=head;
    
    return;
}

int snake::get_length()
{
    return length; 
}

pair<int,int>snake::get_head_pos()
{
    return head->position;
}

int snake::get_eat_food()
{
    return eat_food_type;
}

snake_body* snake::get_head()
{
    return head;
}

char * snake::get_body_element()
{
    return body_element;
}

void snake::change_body_element(char *c)
{
    body_element=c;
}