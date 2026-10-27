#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <vector>
#include <string>

void spawnpiece(std::vector<std::vector<int>> grid){
    grid[0][5]=2;
    grid[1][5]=2;
    grid[2][5]=25;
    grid[2][6]=2;
}

void render(std::vector<std::vector<int>> grid){
    for(int y=0; y<20; y++){
            for(int x=0; x<10; x++){
                if(grid[y][x]!=0){
                    mvaddch(y, x, ACS_CKBOARD);
                }
            }
        }

        refresh();
}


int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);


    int ch;

    srand(time(NULL));
    int random = (rand() % 3) + 1;

    
    std::vector<std::vector<int>> grid = {
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,25,2,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    };
    while (1==1)
    {
        clear();
        ch = getch();
        if(ch==27){//escape
            break;
        }

        for(int y=0; y<20; y++){
            for(int x=0; x<10; x++){
                if(grid[y][x]==25){
                    if(y<19){
                        //CLEAR L SHAPE
                        grid[y-2][x]=0;
                        grid[y-1][x]=0;
                        grid[y][x]=0;
                        grid[y][x+1]=0;

                        //DRAW WITH THE CENTRE
                        grid[y-1][x]=2;
                        grid[y][x]=2;
                        grid[y+1][x]=25; //CETRE
                        grid[y+1][x+1]=2;
                        break;
                    }
                    else if(y==19){
                        grid[y-2][x]=1;
                        grid[y-1][x]=1;
                        grid[y][x]=1;
                        grid[y][x+1]=1;
                        spawnpiece(grid);
                        break;
                    }
                }
            }
        }


        render(grid);

        napms(1000);
    }
    

    getch();
    endwin();
    return 0;
}
