#include "game_menu.h"
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <utility>
#include <python3.8/Python.h>
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
                    choice=2;
                        
                    
                    a=b=clock();
                    state=0;
                    mvprintw(20+5*choice,100,"►");
                    move(0,0);
                    refresh();
                    break;

                case KEY_DOWN:
                    mvprintw(20+5*choice,100," ");
                    choice++;

                    if(choice>2)
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
                    github();
                    else if(choice==2)
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
    mvprintw(25,105,"See Github");
    mvprintw(30,105,"Exit");

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