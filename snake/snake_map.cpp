#include "snake_map.h"
#include "snake.h"
#include <ncurses.h>
#include <cstring>
#include <ctime>


snake_map::snake_map(int player_1,int player_2,int food_num,int speed,std::pair<int,int> map_size){
    height=map_size.first;
    width=map_size.second;
    time_interval=speed;

    middle.first=25-height/2;
    middle.second=(50-width);
    reset();
    print();
    
    
    if(player_1==0)
    player1=new player_snake(this,1,"💠");
    else
    player1=new computer_snake(this,1,"💠");


    if(player_2==0)
    player2=nullptr;
    else if(player_2==1)
    player2=new player_snake(this,2,"💓");
    else
    player2=new computer_snake(this,2,"💓");


    //player1=new special_player_snake(this,1,"💠");
    //player2=new special_computer_snake(this,2,"💓");
    //💠💓💢🌟🔲🔳▒▒ ░░ ▓▓ 
    //player2=new player_snake(this,2,"💓");
    //player1=new unwall_player_snake(this,1,"💠");
    //player2=new unwall_player_snake(this,2,"💓");

    

    //player2=nullptr;
    show_length();

    for(int i=0;i<food_num;i++)
    random_food();
}

void snake_map::reset()
{
    memset(Map,0,sizeof(Map));
    for(int i=1;i<=width;i++)
    {
        Map[1][i]=1;
        Map[height][i]=1;
    }

    for(int i=1;i<=height;i++)
    {
        Map[i][1]=1;
        Map[i][width]=1;
    }

    for(int i=0;i<200;i++)
    {
        for(int j=0;j<250;j++)
        mvprintw(i,j," ");
    }

}

void snake_map::print()
{
    
    for(int i=1;i<=height;i++)
    {
        for(int j=1;j<=width;j++)
        {
            //move(35+2*j,i);
            if(Map[i][j]==1)
            {
                attron(COLOR_PAIR(4));
                mvprintw(middle.first+i,middle.second+60+2*j,"▓▓");   
                attroff(COLOR_PAIR(4));
            }
            else if(Map[i][j]<5)
            {
                if((i+j)%2)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(middle.first+i,middle.second+60+2*j,"  ");
                    attroff(COLOR_PAIR(1));
                }
                else
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(middle.first+i,middle.second+60+2*j,"  ");
                    attroff(COLOR_PAIR(2));
                }

            }
            else
            {
                if((i+j)%2)
                attron(COLOR_PAIR(1));
                else
                attron(COLOR_PAIR(2));

                switch(Map[i][j]-6)
                {
                    case 0:
                        mvprintw(middle.first+i,middle.second+60+j*2,"⌛");
                        //⏰⌛
                        break;
                    case 1:
                        mvprintw(middle.first+i,middle.second+60+j*2,"⭐");
                        //🌠
                        break;
                    case 2:
                        mvprintw(middle.first+i,middle.second+60+j*2,"🍒");
                        //🌽🍀🍗🎃🍔🍒
                        break;
                    case 3:
                        mvprintw(middle.first+i,middle.second+60+j*2,"👻");
                        //👻💀😈
                        break;
                    case 4:
                        mvprintw(middle.first+i,middle.second+60+j*2,"🌀");
                        //🚀🚇㊙🌀
                        break;
                    case 5:
                        mvprintw(middle.first+i,middle.second+60+j*2,"😈");
                        break;
                    default :
                        mvprintw(middle.first+i,middle.second+60+j*2,"🍐");

                }

                if((i+j)%2)
                attroff(COLOR_PAIR(1));
                else
                attroff(COLOR_PAIR(2));


            }
            //🔲🔳▒▒ ░░ ▓▓ 
        }
    }


    

    refresh();

    move(0,0);

}


void snake_map::print_snake()
{
    snake_body* current=player1->get_head();

    while(current!=nullptr)
    {
        if(Map[current->position.first][current->position.second]==0)
        break;

        if((current->position.first+current->position.second)%2)
        {
            attron(COLOR_PAIR(1));
            mvprintw(middle.first+current->position.first,middle.second+60+2*current->position.second,"%s",player1->get_body_element());
            attroff(COLOR_PAIR(1));
        }
        else
        {
            attron(COLOR_PAIR(2));
            mvprintw(middle.first+current->position.first,middle.second+60+2*current->position.second,"%s",player1->get_body_element());
            attroff(COLOR_PAIR(2));
        }

        current=current->next;

        

    }

    if(player2==nullptr)
    return;

    current=player2->get_head();

    while(current!=nullptr)
    {
        if(Map[current->position.first][current->position.second]==0)
        break;
        
        if((current->position.first+current->position.second)%2)
        {
            attron(COLOR_PAIR(1));
            mvprintw(middle.first+current->position.first,middle.second+60+2*current->position.second,"%s",player2->get_body_element());
            attroff(COLOR_PAIR(1));
        }
        else
        {
            attron(COLOR_PAIR(2));
            mvprintw(middle.first+current->position.first,middle.second+60+2*current->position.second,"%s",player2->get_body_element());
            attroff(COLOR_PAIR(2));
        }

        current=current->next;

    }


}

int snake_map::get_point(int x,int y)
{
    return Map[x][y];
};

void snake_map::map_change_point(int x,int y,int v)
{
    Map[x][y]=v;
    return;
}


void snake_map::random_food()
{
    srand(time(NULL));

    int x=rand()%height+1;
    int y=rand()%width+1;

    while(Map[x][y]!=0)
    {
        x=rand()%height+1;
        y=rand()%width+1;
    }

    Map[x][y]=5;
    if((x+y)%2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(middle.first+x,middle.second+60+y*2,"🍐");
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        mvprintw(middle.first+x,middle.second+60+y*2,"🍐");
        attroff(COLOR_PAIR(2));
    }
    
    

    refresh();

    return;

}

bool snake_map::player_move_body()
{
    player_erase_tail();
    
    if(player2==nullptr)
    {
        bool result=player1->move_body();
        if(result==0)
        game_over(4);


        show_length();
        return result;
    }
    else
    {
        bool result1=player1->move_body(),result2=player2->move_body();

        if(player1->get_head_pos()==player2->get_head_pos())
        game_over(0);
        else if(result1==0)
        game_over(2);
        else if(result2==0)   
        game_over(1);

        show_length();
        return  result1&&result2 ;
    }
}

void snake_map::show_length()
{
    attron(COLOR_PAIR(3));
    mvprintw(middle.first+height/2,60+middle.second-20,"Player 1 eat %d foods",player1->get_length()-3);
    if(player2!=nullptr)
    mvprintw(middle.first+height/2,60+middle.second+2*width+4,"Player 2 eat %d foods",player2->get_length()-3);

}

void snake_map::game_over(int winner)
{
    if(winner==0)
    {
        player1->change_body_element("💀");
        player2->change_body_element("💀");
        print_snake();
        attron(COLOR_PAIR(4));
        mvprintw(middle.first+height/2-1,middle.second+60+width-3,"┌─────┐");
        mvprintw(middle.first+height/2,middle.second+60+width-3,  "│ Tie │");
        mvprintw(middle.first+height/2+1,middle.second+60+width-3,"└─────┘");
    }
    else if(winner==1)
    {
        player2->change_body_element("💀");
        print_snake();
        attron(COLOR_PAIR(4));
        mvprintw(middle.first+height/2-1,middle.second+60+width-3,"┌────────────────┐");
        mvprintw(middle.first+height/2,middle.second+60+width-3,  "│ Player 1 Win ! │");
        mvprintw(middle.first+height/2+1,middle.second+60+width-3,"└────────────────┘");

    }
    else if(winner==2)
    {
        player1->change_body_element("💀");
        print_snake();
        attron(COLOR_PAIR(4));
        mvprintw(middle.first+height/2-1,middle.second+60+width-3,"┌────────────────┐");
        mvprintw(middle.first+height/2,middle.second+60+width-3,  "│ Player 2 Win ! │");
        mvprintw(middle.first+height/2+1,middle.second+60+width-3,"└────────────────┘");
    }
    else
    {
        player1->change_body_element("💀");
        print_snake();
        attron(COLOR_PAIR(4));
        mvprintw(middle.first+height/2-1,middle.second+60+width-3,"┌────────────┐");
        mvprintw(middle.first+height/2,middle.second+60+width-3,  "│ You lose ! │");
        mvprintw(middle.first+height/2+1,middle.second+60+width-3,"└────────────┘");
        //mvprintw(middle.first+height/2,middle.second+60+width-3,"You lose !");
    }


    while(1)
    {
        int rel=getch();
        if(rel==10||rel==27)
        return;
    }
    
    

    return;
}

void snake_map::player_erase_tail()
{
    player1->erase_tail();

    if(player2!=nullptr)
    player2->erase_tail();
}

void snake_map::player_change_direction(int player , int n)
{
    if(player==1)
    player1->change_direction(n);
    else if(player2!=nullptr)
    player2->change_direction(n);
}

void snake_map::game_time()
{
    clock_t a,b;
    a=b=clock();

    while(1)
    {
        b=clock();
        if(b-a>time_interval)
        //if(b-a>5000)
        {
            while(kbhit())
            {
                int control=getch();
                if(control==27)
                {
                    if(pause())
                    return;
                }

                ungetch(control);
                player_control();
            }

            a=b=clock();
            if(player_move_body()==0)
            return;
            move(0,0);
            refresh();

            player_change_direction(1,-1);
            player_change_direction(2,-1);

        }
    
    }
}

bool snake_map::pause()
{
    attron(COLOR_PAIR(4));
    mvprintw(middle.first+height/2-5,60+middle.second+width-11,  "┌──────────────────────────┐");
    for(int i=1;i<=8;i++)
    mvprintw(middle.first+height/2+i-5,60+middle.second+width-11,"│                          │");
    mvprintw(middle.first+height/2+9-5,60+middle.second+width-11,"└──────────────────────────┘");
    

    mvprintw(middle.first+height/2-2,60+middle.second+width-1,"Continue");
    mvprintw(middle.first+height/2+2,60+middle.second+width-1,"Exit");
    mvprintw(middle.first+height/2-2,60+middle.second+width-6,"►");
    /*
    mvprintw(30,115,"Continue");
    mvprintw(35,115,"Exit");
    mvprintw(30,110,"►");
    */
    move(0,0);
    refresh();

    int state=0;
    int choice=0;


    clock_t a,b;

    a=b=clock();

    while(1)
    {

        if(kbhit())
        {
            switch(getch())
            {
                case KEY_UP:

                    mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6," ");

                    choice--;
                    if(choice<0)
                    choice=1;

                    mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6,"►");
                    //mvprintw(30+choice*5,110,"►");

                    a=b=clock();
                    state=0;
                    move(0,0);
                    refresh();

                    break;

                case KEY_DOWN:

                    //mvprintw(30+choice*5,110," ");
                    mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6," ");

                    choice++;
                    if(choice>1)
                    choice=0;

                    mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6,"►");
                    //mvprintw(30+choice*5,110,"►");

                    a=b=clock();
                    state=0;
                    move(0,0);
                    refresh();


                    break;

                case 10:
                    print();
                    print_snake();
                    return choice;
                    //break;
            }

        }


        b=clock();

        if(b-a>500000)
        {
            if(state)
            mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6,"►");
            else
            mvprintw(middle.first+height/2-2+4*choice,60+middle.second+width-6," ");

            move(0,0);
            refresh();
            state=!state;
            a=b=clock();
        }

    }






}


void snake_map::player_control()
{

    switch (getch())
    {
        case KEY_UP:
            player_change_direction(1,0);
            break;
        case KEY_RIGHT:
            player_change_direction(1,1);
            break;
        case KEY_DOWN:
            player_change_direction(1,2);
            break;
        case KEY_LEFT:
            player_change_direction(1,3);
            break;
        case 'w':
            player_change_direction(2,0);
            break;
        case 'd':
            player_change_direction(2,1);
            break;
        case 's':
            player_change_direction(2,2);
            break;
        case 'a':
            player_change_direction(2,3);
            break;

    }
}

int snake_map::get_width(){
    return width;
}

int snake_map::get_height(){
    return height;
}

snake* snake_map::get_player(int i)
{
    if(i==1)
    return player1;
    else
    return player2;
}

int snake_map::kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}



unwall_map::unwall_map(int player_1,int player_2,int food_num,int speed,std::pair<int,int> map_size):snake_map(player_1,player_2,food_num,speed,map_size){
    print();
    if(player_1==0)
    player1=new unwall_player_snake(this,1,"💠");
    else
    player1=new unwall_computer_snake(this,1,"💠");


    if(player_2==0)
    player2=nullptr;
    else if(player_2==1)
    player2=new unwall_player_snake(this,2,"💓");
    else
    player2=new unwall_computer_snake(this,2,"💓");
};

void unwall_map::print()
{
    attron(COLOR_PAIR(3));
    /*
    for(int i=2;i<height;i++)
    {        
        mvprintw(middle.first+i,middle.second+60+2," │");   
        //🔲🔳▒▒ ░░ ▓▓
    }
    for(int i=2;i<height;i++)
    {        
        mvprintw(middle.first+i,middle.second+60+2*width,"│ ");   
        //🔲🔳▒▒ ░░ ▓▓
    }
    for(int i=2;i<width;i++)
    {        
        mvprintw(middle.first+1,middle.second+60+2*i,"──");   
        //🔲🔳▒▒ ░░ ▓▓
    }
    for(int i=2;i<width;i++)
    {        
        mvprintw(middle.first+height,middle.second+60+2*i,"──");   
        //🔲🔳▒▒ ░░ ▓▓
    }

    mvprintw(middle.first+1,middle.second+60+2," ┌");
    mvprintw(middle.first+1,middle.second+60+2*width,"┐ ");
    mvprintw(middle.first+height,middle.second+60+2," └");
    mvprintw(middle.first+height,middle.second+60+2*width,"┘ ");
    */
    /*
    for(int i=1;i<=height;i++)
    {
        mvprintw(middle.first+i,middle.second+60+2,"  ");  
        mvprintw(middle.first+i,middle.second+60+2*width,"  ");  
    }


    for(int i=1;i<=width;i++)
    {
        mvprintw(middle.first+1,middle.second+60+2*i,"  ");  
        mvprintw(middle.first+height,middle.second+60+2*i,"  ");  
    }
    */
    for(int i=1;i<=height;i++)
    {
        for(int j=1;j<=width;j++)
        {
            //move(35+2*j,i);
            if(Map[i][j]==1)
            {
                attron(COLOR_PAIR(3));
                mvprintw(middle.first+i,middle.second+60+2*j,"  ");   
                attroff(COLOR_PAIR(3));
            }
            else if(Map[i][j]<5)
            {
                if((i+j)%2)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(middle.first+i,middle.second+60+2*j,"  ");
                    attroff(COLOR_PAIR(1));
                }
                else
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(middle.first+i,middle.second+60+2*j,"  ");
                    attroff(COLOR_PAIR(2));
                }

            }
            else
            {
                if((i+j)%2)
                attron(COLOR_PAIR(1));
                else
                attron(COLOR_PAIR(2));

                switch(Map[i][j]-6)
                {
                    case 0:
                        mvprintw(middle.first+i,middle.second+60+j*2,"⌛");
                        //⏰⌛
                        break;
                    case 1:
                        mvprintw(middle.first+i,middle.second+60+j*2,"⭐");
                        //🌠
                        break;
                    case 2:
                        mvprintw(middle.first+i,middle.second+60+j*2,"🍒");
                        //🌽🍀🍗🎃🍔🍒
                        break;
                    case 3:
                        mvprintw(middle.first+i,middle.second+60+j*2,"👻");
                        //👻💀😈
                        break;
                    case 4:
                        mvprintw(middle.first+i,middle.second+60+j*2,"🌀");
                        //🚀🚇㊙🌀
                        break;
                    case 5:
                        mvprintw(middle.first+i,middle.second+60+j*2,"😈");
                        break;
                    default :
                        mvprintw(middle.first+i,middle.second+60+j*2,"🍐");

                }

                if((i+j)%2)
                attroff(COLOR_PAIR(1));
                else
                attroff(COLOR_PAIR(2));


            }
            //🔲🔳▒▒ ░░ ▓▓ 
        }
    }

    refresh();

    move(0,0);

}


special_food_map::special_food_map(int player_1,int player_2,int food_num,int speed,std::pair<int,int> map_size):snake_map(player_1,player_2,0,speed,map_size){
    
    for(int i=0;i<food_num;i++)
    random_food();

    if(player_1==0)
    player1=new special_player_snake(this,1,"💠");
    else
    player1=new special_computer_snake(this,1,"💠");


    if(player_2==0)
    player2=nullptr;
    else if(player_2==1)
    player2=new special_player_snake(this,2,"💓");
    else
    player2=new special_computer_snake(this,2,"💓");


}

void special_food_map::random_food(){

    srand(time(NULL));
    check_food_type();
    
    int x=rand()%height+1;
    int y=rand()%width+1;

    while(Map[x][y]!=0)
    {
        x=rand()%height+1;
        y=rand()%width+1;
    }

    if((x+y)%2)
    attron(COLOR_PAIR(1));
    else
    attron(COLOR_PAIR(2));

    //int special_food=rand()%11;
    int special_food=1;

    switch(special_food)
    {
        case 0:
            mvprintw(middle.first+x,middle.second+60+y*2,"⌛");
            //⏰⌛
            break;
        case 1:
            mvprintw(middle.first+x,middle.second+60+y*2,"⭐");
            //🌠
            break;
        case 2:
            mvprintw(middle.first+x,middle.second+60+y*2,"🍒");
            //🌽🍀🍗🎃🍔🍒
            break;
        case 3:
            mvprintw(middle.first+x,middle.second+60+y*2,"👻");
            //👻💀😈
            break;
        case 4:
            mvprintw(middle.first+x,middle.second+60+y*2,"🌀");
            //🚀🚇㊙🌀
            break;
        case 5:
            mvprintw(middle.first+x,middle.second+60+y*2,"😈");
            break;
        default :
            mvprintw(middle.first+x,middle.second+60+y*2,"🍐");

    }

    if((x+y)%2)
    attroff(COLOR_PAIR(1));
    else
    attroff(COLOR_PAIR(2));

    if(special_food>5)
    Map[x][y]=5;
    else
    Map[x][y]=6+special_food;

}

void special_food_map::player_control()
{

    if(reverse_num>0)
    {
        reverse_control();
        return;
    }

    switch (getch())
    {
        case KEY_UP:
            player_change_direction(1,0);
            break;
        case KEY_RIGHT:
            player_change_direction(1,1);
            break;
        case KEY_DOWN:
            player_change_direction(1,2);
            break;
        case KEY_LEFT:
            player_change_direction(1,3);
            break;
        case 'w':
            player_change_direction(2,0);
            break;
        case 'd':
            player_change_direction(2,1);
            break;
        case 's':
            player_change_direction(2,2);
            break;
        case 'a':
            player_change_direction(2,3);
            break;
    }
}

void special_food_map::reverse_control()
{
    switch (getch())
    {
        case KEY_UP:
            player_change_direction(1,2);
            break;
        case KEY_RIGHT:
            player_change_direction(1,3);
            break;
        case KEY_DOWN:
            player_change_direction(1,0);
            break;
        case KEY_LEFT:
            player_change_direction(1,1);
            break;
        case 'w':
            player_change_direction(2,2);
            break;
        case 'd':
            player_change_direction(2,3);
            break;
        case 's':
            player_change_direction(2,0);
            break;
        case 'a':
            player_change_direction(2,1);
            break;

    }
}

bool special_food_map::player_move_body()
{
    player_erase_tail();
    if(reverse_num>0)
    reverse_num--;

    if(player2==nullptr)
    {
        bool result=player1->move_body();
        if(result==0)
        game_over(4);


        show_length();
        return result;
    }
    else
    {
        bool result1=player1->move_body(),result2=player2->move_body();

        if(player1->get_head_pos()==player2->get_head_pos())
        game_over(0);
        else if(result1==0)
        game_over(2);
        else if(result2==0)   
        game_over(1);

        show_length();
        return  result1&&result2 ;
    }
}

void special_food_map::check_food_type()
{
    
    int food_type=player1->get_eat_food()-6;

    if(time_interval%2==1)
    time_interval=(time_interval-1)/0.8;
    
    switch (food_type)
    {
        case 0:
            time_interval=time_interval*0.8+1;
            break;
        case 3:
            reverse_num=10;
            break;
        case 5:
            break;
    }

    if(player2==nullptr)
    return;

    food_type=player2->get_eat_food()-6;

    switch (food_type)
    {
        case 0:
            time_interval=time_interval*0.8+1;
            break;
        case 3:
            reverse_num=10;
            break;
        case 5:
            break;
    }
    
}

barrier_map::barrier_map(int player_1,int player_2,int food_num,int speed,std::pair<int,int> map_size):snake_map(player_1,player_2,food_num,speed,map_size){
    
}

void barrier_map::random_food()
{
    srand(time(NULL));

    int x=rand()%height+1;
    int y=rand()%width+1;

    while(Map[x][y]!=0)
    {
        x=rand()%height+1;
        y=rand()%width+1;
    }

    Map[x][y]=5;
    if((x+y)%2)
    {
        attron(COLOR_PAIR(1));
        mvprintw(middle.first+x,middle.second+60+y*2,"🍐");
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(2));
        mvprintw(middle.first+x,middle.second+60+y*2,"🍐");
        attroff(COLOR_PAIR(2));
    }
    refresh();

    if(player1->get_length()==3&&(player2==nullptr||player2->get_length()==3))
    return;


    x=rand()%height+1;
    y=rand()%width+1;

    while(Map[x][y]!=0)
    {
        x=rand()%height+1;
        y=rand()%width+1;
    }

    Map[x][y]=1;
    attron(COLOR_PAIR(4));
    mvprintw(middle.first+x,middle.second+60+y*2,"▓▓");
    attroff(COLOR_PAIR(4));
    
    refresh();

    
    

    return;

}



