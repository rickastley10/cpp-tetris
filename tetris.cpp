#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <vector>
#include <string>

void spawnpiece(std::vector<std::vector<int>>& grid){
    grid[0][5]=2;
    grid[1][5]=2;
    grid[2][5]=25;
    grid[2][6]=2;
}

void drop(std::vector<std::vector<int>>& grid){
    for(int y=19; y>0; y--){
        for(int x=0; x<10; x++){
            if(grid[y][x]==1 && y!=19 && grid[y+1][x]==0){
                grid[y][x]=0;
                grid[y+1][x]=1;
            }
        }
    }
}

void render(std::vector<std::vector<int>> grid){
    for(int y=0; y<20; y++){
        for(int x=0; x<10; x++){
            if(grid[y][x]!=0){
                mvaddch(y, x*2, ACS_CKBOARD);
                mvaddch(y, x*2-1, ACS_CKBOARD);
            }
        }
    }

    for(int y=0; y<20;y++){
        mvaddch(y, 20, ACS_VLINE);
    }
    for(int x=0; x<20;x++){
        mvaddch(20, x, ACS_HLINE);
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

    int done=0;
    
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
        done=0;
        if(ch==KEY_RIGHT){
            for(int y=0; y<20; y++){
                for(int x=0; x<10; x++){
                    if(done==1){break;}
                    if(grid[y][x]==25 && x < 8 && (grid[y][x+2]!=1 && grid[y-1][x+1]!=1 && grid[y-2][x+1]!=1)){
                        //CLEAR L SHAPE
                        grid[y-2][x]=0;
                        grid[y-1][x]=0;
                        grid[y][x]=0;
                        grid[y][x+1]=0;

                        //DRAW L SHAPE
                        grid[y-2][x+1]=2;
                        grid[y-1][x+1]=2;
                        grid[y][x+1]=25; //CETRE
                        grid[y][x+2]=2;
                        done=1;
                        break;
                    }if(done==1){break;}
                }if(done==1){break;}
            }
        }
        done=0;
        if(ch==KEY_LEFT){
            for(int y=0; y<20; y++){
                for(int x=0; x<10; x++){
                    if(done==1){break;}
                    if(grid[y][x]==25 && x > 0 && (grid[y][x-1]!=1 && grid[y-1][x-1]!=1 && grid[y-2][x-1]!=1)){
                        //CLEAR L SHAPE
                        grid[y-2][x]=0;
                        grid[y-1][x]=0;
                        grid[y][x]=0;
                        grid[y][x+1]=0;

                        //DRAW L SHAPE
                        grid[y-2][x-1]=2;
                        grid[y-1][x-1]=2;
                        grid[y][x-1]=25; //CETRE
                        grid[y][x]=2;
                        done=1;
                        break;
                    }if(done==1){break;}
                }if(done==1){break;}
            }
        }

        //   ROTATE
        done=0;
        if(ch==KEY_UP){
            for(int y=0; y<20; y++){
                for(int x=0; x<10; x++){
                    if(done==1){break;}
                    if(grid[y][x]==25){
                        //CLEAR L SHAPE
                        grid[y-2][x]=0;
                        grid[y-1][x]=0;
                        grid[y][x]=0;
                        grid[y][x+1]=0;


                        // DRAW L2 SHAPE
                        grid[y][x]=22;
                        grid[y-1][x]=2;
                        grid[y-1][x+1]=2;
                        grid[y-1][x+2]=2;

                        done=1;
                        break;
                    }
                    else if(grid[y][x]==22){
                        // CLEAR L2 SHAPE
                        grid[y][x]=0;
                        grid[y-1][x]=0;
                        grid[y-1][x+1]=0;
                        grid[y-1][x+2]=0;


                        // DRAW L3 SHAPE
                        grid[y][x]=23;
                        grid[y][x+1]=2;
                        grid[y+1][x+1]=2;
                        grid[y+2][x+1]=2;

                        done=1;
                        break;
                    }
                    else if(grid[y][x]==23){
                        // CLEAR L3 SHAPE
                        grid[y][x]=0;
                        grid[y][x+1]=0;
                        grid[y+1][x+1]=0;
                        grid[y+2][x+1]=0;


                        // DRAW L4 SHAPE
                        grid[y][x]=24;
                        grid[y+1][x]=2;
                        grid[y+1][x-1]=2;
                        grid[y+1][x-2]=2;

                        done=1;
                        break;
                    }
                    else if(grid[y][x]==24){
                        // CLEAR L4 SHAPE
                        grid[y][x]=0;
                        grid[y+1][x]=0;
                        grid[y+1][x-1]=0;
                        grid[y+1][x-2]=0;


                        // DRAW L SHAPE
                        grid[y-2][x]=25;
                        grid[y-1][x]=2;
                        grid[y][x]=2;
                        grid[y][x+1]=2;

                        done=1;
                        break;
                    }

                }if(done==1){break;}
            }
        }


        // MOVE DOWN
        done=0;
        for(int y=0; y<20; y++){
            for(int x=0; x<10; x++){
                // L shape
                if(grid[y][x]==25){
                    if(y<19 && grid[y+1][x]!=1 && grid[y+1][x+1]!=1){
                        //CLEAR L SHAPE
                        grid[y-2][x]=0;
                        grid[y-1][x]=0;
                        grid[y][x]=0;
                        grid[y][x+1]=0;

                        //DRAW L
                        grid[y-1][x]=2;
                        grid[y][x]=2;
                        grid[y+1][x]=25; //CETRE
                        grid[y+1][x+1]=2;
                        done=1;
                        break;
                    }
                    else{
                        grid[y-2][x]=1;
                        grid[y-1][x]=1;
                        grid[y][x]=1;
                        grid[y][x+1]=1;
                        spawnpiece(grid);
                        done=1;
                        break;
                    }

                }
                else if(grid[y][x]==22){
                    if(y<19 && grid[y+1][x]!=1 && grid[y][x+1]!=1 && grid[y][x+2]!=1){

                        // CLEAR L2
                        grid[y][x]=0;
                        grid[y-1][x]=0;
                        grid[y-1][x+1]=0;
                        grid[y-1][x+2]=0;

                        grid[y+1][x]=22;
                        grid[y][x]=2;
                        grid[y][x+1]=2;
                        grid[y][x+2]=2;

                        
                        done=1;
                        break;

                    }

                    else{
                        grid[y][x]=1;
                        grid[y-1][x]=1;
                        grid[y-1][x+1]=1;
                        grid[y-1][x+2]=1;
                        spawnpiece(grid);
                        done=1;
                        break;
                    }
                }
                if(done==1){break;}
            }
            if(done==1){break;}
        }
        done=0;
        for(int y=0; y<20; y++){
            if(done==1){break;}
            if(grid[y][0] == 1 && grid[y][1] == 1 && grid[y][2] == 1 && grid[y][3] == 1 && grid[y][4] == 1 && grid[y][5] == 1 && grid[y][6] == 1 && grid[y][7] == 1 && grid[y][8] == 1 && grid[y][9] == 1){
                grid.erase(grid.begin() + y);
                grid.insert(grid.begin(), std::vector<int>(10, 0));
                done=1;
                drop(grid);
                break;
            }
            
        }
        


        render(grid);

        napms(200);
    }
    

    getch();
    endwin();
    return 0;
}
