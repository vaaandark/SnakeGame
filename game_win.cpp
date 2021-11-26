#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>

#define LEFT 119
#define RIGHT 115
#define UP 97
#define DOWN 100
#define ESC 27

using namespace std;

bool Map[151][151];
int NextX[151][151],NextY[151][151];
int Direction=0;
int Length=1;
int DX[4]={0,1,-1,0},DY[4]={1,0,0,-1};
int HeadX=10,HeadY=10;
int TailX=10,TailY=10;
int TargetX,TargetY;

void Update()
{
    do
    {
        srand(time(NULL));
        TargetX=rand()%20+1;
        TargetY=rand()%20+1;
    } while (Map[TargetX][TargetY]==1);
    Map[TargetX][TargetY]=1;
    NextX[TargetX][TargetY]=0;
    return;
}

void Turn(char Key)
{
    //int Key=getch();
    int Now=Direction;
    if(Key==LEFT)Direction=2;
    if(Key==RIGHT)Direction=1;
    if(Key==UP)Direction=3;
    if(Key==DOWN)Direction=0;
    if(Key==ESC)
    {
		clear();
        printw("Exit?\n");
        Key=getch();
		if(Key==ESC) {
				endwin();
				exit(0);
		}
    }
    if(Direction+Now==3)Direction=Now;
    return;
}

void Move()
{
    if(Map[HeadX+DX[Direction]][HeadY+DY[Direction]]==1)
    {
        if(NextX[HeadX+DX[Direction]][HeadY+DY[Direction]]!=0)
        {
            if(HeadX+DX[Direction]==TailX&&HeadY+DY[Direction]==TailY)
            {
                NextX[HeadX][HeadY]=HeadX+DX[Direction];
                NextY[HeadX][HeadY]=HeadY+DY[Direction];
                HeadX+=DX[Direction];
                HeadY+=DY[Direction];
                TailX=NextX[HeadX][HeadY];
                TailY=NextY[HeadX][HeadY];
                return;
            }
			clear();
            printw("Game Over!\n");
			timeout(-1);
			getch();
			endwin();
            exit(0);
        }
        Update();
        NextX[HeadX][HeadY]=HeadX+DX[Direction];
        NextY[HeadX][HeadY]=HeadY+DY[Direction];
        HeadX+=DX[Direction];
        HeadY+=DY[Direction];
        Length++;
        return;
    }
    NextX[HeadX][HeadY]=HeadX+DX[Direction];
    NextY[HeadX][HeadY]=HeadY+DY[Direction];
    HeadX+=DX[Direction];
    HeadY+=DY[Direction];
    Map[HeadX][HeadY]=1;
    Map[TailX][TailY]=0;
    int TX=TailX,TY=TailY;
    TailX=NextX[TX][TY];
    TailY=NextY[TX][TY];
    NextX[TX][TY]=NextY[TX][TY]=0;
    return;
}

void Print()
{
	clear();
    for(int i=0;i<=21;i++)
    {
        for(int j=0;j<=21;j++)
            Map[i][j]==1?printw(" *"):printw("  ");
        printw("\n");
    }
    printw(" Length:%d\n",Length);
    printw(" Game Mode By HUST_hxj\n");
    return;
}

int main()
{
	initscr();
	curs_set(0);
	timeout(200);
    for(int i=0;i<=21;i+=21)
        for(int j=0;j<=21;j++)
            Map[i][j]=NextX[i][j]=1;
    for(int i=0;i<=21;i+=21)
        for(int j=0;j<=21;j++)
            Map[j][i]=NextX[j][i]=1;
    Map[10][10]=1;
    Update();
    Print();
    while(1)
    {
		char Key;
       	if(Key = getch())Turn(Key);
        Move();
        Print();
    }
    return 0;
}
