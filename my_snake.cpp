#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <fstream>


#define vert 22
#define horiz 62
#define max 22*62

int score = 1, diff = 1, high_score;
char direc = 'D';
bool end_game = false;

struct _locate{
    int x, y;
};

_locate snake[max], food;

void gotoxy(int x, int y);
void game_start();
void game_play();
void show_game_board();
void move();
void help();
void diff_select();
void save_high_score();
int read_high_score(int high_score);
bool check(int x, int y);
_locate gen_food();


int main(){ 
    high_score = read_high_score();
    std::string waiting [4];
    
    waiting[0] = "play";
    waiting[1] = "help";
    waiting[2] = "high score";
    waiting[3] = "exit";
    int i = 0;
    while (i!=3)
    {  
        for (int i=0; i<4; i++){
            gotoxy(int((60 - waiting[i].length())/2), 10+i);
            std::cout<<waiting[i];
        }
        
        std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
        gotoxy(int((60 - waiting[i].length())/2), 10+i);
        std::cout<<waiting[i];
        char a = ' ';
        while ((a !=13)){
            do{
                a = toupper(getch());
            }while((a!='W')&&(a!='S')&&(a!=13));
            if (a == 'W'){
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::tolower);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
                i--;
                if (i<0) i=3;
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
            }
            if (a == 'S'){
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::tolower);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
                i++;
                if (i>3) i=0;
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
            }
            if (a == 13){
                switch (i){
                    case 1:
                        help();
                        break;
                    case 2:
                        gotoxy(5,5);
                        std::cout<<"Diem cao nhat: "<<high_score;
                        break;
                    case 0:
                        game_start();
                        do {
                            direc = toupper(getch());
                        }
                        while ((direc!='W') && (direc!='D') && (direc!='S'));
                        game_play();
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
    return 0;
}

int read_high_score(){
    int high_score;
    std::ifstream f;
    f.open("high_score.dat"); 
    f>>high_score;
    f.close();
    return high_score;
}

void help(){
    system("cls");
    gotoxy(5,5);
    std::cout<<"Phim A: Di chuyen sang trai";
    gotoxy(5,6);
    std::cout<<"Phim D: Di chuyen sang phai";
    gotoxy(5,7);
    std::cout<<"Phim W: Di chuyen len tren";
    gotoxy(5,8);
    std::cout<<"Phim S: Di chuyen Xuong duoi";
    getch();
    system("cls");
}

void save_high_score(int high_score){
    std::ofstream f;
    f.open("high_score.dat"); 
    f<<high_score;
    f.close();
}

void diff_select(){
    gotoxy(5,5);
    std::cout<<"Chon do kho: <<"<<diff<<">>";
    char a = toupper(getch());
    while (a!=13){
        if ((a == 'A') || (a == 'S')) diff--;
        if ((a == 'W') || (a == 'D')) diff++;
        if (diff>4) diff = 1;
        if (diff<1) diff = 4;
        gotoxy(5,5);
        std::cout<<"Chon do kho: <<"<<diff<<">>";
        a = toupper(getch());
    }
    gotoxy(5,5);
    std::cout<<"                  ";
}

/*void waiting(){
    std::string waiting [4];
    
    waiting[0] = "play";
    waiting[1] = "help";
    waiting[2] = "high score";
    waiting[3] = "exit";
    int i = 0;
    while (i!=3)
    {  
        for (int i=0; i<4; i++){
            gotoxy(int((60 - waiting[i].length())/2), 10+i);
            std::cout<<waiting[i];
        }
        
        std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
        gotoxy(int((60 - waiting[i].length())/2), 10+i);
        std::cout<<waiting[i];
        char a = ' ';
        while ((a !=13)){
            do{
                a = toupper(getch());
            }while((a!='W')&&(a!='S')&&(a!=13));
            if (a == 'W'){
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::tolower);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
                i--;
                if (i<0) i=3;
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
            }
            if (a == 'S'){
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::tolower);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
                i++;
                if (i>3) i=0;
                std::transform(waiting[i].begin(), waiting[i].end(),waiting[i].begin(), ::toupper);
                gotoxy(int((60 - waiting[i].length())/2), 10+i);
                std::cout<<waiting[i];
            }
            if (a == 13){
                switch (i){
                    case 1:
                        help();
                        break;
                    case 2:
                        gotoxy(5,5);
                        std::cout<<"Điểm cao nhất: "<<high_score;
                        break;
                    case 0:
                        game_start();
                        do {
                            direc = toupper(getch());
                        }
                        while ((direc!='W') && (direc!='D') && (direc!='S'));
                        game_play();
                        break;
                    
                    default:
                        break;
                }
            }
        }
    }
    
}
*/
bool check(int x, int y){
    for (int i = 0; i<=score; i++){
        if ((x == snake[i].x) && (y == snake[i].y))
            return false;
    }
    return ((x>0) && (x<61) && (y>0) && (y<21));
}

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = {x, y};
  SetConsoleCursorPosition(h,c);
}

_locate gen_food(){
    int x,y;
    do{
        x = rand() % (60 - 1 + 1) + 1;
        y = rand() % (20 - 1 + 1) + 1;
    }
    while (!check(x, y));
    return {x, y};
}

void show_game_board(){
    system("cls");
    for (int i = 0; i<vert; i++){
        gotoxy(0,i);
        std::cout<<"x";
        gotoxy(horiz,i);
        std::cout<<"x";
        Sleep(10);
    }
    for (int i = 0; i<horiz; i++){
        gotoxy(i, 0);
        std::cout<<"x";
        gotoxy(i, vert);
        std::cout<<"x";
        Sleep(10);
    }
    for (int i = vert; i<vert+4; i++){
        gotoxy(31,i);
        std::cout<<"x";
        gotoxy(horiz,i);
        std::cout<<"x";
        Sleep(10);
    }
    for (int i = 31; i<horiz; i++){
        gotoxy(i, vert+3);
        std::cout<<"x";
        Sleep(10);
    }

    gotoxy(food.x, food.y);
    std::cout<<'*';
    gotoxy(snake[0].x, snake[0].y);
    std::cout<<'S';
    gotoxy(snake[1].x, snake[1].y);
    std::cout<<'S';
    gotoxy(38, 24);
    std::cout<<"Score: "<<score<<"   ";
}

void game_start(){
    snake[0]={2,10};
    snake[1]={1,10};
    end_game = false;
    score = 1;
    food = gen_food();
    show_game_board();
    diff_select();
}

void move(){
    _locate vect;
    switch (direc)
    {
    case 'D':
        vect = {1, 0};
        break;
    case 'A':
        vect = {-1, 0};
        break;
    case 'W':
        vect = {0, -1};
        break;
    case 'S':
        vect = {0, 1};
        break;
    default:
        break;
    }
    /**/
    if (check(snake[0].x + vect.x, snake[0].y + vect.y)){
        if ((snake[0].x + vect.x == food.x) && (snake[0].y + vect.y == food.y)){
            score++;
            food = gen_food();
            gotoxy(food.x, food.y);
            std::cout<<'*';
        }else{
            gotoxy(snake[score].x, snake[score].y);
            std::cout<<' ';
        };
        for (int i=score; i>0; i--){
            snake[i]=snake[i-1];
        }
        snake[0].x = snake[0].x + vect.x;
        snake[0].y = snake[0].y + vect.y;
        gotoxy(snake[0].x, snake[0].y);
        std::cout<<'S';
        gotoxy(45, 24);
        std::cout<<score<<"   ";
    }
    else
        end_game = true;
}

void game_play(){
    
    while (!end_game){
        move();
        //show_game();
        if (score>high_score){ 
            high_score=score;
            save_high_score(high_score);
        }
        Sleep(200 - 30*diff);  
        if (kbhit()){
            char k = toupper(getch());
            if ((k!='A') && (k!='D') && (k!='W') && (k!='S')) continue;
            if (((k == 'A') && (direc == 'D')) || ((k == 'D') && (direc == 'A')) 
             || ((k == 'W') && (direc == 'S')) || ((k == 'S') && (direc == 'W'))) continue;
            direc = k;
        }
    }
}
