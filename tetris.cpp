#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <vector>
#include <string>



void clear_piece(std::vector<std::vector<int>>& grid, int piece[8], int x, int y, int res){
    for(int i = 0; i < 8; i += 2){
        int Y = y + piece[i];
        int X = x + piece[i+1];
        if(Y >= 0 && Y < 20 && X >= 0 && X < 10)
            grid[Y][X] = res;
    }
}


void move_piece(std::vector<std::vector<int>>& grid, int piece[8], int x, int y, int mx, int my, int shape){
    for (int i=0; i<8; i+=2){
        int Y = y + piece[i] + my;
        int X = x + piece[i+1] + mx;
        if(Y >= 0 && Y < 20 && X >= 0 && X < 10){
            if(piece[i] == 0 && piece[i+1] == 0){
                grid[Y][X] = shape;
            }
            else{
                grid[Y][X] = 2;
            }
        }

    }
}

void spawnpiece(std::vector<std::vector<int>>& grid, int piece[8], int& shape){
    // SHAPES
    int Lshape[8]={-2,0,  -1,0,  0,0,  0,1};//      3
    int Jshape[8]={-2,0,  -1,0,  0,0,  0,-1};//     4
    int Sshape[8]={-1,0,  -1,1,  0,0,  0,-1};//     5
    int Oshape[8]={1,0,  1,1,  0,0,  0,1};//        6
    int Zshape[8]={-1,0, -1,-1, 0,0, 0,1};//     7
    int Ishape[8]={2,0,  1,0,  0,0,  3,0};//        8
    int Tshape[8]={0,-1,  0,1,  0,0,  -1,0};//      9


    shape = (rand() % 7)+3;
    grid[2][5]=shape;
    if(grid[2][5]==3){
        for(int i=0;i<8;i++){
            piece[i]=Lshape[i];
        }
    }
    else if(grid[2][5]==4){
        for(int i=0;i<8;i++){
            piece[i]=Jshape[i];
        }
    }
    else if(grid[2][5]==5){
        for(int i=0;i<8;i++){
            piece[i]=Sshape[i];
        }
    }
    else if(grid[2][5]==6){
        for(int i=0;i<8;i++){
            piece[i]=Oshape[i];
        }
    }
    else if(grid[2][5]==7){
        for(int i=0;i<8;i++){
            piece[i]=Zshape[i];
        }
    }
    else if(grid[2][5]==8){
        for(int i=0;i<8;i++){
            piece[i]=Ishape[i];
        }
    }
    else if(grid[2][5]==9){
        for(int i=0;i<8;i++){
            piece[i]=Tshape[i];
        }
    }
    

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

void render(std::vector<std::vector<int>> grid, int score, int level){
    for(int y=0; y<20; y++){
        for(int x=0; x<10; x++){
            if(grid[y][x]!=0){
                mvaddch(y, x*2, ACS_CKBOARD);
                mvaddch(y, x*2+1, ACS_CKBOARD);
            }
        }
    }

    for(int y=0; y<20;y++){
        mvaddch(y, 20, ACS_VLINE);
    }
    for(int x=0; x<20;x++){
        mvaddch(20, x, ACS_HLINE);
    }
    int x=level*4000 + score;
    mvprintw(21, 6, "score: %d", x);

    refresh();
}

int colision(std::vector<std::vector<int>>& grid, int piece[8],
             int x, int y, int mx, int my, int shape)
{
    for(int i = 0; i < 8; i += 2){
        int Y = y + piece[i]   + my;
        int X = x + piece[i+1] + mx;
        if(Y < 0 || Y >= 20 || X < 0 || X >= 10) return 1;  // off board = blocked
        if(grid[Y][X] == 1) return 1;
    }
    return 0;   // ← MUST return 0; this is the ud2 fix
}

void game_over(std::vector<std::vector<int>>& grid, int piece[8], int& shape, int& flip_type, int& score, int& level){
    int Lshape[8]={-2,0,  -1,0,  0,0,  0,1};//      3

    for(int i=-3;i<10;i++){
        clear();
        mvprintw(i, 4,   "      GAME OVER       ");
        mvprintw(i+1, 4, "----------------------");
        mvprintw(i+2, 4, "press any key to start");

        refresh();
        napms(50);
    }
    shape=3;
    for(int y=0; y<20; y++){
        for(int x=0; x<10; x++){
            grid[y][x]=0;
        }
    }
    for(int i=0;i<8;i++)piece[i]=Lshape[i];
    flip_type=1;
    score=0;
    level=0;
    spawnpiece(grid, piece, shape);
    

    nodelay(stdscr, FALSE);
    getch();
    nodelay(stdscr, TRUE);
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

    int piece[8]={-2,0,  -1,0,  0,0,  0,1};
    int flip_piece[8]={-2,0,  -1,0,  0,0,  0,1};
    int flip_type=1;

    int shape=3;

    // SHAPES
    int Lshape[8]={-2,0,  -1,0,  0,0,  0,1};//      3
    int Jshape[8]={-2,0,  -1,0,  0,0,  0,-1};//     4
    int Sshape[8]={-1,0,  -1,1,  0,0,  0,-1};//     5
    int Oshape[8]={1,0,  1,1,  0,0,  0,1};//        6
    int Zshape[8]={-1,0, -1,-1, 0,0, 0,1};//     7
    int Ishape[8]={2,0,  1,0,  0,0,  3,0};//        8
    int Tshape[8]={0,-1,  0,1,  0,0,  -1,0};//      9

    int score=0;
    int level=0;

    int done=0;


    int X=0;int Y=0;
    
    std::vector<std::vector<int>> grid = {
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0},
    {0,0,0,0,3,2,0,0,0,0},
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
                    if(grid[y][x]==shape){

                        if(colision(grid, piece, x, y, 1, 0, shape)==0){
                            clear_piece(grid, piece, x, y, 0);
                            move_piece(grid, piece, x, y, 1, 0, shape);
                        }
                        
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
                    if(grid[y][x]==shape){
                        
                        if(colision(grid, piece, x, y, -1, 0, shape)==0){
                            clear_piece(grid, piece, x, y, 0);
                            move_piece(grid, piece, x, y, -1, 0, shape);
                        }
                        done=1;
                        break;
                    }if(done==1){break;}
                }if(done==1){break;}
            }
        }

        //   ROTATE
        done=0;
        if(ch == KEY_UP){

            done = 0;
            for(int y = 0; y < 20; y++){
                for(int x = 0; x < 10; x++){
                    if(done == 1){ break; }
                    if(grid[y][x] == shape){

                        int old_piece[8];
                        for(int i = 0; i < 8; i++) old_piece[i] = piece[i];


                        if(flip_type == 1){
                            flip_piece[0] = piece[1];
                            flip_piece[1] = -piece[0];
                            flip_piece[2] = piece[3];
                            flip_piece[3] = -piece[2];
                            flip_piece[4] = piece[5];
                            flip_piece[5] = -piece[4];
                            flip_piece[6] = piece[7];
                            flip_piece[7] = -piece[6];
                            for(int i = 0; i < 8; i++) piece[i] = flip_piece[i];
                            flip_type++;
                        }
                        else if(flip_type == 2){
                            if(shape == 3) for(int i = 0; i < 8; i++) piece[i] = Lshape[i];
                            if(shape == 4) for(int i = 0; i < 8; i++) piece[i] = Jshape[i];
                            if(shape == 5) for(int i = 0; i < 8; i++) piece[i] = Sshape[i];
                            if(shape == 6) for(int i = 0; i < 8; i++) piece[i] = Oshape[i];
                            if(shape == 7) for(int i = 0; i < 8; i++) piece[i] = Zshape[i];
                            if(shape == 8) for(int i = 0; i < 8; i++) piece[i] = Ishape[i];
                            if(shape == 9) for(int i = 0; i < 8; i++) piece[i] = Tshape[i];

                            
                            flip_piece[0] = piece[0] * (-1);
                            flip_piece[1] = piece[1] * (-1);
                            flip_piece[2] = piece[2] * (-1);
                            flip_piece[3] = piece[3] * (-1);
                            flip_piece[4] = piece[4] * (-1);
                            flip_piece[5] = piece[5] * (-1);
                            flip_piece[6] = piece[6] * (-1);
                            flip_piece[7] = piece[7] * (-1);
                            for(int i = 0; i < 8; i++) piece[i] = flip_piece[i];
                            flip_type++;
                        }
                        else if(flip_type == 3){
                            if(shape == 3) for(int i = 0; i < 8; i++) piece[i] = Lshape[i];
                            if(shape == 4) for(int i = 0; i < 8; i++) piece[i] = Jshape[i];
                            if(shape == 5) for(int i = 0; i < 8; i++) piece[i] = Sshape[i];
                            if(shape == 6) for(int i = 0; i < 8; i++) piece[i] = Oshape[i];
                            if(shape == 7) for(int i = 0; i < 8; i++) piece[i] = Zshape[i];
                            if(shape == 8) for(int i = 0; i < 8; i++) piece[i] = Ishape[i];
                            if(shape == 9) for(int i = 0; i < 8; i++) piece[i] = Tshape[i];


                            flip_piece[0] = piece[1];  flip_piece[1] = -piece[0];
                            flip_piece[2] = piece[3];  flip_piece[3] = -piece[2];
                            flip_piece[4] = piece[5];  flip_piece[5] = -piece[4];
                            flip_piece[6] = piece[7];  flip_piece[7] = -piece[6];
                            for(int i = 0; i < 8; i++) piece[i] = flip_piece[i];
                            flip_piece[0] = piece[0] * (-1);
                            flip_piece[1] = piece[1] * (-1);
                            flip_piece[2] = piece[2] * (-1);
                            flip_piece[3] = piece[3] * (-1);
                            flip_piece[4] = piece[4] * (-1);
                            flip_piece[5] = piece[5] * (-1);
                            flip_piece[6] = piece[6] * (-1);
                            flip_piece[7] = piece[7] * (-1);
                            for(int i = 0; i < 8; i++) piece[i] = flip_piece[i];
                            flip_type++;
                        }
                        else{
                            if(shape == 3) for(int i = 0; i < 8; i++) piece[i] = Lshape[i];
                            if(shape == 4) for(int i = 0; i < 8; i++) piece[i] = Jshape[i];
                            if(shape == 5) for(int i = 0; i < 8; i++) piece[i] = Sshape[i];
                            if(shape == 6) for(int i = 0; i < 8; i++) piece[i] = Oshape[i];
                            if(shape == 7) for(int i = 0; i < 8; i++) piece[i] = Zshape[i];
                            if(shape == 8) for(int i = 0; i < 8; i++) piece[i] = Ishape[i];
                            if(shape == 9) for(int i = 0; i < 8; i++) piece[i] = Tshape[i];
                            flip_type = 1;
                        }


                        clear_piece(grid, old_piece, x, y, 0);
                        move_piece(grid, piece, x, y, 0, 0, shape);

                        done = 1;
                        break;
                    }
                    if(done == 1){ break; }
                }
                if(done == 1){ break; }
            }
        }


        // MOVE DOWN
        done=0;
        for(int y=0; y<20; y++){
            for(int x=0; x<10; x++){
                // L shape
                if(grid[y][x]==shape){
                    if(colision(grid, piece, x, y, 0, 1, shape)==0){
                        clear_piece(grid, piece, x, y, 0);
                        move_piece(grid, piece, x, y, 0, 1, shape);
                        done=1;
                        break;
                    }
                    else{
                        clear_piece(grid, piece, x, y, 1);
                        spawnpiece(grid, piece, shape);
                        done=1;
                        break;
                    }

                }
                if(done==1){break;}
            }
            if(done==1){break;}
        }


        if(grid[2][5]==1 || grid[3][5]==1){
            game_over(grid, piece, shape, flip_type, score, level);
        }

        // CLEAR LINE
        done=0;
        for(int y=0; y<20; y++){
            if(done==1){break;}
            if(grid[y][0] == 1 && grid[y][1] == 1 && grid[y][2] == 1 && grid[y][3] == 1 && grid[y][4] == 1 && grid[y][5] == 1 && grid[y][6] == 1 && grid[y][7] == 1 && grid[y][8] == 1 && grid[y][9] == 1){
                grid.erase(grid.begin() + y);
                grid.insert(grid.begin(), std::vector<int>(10, 0));
                done=1;
                score+=100;
                drop(grid);
                break;
            }
        
            
        }
        
        if(score>4000){
            level++;
            score=0;
        }
        

        render(grid, score, level);


        napms(std::max(10, 200-(level*2)));
    }
    

    getch();
    endwin();
    return 0;
}
