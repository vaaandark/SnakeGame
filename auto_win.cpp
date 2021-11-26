#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

bool Map[151][151];
int NextX[151][151],NextY[151][151];
int Direction;
int Length=1;
int DX[4]={0,1,-1,0},DY[4]={1,0,0,-1};//RIGHT,DOWN,UP,LEFT
int Pre[8][4]={2,3,0,1,2,3,0,1,2,0,3,1,3,2,1,0,0,1,2,3,1,3,0,2,1,0,3,2,1,0,3,2};//UP->DOWN,LEFT->RIGHT
int HeadX=20,HeadY=20;
int TailX=20,TailY=20;
int TargetX,TargetY;

void Update()
{
    do
    {
        srand(time(NULL));
        TargetX=rand()%40+1;
        TargetY=rand()%40+1;
    } while (Map[TargetX][TargetY]==1);
    Map[TargetX][TargetY]=1;
    NextX[TargetX][TargetY]=0;
    return;
}

void Turn()
{
    int Now=Direction,State;
    if(TargetX<HeadX&&TargetY<HeadY)State=0;
    if(TargetX<HeadX&&TargetY==HeadY)State=1;
    if(TargetX<HeadX&&TargetY>HeadY)State=2;
    if(TargetX==HeadX&&TargetY<HeadY)State=3;
    if(TargetX==HeadX&&TargetY>HeadY)State=4;
    if(TargetX>HeadX&&TargetY<HeadY)State=5;
    if(TargetX>HeadX&&TargetY==HeadY)State=6;
    if(TargetX>HeadX&&TargetY>HeadY)State=7;
    int i=-1;
    do
    {
        i++;
        Direction=Pre[State][i];
    } while (i<3&&(Now+Direction==3||(Map[HeadX+DX[Direction]][HeadY+DY[Direction]]==1&&NextX[HeadX+DX[Direction]][HeadY+DY[Direction]]!=0&&(HeadX+DX[Direction]!=TailX||HeadY+DY[Direction]!=TailY))));
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
            system("clear");
            printf("Game Over!\n");
            printf("Length:%d\n",Length);
            system("pause");
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
    system("clear");
    for(int i=0;i<=41;i++)
    {
        for(int j=0;j<=41;j++)
            Map[i][j]==1?printf(" *"):printf("  ");
        printf("\n");
    }
    printf(" Length:%d\n",Length);
    printf(" Auto Mode By Honeta\n");
    return;
}

int main()
{
    for(int i=0;i<=41;i+=41)
        for(int j=0;j<=41;j++)
            Map[i][j]=NextX[i][j]=1;
    for(int i=0;i<=41;i+=41)
        for(int j=0;j<=41;j++)
            Map[j][i]=NextX[j][i]=1;
    Map[20][20]=1;
    Update();
    Print();
    Turn();
    while(1)
    {
        Turn();
        Move();
        Print();
        usleep(100000);
        system("clear");
    }
    return 0;
}
