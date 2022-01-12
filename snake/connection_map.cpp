#include "snake_map.h"
#include "snake.h"
#include <ncurses.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <fstream>
#include <errno.h>      ///< errno
#include <sys/socket.h> ///< socket
#include <netinet/in.h> ///< sockaddr_in
#include <arpa/inet.h>  ///< getsockname
#include <unistd.h>     ///< close
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include <ncurses.h>
#include <thread>
#include <future>
#include <netinet/tcp.h>
#include <fcntl.h>

connection_map::connection_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my):snake_map(player_1,player1_skin,player_2,player2_skin,food_num,speed,map_size)
{
    sock=s;
    my_snake=my;

    if(my_snake==1)
    connector_snake=2;
    else
    connector_snake=1;
}

void connection_map::game_time()
{
    int disable=1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(char*)&disable, sizeof(int));
    clock_t a, b;
    a = b = clock();

    while (1)
    {   

        while (kbhit())
        {
            int control = getch();
            if (control == 27)
            {
                if (pause())
                    return;
            }

            ungetch(control);
            player_control();
        }

        b = clock();
        if(b-a>time_interval-500&&b-a<time_interval)
        {
            vector<char> buf;//(10,' ');
            
            if(my_snake==1)
            buf.push_back(char('0'+player1->get_direction()));
            else
            buf.push_back(char('0'+player2->get_direction()));
            
            /*
            if(my_snake==1)
            buf[0]=char('0'+player1->get_direction());
            else
            buf[0]=char('0'+player2->get_direction());
            */

            
            send(sock,&buf[0],buf.size(),0);
        }
        else if (b - a > time_interval)
        {
            recv_player_control();  
            

            a = b = clock();
            if (player_move_body() == 0)
                return;

            move(0, 0);
            refresh();

            player_change_direction(1, -1);
            player_change_direction(2, -1);
        }
    }
}

void connection_map::player_control()
{
    switch (getch())
    {
        case KEY_UP:
            player_change_direction(my_snake, 0);
            break;
        case KEY_RIGHT:
            player_change_direction(my_snake, 1);
            break;
        case KEY_DOWN:
            player_change_direction(my_snake, 2);
            break;
        case KEY_LEFT:
            player_change_direction(my_snake, 3);
            break;
    }
    //int sendsu = send(sock, online_cho, sizeof(online_cho), 0);
    /*
    if (sendsu == -1)
    {
        mvprintw(7, 0, "Could not send to server!");
        return;
    }
    */
}

void connection_map::recv_player_control()
{
    char recvBuf[100] = {};
    int r=recv(sock, recvBuf, sizeof(recvBuf), 0);
    //if(r<0)
    //pause();

    switch (recvBuf[0])
    {
        case '0':
            player_change_direction(connector_snake, 0);
            break;
        case '1':
            player_change_direction(connector_snake, 1);
            break;
        case '2':
            player_change_direction(connector_snake, 2);
            break;
        case '3':
            player_change_direction(connector_snake, 3);
            break;
    }
}

connection_unwall_map::connection_unwall_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my):unwall_map(player_1,player1_skin,player_2,player2_skin,food_num,speed,map_size)
{
    sock=s;
    my_snake=my;

    if(my_snake==1)
    connector_snake=2;
    else
    connector_snake=1;
}

void connection_unwall_map::game_time()
{
    int disable=1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(char*)&disable, sizeof(int));
    clock_t a, b;
    a = b = clock();

    while (1)
    {   

        while (kbhit())
        {
            int control = getch();
            if (control == 27)
            {
                if (pause())
                    return;
            }

            ungetch(control);
            player_control();
        }

        b = clock();
        if(b-a>time_interval-500&&b-a<time_interval)
        {
            vector<char> buf;//(10,' ');
            
            if(my_snake==1)
            buf.push_back(char('0'+player1->get_direction()));
            else
            buf.push_back(char('0'+player2->get_direction()));
            
            /*
            if(my_snake==1)
            buf[0]=char('0'+player1->get_direction());
            else
            buf[0]=char('0'+player2->get_direction());
            */

            
            send(sock,&buf[0],buf.size(),0);
        }
        else if (b - a > time_interval)
        {
            recv_player_control();  
            

            a = b = clock();
            if (player_move_body() == 0)
                return;

            move(0, 0);
            refresh();

            player_change_direction(1, -1);
            player_change_direction(2, -1);
        }
    }
}

void connection_unwall_map::player_control()
{
    switch (getch())
    {
        case KEY_UP:
            player_change_direction(my_snake, 0);
            break;
        case KEY_RIGHT:
            player_change_direction(my_snake, 1);
            break;
        case KEY_DOWN:
            player_change_direction(my_snake, 2);
            break;
        case KEY_LEFT:
            player_change_direction(my_snake, 3);
            break;
    }
}

void connection_unwall_map::recv_player_control()
{
    char recvBuf[100] = {};
    int r=recv(sock, recvBuf, sizeof(recvBuf), 0);


    switch (recvBuf[0])
    {
        case '0':
            player_change_direction(connector_snake, 0);
            break;
        case '1':
            player_change_direction(connector_snake, 1);
            break;
        case '2':
            player_change_direction(connector_snake, 2);
            break;
        case '3':
            player_change_direction(connector_snake, 3);
            break;
    }
}


connection_special_map::connection_special_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my):special_food_map(player_1,player1_skin,player_2,player2_skin,food_num,speed,map_size)
{
    sock=s;
    my_snake=my;

    if(my_snake==1)
    connector_snake=2;
    else
    connector_snake=1;
}

void connection_special_map::game_time()
{
    int disable=1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(char*)&disable, sizeof(int));
    clock_t a, b;
    a = b = clock();

    while (1)
    {   

        while (kbhit())
        {
            int control = getch();
            if (control == 27)
            {
                if (pause())
                    return;
            }

            ungetch(control);
            player_control();
        }

        b = clock();
        if(b-a>time_interval-500&&b-a<time_interval)
        {
            vector<char> buf;//(10,' ');
            
            if(my_snake==1)
            buf.push_back(char('0'+player1->get_direction()));
            else
            buf.push_back(char('0'+player2->get_direction()));
            
            /*
            if(my_snake==1)
            buf[0]=char('0'+player1->get_direction());
            else
            buf[0]=char('0'+player2->get_direction());
            */

            
            send(sock,&buf[0],buf.size(),0);
        }
        else if (b - a > time_interval)
        {
            recv_player_control();  
            

            a = b = clock();
            if (player_move_body() == 0)
                return;

            move(0, 0);
            refresh();

            player_change_direction(1, -1);
            player_change_direction(2, -1);
        }
    }

}

void connection_special_map::player_control()
{
    switch (getch())
    {
        case KEY_UP:
            player_change_direction(my_snake, 0);
            break;
        case KEY_RIGHT:
            player_change_direction(my_snake, 1);
            break;
        case KEY_DOWN:
            player_change_direction(my_snake, 2);
            break;
        case KEY_LEFT:
            player_change_direction(my_snake, 3);
            break;
    }
}

void connection_special_map::recv_player_control()
{
    char recvBuf[100] = {};
    int r=recv(sock, recvBuf, sizeof(recvBuf), 0);
    //if(r<0)
    //pause();

    switch (recvBuf[0])
    {
        case '0':
            player_change_direction(connector_snake, 0);
            break;
        case '1':
            player_change_direction(connector_snake, 1);
            break;
        case '2':
            player_change_direction(connector_snake, 2);
            break;
        case '3':
            player_change_direction(connector_snake, 3);
            break;
    }
}

connection_barrier_map::connection_barrier_map(int player_1,char * player1_skin,int player_2,char* player2_skin,int food_num,int speed,std::pair<int,int> map_size,int s,int my):barrier_map(player_1,player1_skin,player_2,player2_skin,food_num,speed,map_size)
{
    sock=s;
    my_snake=my;

    if(my_snake==1)
    connector_snake=2;
    else
    connector_snake=1;
}

void connection_barrier_map::game_time()
{
    int disable=1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(char*)&disable, sizeof(int));
    clock_t a, b;
    a = b = clock();

    while (1)
    {   

        while (kbhit())
        {
            int control = getch();
            if (control == 27)
            {
                if (pause())
                    return;
            }

            ungetch(control);
            player_control();
        }

        b = clock();
        if(b-a>time_interval-500&&b-a<time_interval)
        {
            vector<char> buf;//(10,' ');
            
            if(my_snake==1)
            buf.push_back(char('0'+player1->get_direction()));
            else
            buf.push_back(char('0'+player2->get_direction()));
            
            /*
            if(my_snake==1)
            buf[0]=char('0'+player1->get_direction());
            else
            buf[0]=char('0'+player2->get_direction());
            */

            
            send(sock,&buf[0],buf.size(),0);
        }
        else if (b - a > time_interval)
        {
            recv_player_control();  
            

            a = b = clock();
            if (player_move_body() == 0)
                return;

            move(0, 0);
            refresh();

            player_change_direction(1, -1);
            player_change_direction(2, -1);
        }
    }
}

void connection_barrier_map::player_control()
{
    switch (getch())
    {
        case KEY_UP:
            player_change_direction(my_snake, 0);
            break;
        case KEY_RIGHT:
            player_change_direction(my_snake, 1);
            break;
        case KEY_DOWN:
            player_change_direction(my_snake, 2);
            break;
        case KEY_LEFT:
            player_change_direction(my_snake, 3);
            break;
    }
}

void connection_barrier_map::recv_player_control()
{
    char recvBuf[100] = {};
    int r=recv(sock, recvBuf, sizeof(recvBuf), 0);
    //if(r<0)
    //pause();

    switch (recvBuf[0])
    {
        case '0':
            player_change_direction(connector_snake, 0);
            break;
        case '1':
            player_change_direction(connector_snake, 1);
            break;
        case '2':
            player_change_direction(connector_snake, 2);
            break;
        case '3':
            player_change_direction(connector_snake, 3);
            break;
    }
}