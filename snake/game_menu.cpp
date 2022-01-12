#include "game_menu.h"
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <utility>
#include <python3.8/Python.h>
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
#include <fcntl.h>


//#include "python3.8/Python.h"
//#include <Python.h>
int binary_to_decimal(std::vector<unsigned char> data);
void input_binary_data(int digit,int data,std::ofstream &file);

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
                    choice=4;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(20+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    break;

                case KEY_DOWN:
                    mvprintw(20+5*choice,100," ");
                    choice++;

                    if(choice>4)
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
                    game_setting();                           
                    else if(choice==1)
                    load_game_setting();
                    else if(choice==2)
                    connect_play();    
                    else if(choice==3)
                    github();
                    else if(choice==4)
                    return;

                    choice=0;
                    print_initail_menu();
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
    int setting[8]={0};
    int setting_limit[8]={4,1,2,2,2,3,2,3};
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
                    mvprintw(15+5*choice,85," ");
                    mvprintw(15+5*choice,110," ");
                    mvprintw(15+5*choice,125," ");

                    choice--;
                    if(choice<0)
                    choice=7;
                        
                    
                    a=b=clock();
                    state=0;
                    
                    mvprintw(15+5*choice,85,"►");
                    mvprintw(15+5*choice,110,"◅");
                    mvprintw(15+5*choice,125,"▻");
                    move(0,0);
                    refresh();

                    break;

                case KEY_DOWN:
                    mvprintw(15+5*choice,85," ");
                    mvprintw(15+5*choice,110," ");
                    mvprintw(15+5*choice,125," ");

                    choice++;
                    if(choice>7)
                    choice=0;
                        
                    
                    a=b=clock();
                    state=0;
                    
                    mvprintw(15+5*choice,85,"►");
                    mvprintw(15+5*choice,110,"◅");
                    mvprintw(15+5*choice,125,"▻");
                    move(0,0);
                    refresh();
                    
                    break;

                case KEY_LEFT:
                    setting[choice]--;
                    if(setting[choice]<0)
                    setting[choice]=setting_limit[choice];

                    if((choice==4&&setting[3]==0)||(setting[0]==4&&choice>=5))
                    break;

                    if(choice==0&&setting[0]!=4)
                    {
                        game_change_setting(5,setting[5]);
                        game_change_setting(6,setting[6]);
                        game_change_setting(7,setting[7]);
                    }
                    else if(choice==0&&setting[0]==4)
                    {
                        mvprintw(40, 115, "❔      ");
                        mvprintw(45, 115, "❔      ");
                        mvprintw(50, 115, "❔      ");
                    }
                    

                    if(choice==3&&setting[3]!=0)
                    game_change_setting(4,setting[4]);
                    else if(choice==3&&setting[3]==0)
                    mvprintw(35,115,"X      ");

                    game_change_setting(choice,setting[choice]);
                    
                    break;

                case KEY_RIGHT:
                    setting[choice]++;
                    if(setting[choice]>setting_limit[choice])
                    setting[choice]=0;

                    if((choice==4&&setting[3]==0)||(setting[0]==4&&choice>=5))
                    break;

                    if(choice==0&&setting[0]!=4)
                    {
                        game_change_setting(5,setting[5]);
                        game_change_setting(6,setting[6]);
                        game_change_setting(7,setting[7]);
                    }
                    else if(choice==0&&setting[0]==4)
                    {
                        mvprintw(40, 115, "❔      ");
                        mvprintw(45, 115, "❔      ");
                        mvprintw(50, 115, "❔      ");
                    }

                    if(choice==3&&setting[3]!=0)
                    game_change_setting(4,setting[4]);
                    else if(choice==3&&setting[3]==0)
                    mvprintw(35,115,"X      ");

                    game_change_setting(choice,setting[choice]);
                    break;

                case 27:
                    
                    return;


                case 10:
                    if(setting[0]!=4)
                    into_game(setting[0],setting[1],setting[2],setting[3],setting[4],setting[5],setting[6],setting[7],0);
                    else
                    level_into_game(setting[1],setting[2],setting[3],setting[4]);
                    return;


            }

            


        }

        b=clock();

        if(b-a>500000)
        {
            if(state)
            mvprintw(15+5*choice,85,"►");
            else
            mvprintw(15+5*choice,85," ");

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
            switch_picture(setting);
            switch (setting)
            {
                case 0:
                    mvprintw(15,115,"Normal   ");
                    break;
                case 1:
                    mvprintw(15,115,"Unwall   ");
                    break;
                case 2:
                    mvprintw(15,115,"Barrier  ");
                    break;
                case 3:
                    mvprintw(15,115,"Special  ");
                    break;
                case 4:
                    mvprintw(15,115,"Challenge");
                    break;
                
            }
            break;
        case 1:
            switch (setting)
            {
                case 0:
                    mvprintw(20,115,"Player  ");
                    break;
                case 1:
                    mvprintw(20,115,"Computer  ");
                    break;
            }
            break;
        case 2:
            switch (setting)
            {
                case 0:
                    mvprintw(25,115,"💠💠💠");
                    break;
                case 1:
                    mvprintw(25,115,"💓💓💓");
                    break;
                case 2:
                    mvprintw(25,115,"💢💢💢");
                    break;
            }
            break;
        case 3:
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
        case 4:
            switch (setting)
            {
                case 0:
                    mvprintw(35,115,"💠💠💠");
                    break;
                case 1:
                    mvprintw(35,115,"💓💓💓");
                    break;
                case 2:
                    mvprintw(35,115,"💢💢💢");
                    break;
            }
            break;
        case 5:
            switch (setting)
            {
                case 0:
                    mvprintw(40,115,"1 ");
                    break;
                case 1:
                    mvprintw(40,115,"3 ");
                    break;
                case 2:
                    mvprintw(40,115,"5 ");
                    break;
                case 3:
                    mvprintw(40,115,"7 ");
                    break;
            }
            break;
        case 6:
            switch (setting)
            {
                case 0:
                    mvprintw(45,115,"Slow  ");
                    break;
                case 1:
                    mvprintw(45,115,"Middle");
                    break;
                case 2:
                    mvprintw(45,115,"Fast  ");
                    break;
                
            }
            break;

        case 7:
            switch (setting)
            {
                case 0:
                    mvprintw(50,115,"20*20");
                    break;
                case 1:
                    mvprintw(50,115,"30*30");
                    break;
                case 2:
                    mvprintw(50,115,"40*40");
                    break;
                case 3:
                    mvprintw(50,115,"50*50");
                    break;
                
                
            }
            break;

    }

    refresh();
    move(0,0);
}

void game_menu::into_game(int map,int player1,int player1_skin,int player2,int player2_skin,int food_num,int speed,int map_size,int load)
{
    while(1)
    {
        attron(COLOR_PAIR(3));
        snake_map *ptr;
        //speed=50000+20000*(2-speed);
        std::pair<int,int> size(20+10*map_size,20+10*map_size);
        char* skin[3]={"💠","💓","💢"};
        
        
        
        

        int tmp_food_num=food_num;
        if(load==1)
        {
            food_num=-2;
        }
        else
        {
            std::ofstream output_file("resume",std::ios::binary);
            input_binary_data(1,1,output_file);
            input_binary_data(3,map,output_file);
            input_binary_data(2,player1,output_file);
            input_binary_data(2,player1_skin,output_file);
            input_binary_data(2,player2,output_file);
            input_binary_data(2,player2_skin,output_file);
            input_binary_data(2,food_num,output_file);
            input_binary_data(2,speed,output_file);
            input_binary_data(2,map_size,output_file);
            output_file.close();
        }

        if(map==0)
        ptr=new snake_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size);
        else if(map==1)
        ptr=new unwall_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size);
        else if(map==2)
        ptr=new barrier_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size);
        else
        ptr=new special_food_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size);


        if(load==1)
        ptr->load_game(1+2*tmp_food_num),load=0,food_num=tmp_food_num;

        ptr->down_counter();
        ptr->game_time();

        if(play_again(ptr)==0)
        return;
    }

    
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
    mvprintw(25,105,"Load Game");
    mvprintw(30,105,"Play Online");
    mvprintw(35,105,"See Github");
    mvprintw(40,105,"Exit");

    mvprintw(20,100,"►");
    move(0,0);

}

void game_menu::print_game_setting_menu()
{
    mvprintw(15,95,"Game mode           ");
    mvprintw(20,95,"P1                  ");
    mvprintw(25,95,"P1 skin             ");
    mvprintw(30,95,"P2                  ");
    mvprintw(35,95,"P2 skin             ");
    mvprintw(40,95,"Food Number         ");
    mvprintw(45,95,"Move Speed          ");
    mvprintw(50,95,"Map size            ");

    mvprintw(19,100,"  ⍐");
    mvprintw(20,100,"⍇ ⍗ ⍈");
    mvprintw(29,100,"  🅆");
    mvprintw(30,100,"🄰 🅂 🄳");

    mvprintw(15,115,"Normal");
    mvprintw(20,115,"Player");
    mvprintw(25,115,"💠💠💠");
    mvprintw(30,115,"X");
    mvprintw(35,115,"X");
    mvprintw(40,115,"1");
    mvprintw(45,115,"Slow");
    mvprintw(50,115,"20*20");

    mvprintw(15,85,"►");
    mvprintw(15,110,"◅");
    mvprintw(15,125,"▻");
    //◅    ▻
    switch_picture(0);
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
        //mvprintw(20,95,"Error number: %s. Error message:%s",errno,strerror(errno));
        return "";
    }

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    //err = getsockname(sock, (struct sockaddr*)&name, &namelen);
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
        close(sock);

        return buffer;
    } 
    else
    {
        //mvprintw(20,95,"Error number: %s. Error message: %s",errno,strerror(errno));
        return "";
    }
    





}


void game_menu::connect_play()
{

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int client_sock=-1;
    int server_sock=-2;
    std::future<int> server_thread = std::async(&game_menu::thread_func,this,std::ref(sock));

    mvprintw(20,100,"                  ");
    mvprintw(25,100,"                  ");
    mvprintw(30,100,"                  ");
    mvprintw(35,100,"                  ");
    mvprintw(40,100,"                  ");

    

    mvprintw(22,98,"Connect with Your Friends");
    mvprintw(23,99,"┌──────────────────┐");
    mvprintw(24,99,"│                  │");
    mvprintw(25,99,"└──────────────────┘");
    
    mvprintw(27,100,"►");
    mvprintw(27,105,"Connect");
    mvprintw(32,105,"Exit");
    move(0,0);
    refresh();

    sleep(1);
    if(server_sock==-2)
    get_local_ipAddr();

    int choice=0;
    int state=0;


    clock_t a,b;

    a=b=clock();
    int rel;
    int num=0;
    std::vector<char> input_addr;

    while(1)
    {
        

        if (server_sock!=-1&&server_sock!=-2)
        {
            
            mvprintw(10, 0, "leave");
            game_server_setting(server_sock);
            print_initail_menu();
        }
        else if (client_sock!=-1)
        {

            
            mvprintw(5,0,"in,%d",client_sock);
            refresh();
            game_client_setting(client_sock);
            print_initail_menu();
        }

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

                        client_sock=socket_connect(input_addr);
                        if(client_sock!=-1)
                        {
                            mvprintw(0,0,"success!");                            
                            refresh();
                            break;
                        }
                        else
                        {
                            mvprintw(0,0,"fail");
                            break;
                        }
                        

                    }
                    else if(choice==1)
                    {
                        close(sock);
                        //close(sock);
                        return;
                    }
                
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

            if(server_sock==-2&&server_thread.wait_for(std::chrono::nanoseconds(1))==std::future_status::ready)
            server_sock=server_thread.get();
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

    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags|O_NONBLOCK);


    int r=connect(sock,(struct sockaddr*)&addr,sizeof(addr));

    if (r < 0) {  
        
        if (errno != EINPROGRESS && errno != EWOULDBLOCK) 
            return -1; 

        struct timeval tv;
        fd_set wset;

        tv.tv_sec = 3;
        tv.tv_usec = 0;

        FD_ZERO(&wset);
        FD_SET(sock, &wset); // Add socket to select to listen

        r = select(sock + 1, NULL, &wset, NULL, &tv);
        if (r < 0) {
            return -1; // error
        } else if (0 ==r) { 
            return -1;  // overtime
        }
        mvprintw(3,0,"!");
        refresh();
        
       //return -1;

    }

    fcntl(sock,F_SETFL,flags & ~O_NONBLOCK); 

    //mvprintw(0,0,"!");
    return sock;

}

void input_binary_data(int digit,int data,std::ofstream &file)
{
    //output_file << '1';
    std::vector<int> bit;
    for(int i=0;i<digit;i++)
    {
        if(data!=0)
        bit.push_back(data%2);
        else
        bit.push_back(0);

        data=data>>1;
    }
    std::reverse(bit.begin(),bit.end());

    for(int i=0;i<digit;i++)
    {
        file<<bit[i];
    }

    return;
}

void game_menu::load_game_setting()
{
    std::ifstream game_log;
    game_log.open("resume",std::ios::binary);
    if (game_log.fail()) {
        attron(COLOR_PAIR(4));
        mvprintw(23,99,"┌──────────────────┐");
        mvprintw(24,99,"│   No File Exist  │");
        mvprintw(25,99,"└──────────────────┘");
        attroff(COLOR_PAIR(4));
        move(0,0);
        refresh();
        sleep(1);
    }
    else
    {
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(game_log), {});
        if(buffer.size()<18)
        {
            attron(COLOR_PAIR(4));
            mvprintw(23,99,"┌──────────────────┐");
            mvprintw(24,99,"│   No File Exist  │");
            mvprintw(25,99,"└──────────────────┘");
            attroff(COLOR_PAIR(4));
            move(0,0);
            refresh();
            sleep(1);
        }
        else
        {
            //for(int i=0;i<buffer.size();i++)
            //mvprintw(0,i,"%c",buffer[i]);
            
            int game_mod=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+1,buffer.begin()+4));
            int player1=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+4,buffer.begin()+6));
            int player1_skin=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+6,buffer.begin()+8));
            int player2=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+8,buffer.begin()+10));
            int player2_skin=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+10,buffer.begin()+12));
            int food_num=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+12,buffer.begin()+14));
            int speed=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+14,buffer.begin()+16));
            int map_size=binary_to_decimal(std::vector<unsigned char>(buffer.begin()+16,buffer.begin()+18));
            //mvprintw(3,0,"%d",binary_to_decimal(std::vector<unsigned char>(buffer.begin()+10,buffer.begin()+12)));
            mvprintw(0,0,"%d",game_mod);
            mvprintw(1,0,"%d",player1);
            mvprintw(2,0,"%d",player1_skin);
            mvprintw(3,0,"%d",player2);
            mvprintw(4,0,"%d",player2_skin);
            mvprintw(5,0,"%d",food_num);
            mvprintw(6,0,"%d",speed);
            mvprintw(7,0,"%d",map_size);

            game_log.close();

            into_game(game_mod,player1,player1_skin,player2,player2_skin,food_num,speed,map_size,1);

        }
    }
    
    
    return;
}

int binary_to_decimal(std::vector<unsigned char> data)
{
    int r=0;
    for(int i=0;i<data.size();i++)
    {
        if(i!=0)
        r=r<<1;

        r+=data[i]-'0';
        //if(data[i]=='0')

    }

    return r;
}

bool game_menu::play_again(snake_map*ptr){
    while(1)
    {
        attron(COLOR_PAIR(4));

        mvprintw(ptr->middle.first+(ptr->get_height())/2-2,ptr->middle.second+60+ptr->get_width()-7,"┌─────────────────┐");
        mvprintw(ptr->middle.first+(ptr->get_height())/2-1,ptr->middle.second+60+ptr->get_width()-7,"│   Play Again?   │");
        mvprintw(ptr->middle.first+(ptr->get_height())/2,ptr->middle.second+60+ptr->get_width()-7,  "│                 │");
        mvprintw(ptr->middle.first+(ptr->get_height())/2+1,ptr->middle.second+60+ptr->get_width()-7,"│   ►   YES       │");
        mvprintw(ptr->middle.first+(ptr->get_height())/2+2,ptr->middle.second+60+ptr->get_width()-7,"│                 │");
        mvprintw(ptr->middle.first+(ptr->get_height())/2+3,ptr->middle.second+60+ptr->get_width()-7,"│       NO        │");
        mvprintw(ptr->middle.first+(ptr->get_height())/2+4,ptr->middle.second+60+ptr->get_width()-7,"└─────────────────┘");

        attroff(COLOR_PAIR(4));

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
                        attron(COLOR_PAIR(4));
                        mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3," ");
                        choice--;

                        if(choice<0)
                        choice=1;
                            
                        
                        a=b=clock();
                        state=0;
                        mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3,"►");
                        move(0,0);
                        refresh();
                        attroff(COLOR_PAIR(4));
                        break;

                    case KEY_DOWN:
                        attron(COLOR_PAIR(4));
                        mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3," ");
                        choice++;

                        if(choice>1)
                        choice=0;
                            
                        
                        a=b=clock();
                        state=0;
                        mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3,"►");
                        move(0,0);
                        refresh();
                        attroff(COLOR_PAIR(4));
                        
                        break;

                    case 27:
                        return 0;

                    case 10:
                    {
                        if(choice==0)
                        return 1;
                        else
                        return 0;
                        
                    }

                }

            }

            b=clock();

            if(b-a>500000)
            {
                attron(COLOR_PAIR(4));
                if(state)
                mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3,"►");
                else
                mvprintw(ptr->middle.first+(ptr->get_height())/2+1+2*choice,ptr->middle.second+60+ptr->get_width()-3," ");

                move(0,0);
                refresh();
                state=!state;
                a=b=clock();
                attroff(COLOR_PAIR(4));
            }

        }
        
    }
}


void game_menu::switch_picture(int choice)
{
    mvprintw(15 ,140,"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");
    mvprintw(16 ,140,"▓▓                        ▓▓");
    mvprintw(17 ,140,"▓▓                        ▓▓");
    mvprintw(18 ,140,"▓▓                        ▓▓");
    mvprintw(19 ,140,"▓▓                        ▓▓");
    mvprintw(20 ,140,"▓▓                        ▓▓");
    mvprintw(21 ,140,"▓▓                        ▓▓");
    mvprintw(22 ,140,"▓▓                        ▓▓");
    mvprintw(23 ,140,"▓▓                        ▓▓");
    mvprintw(24 ,140,"▓▓                        ▓▓");
    mvprintw(25 ,140,"▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓");
    switch (choice)
    {
        case 0:
                mvprintw(17 ,142," 💠💠💠💠🍐       ");
                mvprintw(18 ,142,"          ↘   💠+1 ");
                mvprintw(19 ,142,"   💠💠💠💠💠      ");
                mvprintw(20 ,142,"                       ");
                mvprintw(21 ,142,"                💠💠💠💠");
                mvprintw(22 ,142,"                   ⚠ ↘");
                mvprintw(23 ,142,"                  💀💀💀");
                mvprintw(27 ,140,"                            ");    
                mvprintw(29 ,140,"                            ");
                mvprintw(31 ,140,"                            ");
                mvprintw(33 ,140,"                            ");
                
                
                //mvprintw(23 ,176,"▓");
            break;
        case 1:
                mvprintw(17 ,142," 💠💠💠💠🍐       ");
                mvprintw(18 ,142,"          ↘   💠+1 ");
                mvprintw(19 ,142,"   💠💠💠💠💠      ");
                mvprintw(20 ,142,"                       ");
                mvprintw(21 ,142,"                💠💠💠💠");
                mvprintw(22 ,142,"                     ↘");
                mvprintw(23 ,142,"💠 ❕             💠💠💠");
                mvprintw(27 ,140,"                            ");    
                mvprintw(29 ,140,"                            ");
                mvprintw(31 ,140,"                            ");
                mvprintw(33 ,140,"                            ");
            break;
        case 2:
                mvprintw(17 ,142," 💠💠💠💠🍐       ");
                mvprintw(18 ,142,"          ↘   💠+1 ▓▓+1");
                mvprintw(19 ,142,"   💠💠💠💠💠      ");
                mvprintw(20 ,142,"                       ");
                mvprintw(21 ,142,"                💠💠💠💠");
                mvprintw(22 ,142,"                   ⚠ ↘");
                mvprintw(23 ,142,"                  💀💀💀");
                mvprintw(27 ,140,"                            ");    
                mvprintw(29 ,140,"                            ");
                mvprintw(31 ,140,"                            ");
                mvprintw(33 ,140,"                            ");

            break;
        case 3:
                mvprintw(17 ,142," 💠💠💠💠🎲       ");
                mvprintw(18 ,142,"          ↘   💠+1 ");
                mvprintw(19 ,142,"   💠💠💠💠💠      ");
                mvprintw(20 ,142,"                       ");
                mvprintw(21 ,142,"                💠💠💠💠");
                mvprintw(22 ,142,"                   ⚠ ↘");
                mvprintw(23 ,142,"                  💀💀💀");    
                mvprintw(27 ,140,"             🎲            ");                
                mvprintw(29 ,140,"  ⌛ Speed up  🌀 Teleport ");                
                mvprintw(31 ,140,"  ⭐ Invincible👻 Opposite  ");                
                mvprintw(33 ,140,"  🍒 Two Point 😈 Invisible ");
                
                
              
            break;
        case 4:

                mvprintw(17, 142, "    All Game Mode ❕   ");
                mvprintw(18, 142, "                       ");
                mvprintw(19, 142, "       10 Level   🚩   ");
                mvprintw(20, 142, "                       ");
                mvprintw(21, 142, "     Eat   Food   🍐   ");
                mvprintw(22, 142, "     Wait  Time   ⏰   ");
                mvprintw(23, 142, "     Limit Step   👣   ");
                mvprintw(27, 140, "     ⚠  Can't Save ⚠         ");
                mvprintw(29, 140, "                            ");
                mvprintw(31, 140, "                            ");
                mvprintw(33, 140, "                            ");


                break;
    }
    refresh();
    move(0,0);
}


int game_menu::thread_func(int &sock)
{
    //int sock = socket(AF_INET, SOCK_STREAM, 0);
    

    struct sockaddr_in serverInfo;
    if (sock == -1)
    {
        mvprintw(0,10,"sock error");
        return -1;
    }

    bzero(&serverInfo, sizeof(serverInfo));
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = htonl(INADDR_ANY);
    serverInfo.sin_port = htons(1102);
    int r=bind(sock, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
    
    if (r == -1)
    {
        mvprintw(0,10,"bind error");
        return -1;
    }
    

    if (listen(sock, SOMAXCONN) == -1)
    {
        mvprintw(0,10,"listen error");
        return -1;
    }

    fd_set rfd; 
    struct timeval tv;
    tv.tv_sec=1;
    tv.tv_usec=0;
    //int flags = fcntl(sock, F_GETFL, 0);
    //fcntl(sock, F_SETFL, flags|O_NONBLOCK);
    
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags|O_NONBLOCK);

    while(1)
    {

        int client_socket_fd = accept(sock, NULL, NULL);
        if (client_socket_fd == -1) {
            if (errno == EWOULDBLOCK) 
            {
                //printf("No pending connections; sleeping for one second.\n");
                sleep(1);
            }
            else 
            return -1;

        } 
        else 
        {
            mvprintw(0, 0, "I am server!");
            return client_socket_fd;
        }


    }
    /*
    struct sockaddr_in clientInfo;
    socklen_t addrlen = sizeof(clientInfo);
    int forClientSockfd = accept(sock, (struct sockaddr *)&clientInfo, &addrlen);
    if (forClientSockfd < 0)
    {
        mvprintw(0, 0, "fail!!");
        return -1;
    }
    else
    {
        mvprintw(0, 0, "I am server!");
        return forClientSockfd;
    }
    */
}


void game_menu::game_server_setting(int sock)
{
    mvprintw(17, 105, "                        ");
    mvprintw(18, 99, "                         ");
    mvprintw(19, 99, "                         ");
    mvprintw(20, 99, "                         ");
    mvprintw(22, 98, "                         ");
    mvprintw(23, 99, "                         ");
    mvprintw(24, 99, "                         ");
    mvprintw(25, 99, "                         ");
    mvprintw(27, 100, "                        ");
    mvprintw(27, 105, "                        ");
    mvprintw(32, 105, "                        ");
    print_game_setting_menu();
    //refresh();
    //mvprintw(25, 115, "Player");
    mvprintw(30, 115, "Player");
    mvprintw(35, 115, "💠💠💠");
    refresh();

    int choice = 0;
    int state = 0;
    int setting[8] = {0};
    int setting_limit[8] = {3, 0,2, 0,2, 3, 2, 3};
    char online_cho[10]; // key ... choice, state
    // memset(setting,0,sizeof(setting));

    struct timeval timeout;
    timeout.tv_sec=0;
    timeout.tv_usec=1;

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) == -1)
    {
        perror("setsockopt failed");
        return;
    }
    clock_t a, b;

    a = b = clock();

    while (1)
    {

        if (kbhit())
        {
            mvprintw(5, 0, "hi");
            // int cho = getch();
            // printw("%d", getch());
            switch (getch())
            {
                case KEY_UP:
                    mvprintw(15 + 5 * choice, 85, " ");
                    mvprintw(15 + 5 * choice, 110, " ");
                    mvprintw(15 + 5 * choice, 125, " ");

                    choice--;
                    if (choice < 0)
                        choice = 7;

                    a = b = clock();
                    state = 0;

                    mvprintw(15 + 5 * choice, 85, "►");
                    mvprintw(15 + 5 * choice, 110, "◅");
                    mvprintw(15 + 5 * choice, 125, "▻");
                    move(0, 0);
                    refresh();

                    online_cho[0] = '0';

                    break;

                case KEY_DOWN:
                    mvprintw(15 + 5 * choice, 85, " ");
                    mvprintw(15 + 5 * choice, 110, " ");
                    mvprintw(15 + 5 * choice, 125, " ");

                    choice++;
                    if (choice > 7)
                        choice = 0;

                    a = b = clock();
                    state = 0;

                    mvprintw(15 + 5 * choice, 85, "►");
                    mvprintw(15 + 5 * choice, 110, "◅");
                    mvprintw(15 + 5 * choice, 125, "▻");
                    move(0, 0);
                    refresh();

                    online_cho[0] = '1';

                    break;

                case KEY_LEFT:
                    setting[choice]--;
                    if (setting[choice] < 0)
                        setting[choice] = setting_limit[choice];



                    if(choice!=1&&choice!=3)
                    game_change_setting(choice, setting[choice]);

                    online_cho[0] = '2';

                    break;

                case KEY_RIGHT:
                    setting[choice]++;
                    if (setting[choice] > setting_limit[choice])
                        setting[choice] = 0;


                    if(choice!=1&&choice!=3)
                    game_change_setting(choice, setting[choice]);

                    online_cho[0] = '3';

                    break;

                case 27:
                    online_cho[0] = '4';
                    return;

                case 10:
                    online_cho[0] = '5';
                    int sendsu = send(sock, online_cho, sizeof(online_cho), 0);
                    if (sendsu == -1)
                    {
                        mvprintw(7, 0, "Could not send to server!");
                        return;
                    }
                    online_into_game(setting[0], 0,setting[2],1, setting[4], setting[5], setting[6], setting[7],sock,1);
                    return;
            }
            int sendsu = send(sock, online_cho, sizeof(online_cho), 0);
            if (sendsu == -1)
            {
                mvprintw(7, 0, "Could not send to server!");
                return;
            }
        }

        b = clock();

        if (b - a > 500000)
        {
            if (state)
                mvprintw(15 + 5 * choice, 85, "►");
            else
                mvprintw(15 + 5 * choice, 85, " ");

            move(0, 0);
            refresh();
            state = !state;
            a = b = clock();
        }
    }
}


void game_menu::game_client_setting(int sock)
{
    mvprintw(17, 105, "                        ");
    mvprintw(18, 99, "                         ");
    mvprintw(19, 99, "                         ");
    mvprintw(20, 99, "                         ");
    mvprintw(22, 98, "                         ");
    mvprintw(23, 99, "                         ");
    mvprintw(24, 99, "                         ");
    mvprintw(25, 99, "                         ");
    mvprintw(27, 100, "                        ");
    mvprintw(27, 105, "                        ");
    mvprintw(32, 105, "                        ");
    print_game_setting_menu();
    //refresh();
    //mvprintw(25, 115, "Player");
    mvprintw(30, 115, "Player");
    mvprintw(35, 115, "💠💠💠");
    refresh();

    int choice = 0;
    int state = 0;
    int setting[8] = {0};
    int setting_limit[8] = {3, 0,2, 0,2, 3, 2, 3};
    // memset(setting,0,sizeof(setting));


    struct timeval timeout;
    timeout.tv_sec=0;
    timeout.tv_usec=1;

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) == -1)
    {
        perror("setsockopt failed");
        return;
    }

    clock_t a, b;

    a = b = clock();

    while (1)
    {
        char recvBuf[1];
        int recvsu = recv(sock, recvBuf, sizeof(recvBuf), 0);
        mvprintw(10,0,"%d",recvsu);
        refresh();
        if(recvsu!=-1)
        {
            switch (recvBuf[0])
            {
                case '0':
                    mvprintw(15 + 5 * choice, 85, " ");
                    mvprintw(15 + 5 * choice, 110, " ");
                    mvprintw(15 + 5 * choice, 125, " ");

                    choice--;
                    if (choice < 0)
                        choice = 7;

                    a = b = clock();
                    state = 0;

                    mvprintw(15 + 5 * choice, 85, "►");
                    mvprintw(15 + 5 * choice, 110, "◅");
                    mvprintw(15 + 5 * choice, 125, "▻");
                    move(0, 0);
                    refresh();

                    

                    break;

                case '1':
                    mvprintw(15 + 5 * choice, 85, " ");
                    mvprintw(15 + 5 * choice, 110, " ");
                    mvprintw(15 + 5 * choice, 125, " ");

                    choice++;
                    if (choice > 7)
                        choice = 0;

                    a = b = clock();
                    state = 0;

                    mvprintw(15 + 5 * choice, 85, "►");
                    mvprintw(15 + 5 * choice, 110, "◅");
                    mvprintw(15 + 5 * choice, 125, "▻");
                    move(0, 0);
                    refresh();


                    break;

                case '2':
                    setting[choice]--;
                    if (setting[choice] < 0)
                        setting[choice] = setting_limit[choice];



                    if(choice!=1&&choice!=3)
                    game_change_setting(choice, setting[choice]);

                    break;

                case '3':
                    setting[choice]++;
                    if (setting[choice] > setting_limit[choice])
                        setting[choice] = 0;


                    if(choice!=1&&choice!=3)
                    game_change_setting(choice, setting[choice]);

                    break;

                case '4':

                    return;

                case '5':
                    online_into_game(setting[0], 0,setting[2],1, setting[4], setting[5], setting[6], setting[7],sock,2);
                    return;
            }
        }
        

        b = clock();

        mvprintw(1,0,"%d",b-a);

        if (b - a > 4000)
        {
            if (state)
                mvprintw(15 + 5 * choice, 85, "►");
            else
                mvprintw(15 + 5 * choice, 85, " ");

            move(0, 0);
            refresh();
            state = !state;
            a = b = clock();
        }
    }

}


void game_menu::online_into_game(int map,int player1,int player1_skin,int player2,int player2_skin,int food_num,int speed,int map_size,int sock,int my)
{
    while(1)
    {
        attron(COLOR_PAIR(3));
        snake_map *ptr;
        //speed=50000+20000*(2-speed);
        std::pair<int,int> size(20+10*map_size,20+10*map_size);
        char* skin[3]={"💠","💓","💢"};
        
        
        
        

        

        if(map==0)
        ptr=new connection_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,sock,my);
        //ptr=new snake_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,500000,size);
        else if(map==1)
        ptr=new connection_unwall_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,sock,my);
        else if(map==2)
        ptr=new connection_barrier_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,sock,my);
        else
        ptr=new connection_special_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,sock,my);



        ptr->down_counter();
        ptr->game_time();

        if(play_again(ptr)==0)
        return;
    }

    
}


void game_menu::level_into_game(int player1,int player1_skin,int player2,int player2_skin)
{
    int level_setting[11][4] =    {{0, 0, 0, 0}, {0, 1, 0, 0}, {2, 45, 3, 0}, {1, 10, 1, 0}, {3, 45, 3, 0}, {1, 1, 3, 0}, {2, 65, 2, 1}, {3, 5, 3, 2}, {2, 1, 0, 2}, {3, 50, 1, 2}, {1, 3, 1, 2}};
    int level_requirment[11][3] = {{0, 0, 0},   {0, 10, 0},     {60, 0, 0},   {0, 10, 200},  {30, 0, 0},     {0, 20, 0},   {120, 0, 0},  {0, 30, 999},  {0, 25, 0},   {0, 20, 0}, {0, 99, 0}};
    //int level_requirment[11][3] = {{1, 0, 0},   {1, 0, 0},     {1, 0, 0},   {1, 0, 200},  {1, 0, 0},     {1, 0, 0},   {1, 0, 0},  {1, 0, 999},  {0, 5 ,0},   {0, 5, 0}, {0, 5, 0}};
   
    char *skin[3] = {"💠", "💓", "💢"};

    while(1)
    {
        attron(COLOR_PAIR(3));
        snake_map *ptr;

        for(int level_num=1;level_num<11;level_num++)
        {



            int map=level_setting[level_num][0];
            int food_num=level_setting[level_num][1];
            std::pair<int, int> size(20 + 10 * level_setting[level_num][2], 20 + 10 * level_setting[level_num][2]);
            int speed=level_setting[level_num][3];

            
            if(map==0)
            ptr= new level_snake_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,level_requirment[level_num],level_num);
            else if(map==1)
            ptr = new level_unwall_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,level_requirment[level_num],level_num);
            else if(map==2)
            ptr = new level_barrier_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,level_requirment[level_num],level_num);
            else 
            ptr = new level_special_food_map(player1,skin[player1_skin],player2,skin[player2_skin],1+2*food_num,50000+20000*(2-speed),size,level_requirment[level_num],level_num);
            

            ptr->down_counter();
            ptr->game_time();

            if(ptr->get_width()!=-1)
            break;

            into_next_level();
            

        }

        while (1)
        {
            int rel = getch();
            if (rel == 10 || rel == 27)
                break;;
        }


        if (play_again(ptr) == 0)
        return;
    }


}


void game_menu::into_next_level()
{
    attron(COLOR_PAIR(3));

    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 250; j++)
            mvprintw(i, j, " ");
    }

    int a = 20, b = 60, t = 200 * 1000;

    mvprintw(a, b,     "  ▓▓          ▓▓▓▓▓▓▓▓▓▓  ▓▓      ▓▓  ▓▓▓▓▓▓▓▓▓▓  ▓▓              ▓▓      ▓▓  ▓▓▓▓▓▓▓▓   ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 1, b, "  ▓▓          ▓▓          ▓▓      ▓▓  ▓▓          ▓▓              ▓▓      ▓▓  ▓▓      ▓▓ ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 2, b, "  ▓▓          ▓▓▓▓▓▓      ▓▓      ▓▓  ▓▓▓▓▓▓      ▓▓              ▓▓      ▓▓  ▓▓▓▓▓▓▓▓   ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 3, b, "  ▓▓          ▓▓          ▓▓      ▓▓  ▓▓          ▓▓              ▓▓      ▓▓  ▓▓         ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 4, b, "  ▓▓          ▓▓            ▓▓  ▓▓    ▓▓          ▓▓              ▓▓      ▓▓  ▓▓         ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 5, b, "  ▓▓          ▓▓            ▓▓  ▓▓    ▓▓          ▓▓              ▓▓      ▓▓  ▓▓         ");
    move(0, 0);
    refresh();
    usleep(t);
    mvprintw(a + 6, b, "  ▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓      ▓▓      ▓▓▓▓▓▓▓▓▓▓  ▓▓▓▓▓▓▓▓▓▓        ▓▓▓▓▓▓    ▓▓         ");

    move(0, 0);
    refresh();
    usleep(t * 3);
}