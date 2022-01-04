#include "game_menu.h"
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <utility>
#include <python3.8/Python.h>
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


//#include "python3.8/Python.h"
//#include <Python.h>

int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void game_menu::initial_menu()
{
    
    
    //135 206 250
    //67 205 128
    //64 224 208
    //	32 178 170
    //245 245 220
    //front
    //	65 105 225
    // 70 130 180
    // 100 105 225
    // 125 105 255
    //back

    start_color();
    double x=3.92;
    init_color(COLOR_CYAN, 245*x, 245*x, 220*x);
    init_color(COLOR_BLUE, 125*x, 105*x, 255*x);
    init_color(COLOR_RED,  71*x  ,60*x, 139*x);
    init_pair(1,COLOR_RED,COLOR_RED);
    init_pair(2,COLOR_MAGENTA,COLOR_MAGENTA);
    init_pair(3,COLOR_CYAN,COLOR_BLUE);
    init_pair(4,COLOR_BLUE,COLOR_CYAN);
    

    print_initail_menu();

    

    int choice=0;
    int state=0;


    clock_t a,b;

    a=b=clock();

    while(1)
    {
        if(kbhit())
        {
            //printw("%d",getch());
            switch (getch())
            {
                case KEY_UP:

                    mvprintw(20+5*choice,100," ");
                    choice--;

                    if(choice<0)
                    choice=3;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(20+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    break;

                case KEY_DOWN:
                    mvprintw(20+5*choice,100," ");
                    choice++;

                    if(choice>3)
                    choice=0;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(20+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    
                    break;

                case 27:
                    return;


                case 10:
                {
                    if(choice==0)
                    {
                        game_setting();
                        print_initail_menu();
                    }
                    else if(choice==1)
                    {
                        connect_play();
                        print_initail_menu();
                        choice=0;
                    }
                    //get_local_ipAddr();
                    else if(choice==2)
                    github();
                    else if(choice==3)
                    return;
                }


            }

            


        }

        b=clock();

        if(b-a>500000)
        {
            if(state)
            mvprintw(20+5*choice,100,"►");
            else
            mvprintw(20+5*choice,100," ");

            move(0,0);
            refresh();
            state=!state;
            a=b=clock();
        }

        


    }
   

    //mvprintw(9,0,"💠💠💠💠💠");
    

    move(0,0);

    refresh();
}


void game_menu::game_setting()
{

    print_game_setting_menu();


    int choice=0;
    int state=0;
    int setting[6]={0};
    int setting_limit[6]={3,1,2,3,2,3};
    //memset(setting,0,sizeof(setting));


   

    clock_t a,b;

    a=b=clock();

    while(1)
    {
        if(kbhit())
        {
            //printw("%d",getch());
            switch (getch())
            {
                case KEY_UP:
                    mvprintw(20+5*choice,85," ");
                    mvprintw(20+5*choice,110," ");
                    mvprintw(20+5*choice,125," ");

                    choice--;
                    if(choice<0)
                    choice=5;
                        
                    
                    a=b=clock();
                    state=0;
                    
                    mvprintw(20+5*choice,85,"►");
                    mvprintw(20+5*choice,110,"◅");
                    mvprintw(20+5*choice,125,"▻");
                    move(0,0);
                    refresh();

                    break;

                case KEY_DOWN:
                    mvprintw(20+5*choice,85," ");
                    mvprintw(20+5*choice,110," ");
                    mvprintw(20+5*choice,125," ");

                    choice++;
                    if(choice>5)
                    choice=0;
                        
                    
                    a=b=clock();
                    state=0;
                    
                    mvprintw(20+5*choice,85,"►");
                    mvprintw(20+5*choice,110,"◅");
                    mvprintw(20+5*choice,125,"▻");
                    move(0,0);
                    refresh();
                    
                    break;

                case KEY_LEFT:
                    setting[choice]--;
                    if(setting[choice]<0)
                    setting[choice]=setting_limit[choice];

                    
                    game_change_setting(choice,setting[choice]);
                    
                    break;

                case KEY_RIGHT:
                    setting[choice]++;
                    if(setting[choice]>setting_limit[choice])
                    setting[choice]=0;

                    
                    game_change_setting(choice,setting[choice]);
                    break;

                case 27:
                    
                    return;


                case 10:
                    into_game(setting[0],setting[1],setting[2],setting[3],setting[4],setting[5]);
                    return;


            }

            


        }

        b=clock();

        if(b-a>500000)
        {
            if(state)
            mvprintw(20+5*choice,85,"►");
            else
            mvprintw(20+5*choice,85," ");

            move(0,0);
            refresh();
            state=!state;
            a=b=clock();
        }

        


    }


}


void game_menu::game_change_setting(int choice,int setting)
{
    switch (choice)
    {
        case 0:
            switch (setting)
            {
                case 0:
                    mvprintw(20,115,"Normal  ");
                    break;
                case 1:
                    mvprintw(20,115,"Unwall  ");
                    break;
                case 2:
                    mvprintw(20,115,"Barrier ");
                    break;
                case 3:
                    mvprintw(20,115,"Special ");
                    break;
            }
            break;
        case 1:
            switch (setting)
            {
                case 0:
                    mvprintw(25,115,"Player  ");
                    break;
                case 1:
                    mvprintw(25,115,"Computer  ");
                    break;
            }
            break;
        case 2:
            switch (setting)
            {
                case 0:
                    mvprintw(30,115,"X        ");
                    break;
                case 1:
                    mvprintw(30,115,"Player    ");
                    break;
                case 2:
                    mvprintw(30,115,"Computer  ");
                    break;
            }
            break;
        case 3:
            switch (setting)
            {
                case 0:
                    mvprintw(35,115,"1");
                    break;
                case 1:
                    mvprintw(35,115,"3");
                    break;
                case 2:
                    mvprintw(35,115,"5");
                    break;
                case 3:
                    mvprintw(35,115,"7");
                    break;
            }
            break;
        case 4:
            switch (setting)
            {
                case 0:
                    mvprintw(40,115,"Slow  ");
                    break;
                case 1:
                    mvprintw(40,115,"Middle");
                    break;
                case 2:
                    mvprintw(40,115,"Fast  ");
                    break;
                
            }
            break;

        case 5:
            switch (setting)
            {
                case 0:
                    mvprintw(45,115,"20*20");
                    break;
                case 1:
                    mvprintw(45,115,"30*30");
                    break;
                case 2:
                    mvprintw(45,115,"40*40");
                    break;
                case 3:
                    mvprintw(45,115,"50*50");
                    break;
                
                
            }
            break;

    }

    refresh();
    move(0,0);
}

void game_menu::into_game(int map,int player1,int player2,int food_num,int speed,int map_size)
{
    snake_map *ptr;
    speed=50000+20000*(2-speed);
    std::pair<int,int> size(20+10*map_size,20+10*map_size);

    if(map==0)
    ptr=new snake_map(player1,player2,1+2*food_num,speed,size);
    else if(map==1)
    ptr=new unwall_map(player1,player2,1+2*food_num,speed,size);
    else if(map==2)
    ptr=new barrier_map(player1,player2,1+2*food_num,speed,size);
    else
    ptr=new special_food_map(player1,player2,1+2*food_num,speed,size);

    ptr->down_counter();
    ptr->game_time();

    
}



void game_menu::print_initail_menu()
{
    attron(COLOR_PAIR(3));
    
    for(int i=0;i<200;i++)
    {
        for(int j=0;j<250;j++)
        mvprintw(i,j," ");
    }
    
    mvprintw(5 ,80,"  ▓▓▓▓      ▓▓    ▓▓      ▓▓▓▓      ▓▓    ▓▓    ▓▓▓▓▓▓▓▓");
    mvprintw(6 ,80,"▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓      ");
    mvprintw(7 ,80,"▓▓          ▓▓▓▓  ▓▓    ▓▓    ▓▓    ▓▓  ▓▓      ▓▓      ");
    mvprintw(8 ,80,"  ▓▓▓▓      ▓▓  ▓▓▓▓    ▓▓    ▓▓    ▓▓▓▓        ▓▓▓▓▓▓  ");
    mvprintw(9 ,80,"      ▓▓    ▓▓    ▓▓    ▓▓▓▓▓▓▓▓    ▓▓  ▓▓      ▓▓      ");
    mvprintw(10,80,"▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓      ");
    mvprintw(11,80,"  ▓▓▓▓      ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓    ▓▓▓▓▓▓▓▓");
    

    mvprintw(20,105,"Play");
    mvprintw(25,105,"Play Online");
    mvprintw(30,105,"See Github");
    mvprintw(35,105,"Exit");

    mvprintw(20,100,"►");
    move(0,0);

}

void game_menu::print_game_setting_menu()
{
    mvprintw(20,95,"Game mode           ");
    mvprintw(25,95,"P1                  ");
    mvprintw(30,95,"P2                  ");
    mvprintw(35,95,"Food Number");
    mvprintw(40,95,"Move Speed");
    mvprintw(45,95,"Map size  ");

    mvprintw(20,115,"Normal");
    mvprintw(25,115,"Player");
    mvprintw(30,115,"X");
    mvprintw(35,115,"1");
    mvprintw(40,115,"Slow");
    mvprintw(45,115,"20*20");

    mvprintw(20,85,"►");
    mvprintw(20,110,"◅");
    mvprintw(20,125,"▻");
    //◅    ▻
    move(0,0);
}

void game_menu::github()
{

    Py_Initialize();
    
    int res;
    PyObject *pModule=NULL;
    PyObject *pFunc=NULL;
    PyObject *pArgs=NULL;
    PyObject *pResult=NULL;


    if( !Py_IsInitialized()){
		mvprintw(0,0,"Error");
		return;
	}
    /*
    if(!(pModule=PyImport_Import(PyUnicode_FromString("mygithub"))))
    {
        mvprintw(1,0,"Error");
        return;
    }
    
    if(!(pFunc=PyObject_GetAttrString(pModule, "mygithub")))
    {
        mvprintw(2,0,"Error");
        return;
    }

    pResult=PyObject_CallObject(pFunc, pArgs);
    if(pArgs)
    Py_DECREF(pArgs);
    if(pFunc)
    Py_DECREF(pFunc);
    */
    
    PyRun_SimpleString("import webbrowser");
    PyRun_SimpleString("webbrowser.open('https://github.com/Yui-Arthur/Snake-Game', new=2)");    
    

    Py_Finalize();
    



}


char* game_menu::get_local_ipAddr()
{

    const char* google_dns_server = "8.8.8.8";
    int dns_port = 53;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0)
    {
        mvprintw(20,95,"Socket error");
        return "";
    }
    

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(google_dns_server);
    serv.sin_port = htons(dns_port);

    int err = connect(sock, (const struct sockaddr*)&serv, sizeof(serv));
    if (err < 0)
    {
        mvprintw(20,95,"Error number: %s. Error message:%s",errno,strerror(errno));
        return "";
    }

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*)&name, &namelen);
    char buffer[100];
    const char* p=inet_ntop(AF_INET, &name.sin_addr, buffer, 80);

    if(p != nullptr)
    {
        //┌─┐
        //│ │
        //└─┘
        mvprintw(17,105,"Your IP");
        mvprintw(18,99,"┌──────────────────┐");
        mvprintw(19,99,"│                  │");
        mvprintw(20,99,"└──────────────────┘");
        mvprintw(19,102,"%s",buffer);

        return buffer;
    } 
    else
    {
        mvprintw(20,95,"Error number: %s. Error message: %s",errno,strerror(errno));
        return "";
    }
    





}


void game_menu::connect_play()
{

    mvprintw(20,100,"                  ");
    mvprintw(25,100,"                  ");
    mvprintw(30,100,"                  ");
    mvprintw(35,100,"                  ");
    
    get_local_ipAddr();

    mvprintw(22,98,"Connect with Your Friends");
    mvprintw(23,99,"┌──────────────────┐");
    mvprintw(24,99,"│                  │");
    mvprintw(25,99,"└──────────────────┘");
    
    mvprintw(27,100,"►");
    mvprintw(27,105,"Connect");
    mvprintw(32,105,"Exit");
    move(0,0);
    int choice=0;
    int state=0;


    clock_t a,b;

    a=b=clock();
    int rel;
    int num=0;
    std::vector<char> input_addr;

    while(1)
    {
        if(kbhit())
        {
            //printw("%d",getch());
            switch (rel=getch())
            {
                case KEY_UP:

                    mvprintw(27+5*choice,100," ");
                    choice--;

                    if(choice<0)
                    choice=1;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(27+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    break;

                case KEY_DOWN:
                    mvprintw(27+5*choice,100," ");
                    choice++;

                    if(choice>1)
                    choice=0;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(27+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    
                    break;

                case 27:
                    return;


                case 10:
                    if(choice==0)
                    {
                        if(input_addr.empty())
                        break;

                        int sock=socket_connect(input_addr);
                        if(sock!=-1)
                        mvprintw(0,0,"success!");
                        break;

                    }
                    else if(choice==1)
                    return;
                
                case KEY_BACKSPACE:

                    if(!input_addr.empty())
                    {
                        num--,input_addr.pop_back();
                        mvprintw(24,102+num," ");
                        move(0,0);
                    }
                    break;
                
                default:
                    if((rel==46||rel>=48&&rel<=57)&&input_addr.size()<=15)
                    {
                        mvprintw(24,102+num,"%c",char(rel));
                        num++;
                        input_addr.push_back(char(rel));
                        move(0,0);
                    }
                    
                    



            }

            


        }

        b=clock();

        if(b-a>500000)
        {
            if(state)
            mvprintw(27+5*choice,100,"►");
            else
            mvprintw(27+5*choice,100," ");

            move(0,0);
            refresh();
            state=!state;
            a=b=clock();
        }

    
    }

}

int game_menu::socket_connect(std::vector<char> input_addr)
{
    
    int sock=socket(AF_INET,SOCK_STREAM,0);

    if(sock<0)
    {
        mvprintw(24,102,"Socket Error");
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(1102);
    addr.sin_addr.s_addr=inet_addr(&input_addr[0]);

    int r=connect(sock,(struct sockaddr*)&addr,sizeof(addr));
    //"61.227.224.135"
    if(r==-1)
    {
        perror("fail");
        return -1;
    }

    //mvprintw(0,0,"!");
    return r;

}