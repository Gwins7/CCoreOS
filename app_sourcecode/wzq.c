#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <Windows.h>
#include <time.h>
#define SIZE 15
#define CHARSIZE 1

void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void GetPic(void);
void ifsix(void);
void ifforbidden(void);
void ifwin(void);
void randdown(void);
void pvedown1(void);
void displayBoardScore(void);

void clear_screen(void){
    printf("\033c");
}

char x=0;
int y=0;
int z=0;
int status=1;
int bow=0,pv=0;
int forbidtag=0,forbidden=0;
int nowx=0,nowy=0;
//空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"|-------------|",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
        "|             |",
		"|             |",
		"|-------------|"
};
//此数组存储用于显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];

char play1Pic='o';//黑棋子;
char play1CurrentPic='~'; 

char play2Pic='x';//白棋子;
char play2CurrentPic='+';

//此数组用于记录当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()
{
    initRecordBorard();    //初始化一个空棋盘
    innerLayoutToDisplayArray();  //将心中的棋盘转成用于显示的棋盘
    printf("wzq Author:Gwins7\n");
    // printf("pvp(1) or pve(2) or eve(3)?\n");
    // scanf("%d",&pv);
    // if(pv==2){
    //     printf("computer Black(1) or White(2)?\n");
    //     scanf("%d",&bow);
    // }
    pv = 3;
    displayBoard(); 
    while(1){
    GetPic();
    innerLayoutToDisplayArray();
    forbidtag=0;
    ifsix();
    ifwin();
    ifforbidden();
    displayBoard();          //显示棋盘
    }
    return 0;
}

//初始化一个空棋盘格局  
void initRecordBorard(void){
	//通过双重循环，将arrayForInnerBoardLayout清0
      int i,j;
      for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            arrayForInnerBoardLayout[i][j]=0;
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
    //第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    int i,j;
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE*CHARSIZE+1;j++)
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
	//第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将棋子复制到arrayForDisplayBoard的相应位置上
    //1黑2白
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i][j]!=0) {
                if (arrayForInnerBoardLayout[i][j]==1) {
                    arrayForDisplayBoard[i][j*CHARSIZE]=play1Pic;
                }
                if (arrayForInnerBoardLayout[i][j]==2) {
                    arrayForDisplayBoard[i][j*CHARSIZE]=play2Pic;
                }
            }  
        }
    if (status==2) {
        arrayForDisplayBoard[SIZE-y][(x)*CHARSIZE]=play1CurrentPic;
        nowx=x;nowy=y;
    }
    if (status==1) {
        arrayForDisplayBoard[SIZE-y][(x)*CHARSIZE]=play2CurrentPic;
        nowx=x;nowy=y;
    }
}
//显示棋盘格局 
void displayBoard(void){
	int i;
	//第一步：清屏
	//system("clear");   //清屏
	clear_screen();
    printf("wzq Author:Gwins7\n");
	//第二步：将arrayForDisplayBoard输出到屏幕上
        for (i=0;i<SIZE;i++) printf("%2d%s\n",SIZE-i,arrayForDisplayBoard[i]);
	//第三步：输出最下面的一行字母A B .... 
        printf("  ");
        for (i=0;i<SIZE;i++) printf("%c",('A'+i));
        printf("\n");
        if (nowx!=0 && nowy!=0) printf("Lastdown:%c%d\n",nowx+'a',nowy);
} 

void GetPic(void){
    if (pv==2 && status==bow){
        pvedown1();
        return;
    }
    if (pv==3){
        bow=status;
        pvedown1();
        return;
    }

    char s[5];
    static char tempx;
    static int tempy;
    tempx=x;tempy=y;
    printf("example input:h12\n");
    if (status==1) printf("now:Black\ninput:");
    if (status==2) printf("now:White\ninput:");
    scanf("%s",s);
    if (s[0]=='q' && s[1]=='u' && s[2]=='i' && s[3]=='t') exit(0);
    x=s[0];
    if (strlen(s)==3) y=(s[1]-'0')*10+s[2]-'0';
    else if(strlen(s)==2) y=s[1]-'0'; 
    else {printf("input error\n");sleep(1);y=tempy;x=tempx;return;}
    
    if (x>='a' && x<='o') x=x-'a'+'A';
    if (x>='A' && x<='O' && y>0 && y<16){
        x=x-'A';
        if (arrayForInnerBoardLayout[SIZE-y][x]!=0) {
            y=tempy;
            x=tempx;
            printf("already down\n");
            sleep(1);
            return;
        }
        else if (status==1) {arrayForInnerBoardLayout[SIZE-y][x]=1;status=2;return;}
        else if (status==2) {arrayForInnerBoardLayout[SIZE-y][x]=2;status=1;return;}
    }
    else {printf("input overflowed\n");sleep(1);y=tempy;x=tempx;return;}
}
void ifsix(void){
    static int status1=0;
    int i,j;
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE-5;j++)
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1 && arrayForInnerBoardLayout[i][j+4]==1 && arrayForInnerBoardLayout[i][j+5]==1) status1=1;
    for (i=0;i<SIZE-5;i++)
        for (j=0;j<SIZE;j++)
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1 && arrayForInnerBoardLayout[i+4][j]==1 && arrayForInnerBoardLayout[i+5][j]==1) status1=1;
    for (i=0;i<SIZE-5;i++)
        for (j=0;j<SIZE-5;j++)
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1 && arrayForInnerBoardLayout[i+4][j+4]==1 && arrayForInnerBoardLayout[i+5][j+5]==1) status1=1;
    for (i=0;i<SIZE-5;i++)
        for (j=5;j<SIZE;j++)
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1 && arrayForInnerBoardLayout[i+4][j-4]==1 && arrayForInnerBoardLayout[i+5][j-5]==1) status1=1;
    
    if (status1==1 && forbidtag==0){
        displayBoard();
        printf("Forbidden! White win.(1)\n");
        exit(0);
    }
    else if (status1==1 && forbidtag==1) {
        status1=0;forbidden=1;return;
    }
}

void ifforbidden(void){
    static int huosan1=0,huosan2=0,si1=0,si2=0;
    huosan2=huosan1;si2=si1;
    huosan1=0;si1=0;
    int i,j;
    for (i=0;i<SIZE;i++)
        for (j=1;j<SIZE-3;j++){
            if (arrayForInnerBoardLayout[i][j-1]==1 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1) 
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+3==SIZE-1 || arrayForInnerBoardLayout[i][j+4]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i][j-1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==0 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1) 
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+3==SIZE-1 || arrayForInnerBoardLayout[i][j+4]!=1))
                    si1++;            
            if (arrayForInnerBoardLayout[i][j-1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==0 && arrayForInnerBoardLayout[i][j+3]==1)
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+3==SIZE-1 || arrayForInnerBoardLayout[i][j+4]!=1))
                    si1++;
        
        }
    for (i=1;i<SIZE-3;i++)
        for (j=0;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i-1][j]==1 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==0 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==0 && arrayForInnerBoardLayout[i+3][j]==1) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j]!=1))
                    si1++;
        }
    for (i=1;i<SIZE-3;i++)
        for (j=1;j<SIZE-3;j++){
            if (arrayForInnerBoardLayout[i-1][j-1]==1 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1) 
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+3==SIZE-1 || j+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j+4]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j-1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==0 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1) 
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+3==SIZE-1 || j+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j+4]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j-1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==0 && arrayForInnerBoardLayout[i+3][j+3]==1) 
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+3==SIZE-1 || j+3==SIZE-1 || arrayForInnerBoardLayout[i+4][j+4]!=1))
                    si1++;
        }
    for (i=1;i<SIZE-3;i++)
        for (j=3;j<SIZE-1;j++){
            if (arrayForInnerBoardLayout[i-1][j+1]==1 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+3==SIZE-1 || j-3==0 || arrayForInnerBoardLayout[i+4][j-4]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j+1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==0 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+3==SIZE-1 || j-3==0 || arrayForInnerBoardLayout[i+4][j-4]!=1))
                    si1++;
            if (arrayForInnerBoardLayout[i-1][j+1]==1 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==0 && arrayForInnerBoardLayout[i+3][j-3]==1) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+3==SIZE-1 || j-3==0 || arrayForInnerBoardLayout[i+4][j-4]!=1))
                    si1++;
        }

    for (i=0;i<SIZE;i++)
        for (j=1;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==0 && arrayForInnerBoardLayout[i][j+4]==0)
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+4==SIZE-1 || arrayForInnerBoardLayout[i][j+5]!=1))
                huosan1++;            
            if (arrayForInnerBoardLayout[i][j-1]==0 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1 && arrayForInnerBoardLayout[i][j+4]==0) 
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+4==SIZE-1 || arrayForInnerBoardLayout[i][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==0 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1 && arrayForInnerBoardLayout[i][j+4]==0) 
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+4==SIZE-1 || arrayForInnerBoardLayout[i][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==0 && arrayForInnerBoardLayout[i][j+3]==1 && arrayForInnerBoardLayout[i][j+4]==0) 
                if ((j-1==0 || arrayForInnerBoardLayout[i][j-2]!=1) && (j+4==SIZE-1 || arrayForInnerBoardLayout[i][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1 && (arrayForInnerBoardLayout[i][j+4]==0 || arrayForInnerBoardLayout[i][j-1]==0)) 
                si1++;
        }
    for (i=1;i<SIZE-4;i++)
        for (j=0;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i-1][j]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==0 && arrayForInnerBoardLayout[i+4][j]==0) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j]==0 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1 && arrayForInnerBoardLayout[i+4][j]==0) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==0 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1 && arrayForInnerBoardLayout[i+4][j]==0) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==0 && arrayForInnerBoardLayout[i+3][j]==1 && arrayForInnerBoardLayout[i+4][j]==0) 
                if ((i-1==0 || arrayForInnerBoardLayout[i-2][j]!=1) && (i+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1 && (arrayForInnerBoardLayout[i+4][j]==0 || arrayForInnerBoardLayout[i-1][j]==0)) 
                si1++;
        }
    for (i=1;i<SIZE-4;i++)
        for (j=1;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i-1][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==0 && arrayForInnerBoardLayout[i+4][j+4]==0)
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+4==SIZE-1 || j+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j-1]==0 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1 && arrayForInnerBoardLayout[i+4][j+4]==0)
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+4==SIZE-1 || j+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==0 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1 && arrayForInnerBoardLayout[i+4][j+4]==0) 
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+4==SIZE-1 || j+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==0 && arrayForInnerBoardLayout[i+3][j+3]==1 && arrayForInnerBoardLayout[i+4][j+4]==0) 
                if ((i-1==0 || j-1==0 || arrayForInnerBoardLayout[i-2][j-2]!=1) && (i+4==SIZE-1 || j+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j+5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1 && (arrayForInnerBoardLayout[i+4][j+4]==0 || arrayForInnerBoardLayout[i-1][j-1]==0)) 
                si1++;
        }
    for (i=1;i<SIZE-4;i++)
        for (j=4;j<SIZE-1;j++){
            if (arrayForInnerBoardLayout[i-1][j+1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==0 && arrayForInnerBoardLayout[i+4][j-4]==0) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+4==SIZE-1 || j-4==0 || arrayForInnerBoardLayout[i+5][j-5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j+1]==0 && arrayForInnerBoardLayout[i][j]==0 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1 && arrayForInnerBoardLayout[i+4][j-4]==0) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+4==SIZE-1 || j-4==0 || arrayForInnerBoardLayout[i+5][j-5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j+1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==0 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1 && arrayForInnerBoardLayout[i+4][j-4]==0) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+4==SIZE-1 || j-4==0 || arrayForInnerBoardLayout[i+5][j-5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i-1][j+1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==0 && arrayForInnerBoardLayout[i+3][j-3]==1 && arrayForInnerBoardLayout[i+4][j-4]==0) 
                if ((i-1==0 || j+1==SIZE-1 || arrayForInnerBoardLayout[i-2][j+2]!=1) && (i+4==SIZE-1 || j-4==0 || arrayForInnerBoardLayout[i+5][j-5]!=1))
                    huosan1++;
            if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1 && (arrayForInnerBoardLayout[i+4][j-4]==0 || arrayForInnerBoardLayout[i-1][j+1]==0)) 
                si1++;
        }
        
    for (i=0;i<SIZE;i++)
        for (j=2;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i][j-2]==0 && arrayForInnerBoardLayout[i][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==0 && arrayForInnerBoardLayout[i][j+4]==0) 
                if ((j-2==0 || arrayForInnerBoardLayout[i][j-3]!=1) && (j+4==SIZE-1 || arrayForInnerBoardLayout[i][j+5]!=1))
                    huosan1--;
        }
    for (i=2;i<SIZE-4;i++)
        for (j=0;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i-2][j]==0 && arrayForInnerBoardLayout[i-1][j]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==0 && arrayForInnerBoardLayout[i+4][j]==0) 
                if ((i-2==0 || arrayForInnerBoardLayout[i-3][j]!=1) && (i+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j]!=1))
                    huosan1--;
        }
    for (i=2;i<SIZE-4;i++)
        for (j=2;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i-2][j-2]==0 && arrayForInnerBoardLayout[i-1][j-1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==0 && arrayForInnerBoardLayout[i+4][j+4]==0) 
                if ((i-2==0 || j-2==0 || arrayForInnerBoardLayout[i-3][j-3]!=1) && (i+4==SIZE-1 || j+4==SIZE-1 || arrayForInnerBoardLayout[i+5][j+5]!=1))
                    huosan1--;
        }
    for (i=2;i<SIZE-4;i++)
        for (j=4;j<SIZE-2;j++){
            if (arrayForInnerBoardLayout[i-2][j+2]==0 && arrayForInnerBoardLayout[i-1][j+1]==0 && arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==0 && arrayForInnerBoardLayout[i+4][j-4]==0) 
                if ((i-2==0 || j+2==SIZE-1 || arrayForInnerBoardLayout[i-3][j+3]!=1) && (i+4==SIZE-1 || j-4==0 || arrayForInnerBoardLayout[i+5][j-5]!=1))
                    huosan1--;
        }

    if ((huosan1-huosan2>=2 || si1-si2>=2) && forbidtag==0) {
        displayBoard();
        printf("Forbidden! White win.(2)\n");
        exit(0);
    }
    else if ((huosan1-huosan2>=2 || si1-si2>=2) && forbidtag==1) {
        huosan1=huosan2;si1=si2;
        forbidden=1;return;
    }
}

void ifwin(void){
    static int down=0;
    static int winstatus=0;
    int i,j;
    down=down+1;
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i][j]==2 && arrayForInnerBoardLayout[i][j+1]==2 && arrayForInnerBoardLayout[i][j+2]==2 && arrayForInnerBoardLayout[i][j+3]==2 && arrayForInnerBoardLayout[i][j+4]==2) winstatus=2;
            else if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i][j+1]==1 && arrayForInnerBoardLayout[i][j+2]==1 && arrayForInnerBoardLayout[i][j+3]==1 && arrayForInnerBoardLayout[i][j+4]==1) winstatus=1;
        }
    for (i=0;i<SIZE-4;i++)
        for (j=0;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i][j]==2 && arrayForInnerBoardLayout[i+1][j]==2 && arrayForInnerBoardLayout[i+2][j]==2 && arrayForInnerBoardLayout[i+3][j]==2 && arrayForInnerBoardLayout[i+4][j]==2) winstatus=2;
            else if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j]==1 && arrayForInnerBoardLayout[i+2][j]==1 && arrayForInnerBoardLayout[i+3][j]==1 && arrayForInnerBoardLayout[i+4][j]==1) winstatus=1;
        }
    for (i=0;i<SIZE-4;i++)
        for (j=0;j<SIZE-4;j++){
            if (arrayForInnerBoardLayout[i][j]==2 && arrayForInnerBoardLayout[i+1][j+1]==2 && arrayForInnerBoardLayout[i+2][j+2]==2 && arrayForInnerBoardLayout[i+3][j+3]==2 && arrayForInnerBoardLayout[i+4][j+4]==2) winstatus=2;
            else if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j+1]==1 && arrayForInnerBoardLayout[i+2][j+2]==1 && arrayForInnerBoardLayout[i+3][j+3]==1 && arrayForInnerBoardLayout[i+4][j+4]==1) winstatus=1;
        }
    for (i=0;i<SIZE-4;i++)
        for (j=4;j<SIZE;j++){
            if (arrayForInnerBoardLayout[i][j]==2 && arrayForInnerBoardLayout[i+1][j-1]==2 && arrayForInnerBoardLayout[i+2][j-2]==2 && arrayForInnerBoardLayout[i+3][j-3]==2 && arrayForInnerBoardLayout[i+4][j-4]==2) winstatus=2;
            else if (arrayForInnerBoardLayout[i][j]==1 && arrayForInnerBoardLayout[i+1][j-1]==1 && arrayForInnerBoardLayout[i+2][j-2]==1 && arrayForInnerBoardLayout[i+3][j-3]==1 && arrayForInnerBoardLayout[i+4][j-4]==1) winstatus=1;
        }
    if (winstatus==1){
            displayBoard();
            printf("Black win!\n");
            exit(0);
        }
    else if (winstatus==2){
            displayBoard();
            printf("White win!\n");
            exit(0);
        }
    else if (down==225){
            displayBoard();
            printf("Draw.\n");
            exit(0);
        }
}

void randdown(void){
    srand((unsigned)time(NULL));
    x=rand()%SIZE;
    y=rand()%SIZE;
    while(arrayForInnerBoardLayout[SIZE-y][x]!=0){
    x=rand()%SIZE;
    y=rand()%SIZE;
    }
    if (status==1) {arrayForInnerBoardLayout[SIZE-y][x]=1;status=2;return;}
    else if (status==2) {arrayForInnerBoardLayout[SIZE-y][x]=2;status=1;return;}
}


struct SingleInfo{
        int linknum;
        int oppnum;
        int space;
    }; 
struct SingleScore{
        struct SingleInfo info[4];
        int score;
        int live[7];
        int half[7];
        int dead[7];
        int forbidden;
    };
struct SingleScore myBoardScore[2][SIZE][SIZE];//0b1w
void pvedown1(void){//0b1w
    int a,b,i,j,k,l,m;
    int fourtag1,fourtag2;
    int r1=0,r2=0;
    for (i=0;i<SIZE;i++)
		for (j=0;j<SIZE;j++){//全部初始化
			for (k=0;k<4;k++){
                for (m=0;m<=1;m++){
				    myBoardScore[m][i][j].info[k].linknum=1;
				    myBoardScore[m][i][j].info[k].oppnum=0;
                    myBoardScore[m][i][j].info[k].space=0;
                    myBoardScore[m][i][j].score=0;
                    for (l=0;l<6;l++){
                    myBoardScore[m][i][j].live[l]=0;
                    myBoardScore[m][i][j].half[l]=0;
                    myBoardScore[m][i][j].dead[l]=0;
                    }
                }
                myBoardScore[0][i][j].forbidden=0;
            }
        }
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
        	for (k=1;k<3;k++){//统计数值
            int nk=(k==1)?2:1;
            int z;int temp1,temp2;
            a=i;b=j;z=0;
            fourtag1=fourtag2=0;
            temp1=temp2=0;
            if (a==0){
                myBoardScore[k-1][i][j].info[1].oppnum++;
                myBoardScore[k-1][i][j].info[2].oppnum++;
                myBoardScore[k-1][i][j].info[3].oppnum++;
            }
            if (b==0){
                myBoardScore[k-1][i][j].info[0].oppnum++;
                myBoardScore[k-1][i][j].info[2].oppnum++;
                myBoardScore[k-1][i][j].info[3].oppnum++;
            }
            if (a==SIZE-1){
                myBoardScore[k-1][i][j].info[1].oppnum++;
                myBoardScore[k-1][i][j].info[2].oppnum++;
                myBoardScore[k-1][i][j].info[3].oppnum++;
            }
            if (b==SIZE-1){
                myBoardScore[k-1][i][j].info[0].oppnum++;
                myBoardScore[k-1][i][j].info[2].oppnum++;
                myBoardScore[k-1][i][j].info[3].oppnum++;
            }
            while(b>0){
                b--;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || b==0 || arrayForInnerBoardLayout[a][b-1]!=k) break;myBoardScore[k-1][i][j].info[0].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[0].linknum++;temp1++;if (b==0) myBoardScore[k-1][i][j].info[0].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[0].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            a=i;b=j;z=0;temp1=temp2=0;
            while(b<SIZE-1){
                b++;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || b==SIZE-1 || arrayForInnerBoardLayout[a][b+1]!=k) break;myBoardScore[k-1][i][j].info[0].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[0].linknum++;temp1++;if (b==SIZE-1) myBoardScore[k-1][i][j].info[0].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[0].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }

            a=i;b=j;z=0;temp1=temp2=0;
            while(a>0){
                a--;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==0 || arrayForInnerBoardLayout[a-1][b]!=k) break;myBoardScore[k-1][i][j].info[1].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[1].linknum++;temp1++;if (a==0) myBoardScore[k-1][i][j].info[1].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[1].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            a=i;b=j;z=0;temp1=temp2=0;
            while(a<SIZE-1){
                a++;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==SIZE-1 || arrayForInnerBoardLayout[a+1][b]!=k) break;myBoardScore[k-1][i][j].info[1].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[1].linknum++;temp1++;if (a==SIZE-1) myBoardScore[k-1][i][j].info[1].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[1].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }

            a=i;b=j;z=0;temp1=temp2=0;
            while (a>0 && b>0){
                a--;b--;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==0 || b==0 || arrayForInnerBoardLayout[a-1][b-1]!=k) break;myBoardScore[k-1][i][j].info[2].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[2].linknum++;temp1++;if (a==0 || b==0) myBoardScore[k-1][i][j].info[2].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[2].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            a=i;b=j;z=0;temp1=temp2=0;
            while (a<SIZE-1 && b<SIZE-1){
                a++;b++;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==SIZE-1 || b==SIZE-1 || arrayForInnerBoardLayout[a+1][b+1]!=k) break;myBoardScore[k-1][i][j].info[2].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[2].linknum++;temp1++;if (a==SIZE-1 || b==SIZE-1) myBoardScore[k-1][i][j].info[2].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[2].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            
            a=i;b=j;z=0;temp1=temp2=0;
            while (a>0 && b<SIZE-1){
                a--;b++;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==0 || b==SIZE-1 || arrayForInnerBoardLayout[a-1][b+1]!=k) break;myBoardScore[k-1][i][j].info[3].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[3].linknum++;temp1++;if (a==0 || b==SIZE-1) myBoardScore[k-1][i][j].info[3].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[3].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            a=i;b=j;z=0;temp1=temp2=0;
            while (a<SIZE-1 && b>0){
                a++;b--;
                if (arrayForInnerBoardLayout[a][b]==0) {z++;if (z==2 || a==SIZE-1 || b==0 || arrayForInnerBoardLayout[a+1][b-1]!=k) break;myBoardScore[k-1][i][j].info[3].space++;temp2++;}
                if (arrayForInnerBoardLayout[a][b]==k) {myBoardScore[k-1][i][j].info[3].linknum++;temp1++;if (a==SIZE-1 || b==0) myBoardScore[k-1][i][j].info[3].oppnum++;}
                if (arrayForInnerBoardLayout[a][b]==nk) {myBoardScore[k-1][i][j].info[3].oppnum++;break;}
                if (temp1==4 && temp2==0) {
                    if(k-1==0) fourtag1=1;
                    else if (k-2==0) fourtag2==1;}
            }
            
            int r;
            r1=0;r2=0;
            for (l=0;l<4;l++){
                r=myBoardScore[k-1][i][j].info[l].linknum;
                if (k-1==0 && r>6) r=6;
                if (k-1==1 && r>5) r=5;
                if (myBoardScore[k-1][i][j].info[l].space!=0){
                        if (k-1==0 && myBoardScore[k-1][i][j].info[l].oppnum<=2 && (r>=3 && r<=5)){
                            if (myBoardScore[k-1][i][j].info[l].oppnum==0 && r==3) r1++;
                            if (r==4) r2++;
                        }
                        r=r-1;if (r==0) r=1;
                    }
                switch (myBoardScore[k-1][i][j].info[l].oppnum){
                case 0:myBoardScore[k-1][i][j].live[r]++;break;
                case 1:myBoardScore[k-1][i][j].half[r]++;break;
                case 2:myBoardScore[k-1][i][j].dead[r]++;break;
                }
            }
        }
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
        	for (k=1;k<3;k++){//算分
            int nk=(k==1)?2:1;
            if (k-1==0 && arrayForInnerBoardLayout[i][j]==0){
                forbidden=0;
                forbidtag=1;
                arrayForInnerBoardLayout[i][j]=1;
                ifsix();
                if (forbidden==0) ifforbidden();
                if (forbidden==1) myBoardScore[0][i][j].forbidden=1;
                arrayForInnerBoardLayout[i][j]=0;
            }
            if (r1+myBoardScore[0][i][j].live[3]>=2 || (r2+myBoardScore[0][i][j].live[4]+myBoardScore[0][i][j].half[4])>=2 || (myBoardScore[0][i][j].live[6]+myBoardScore[0][i][j].half[6]+myBoardScore[0][i][j].dead[6]!=0)) myBoardScore[0][i][j].forbidden=1; 
            int s=0;
            s=s+myBoardScore[nk-1][i][j].live[5]*25000+myBoardScore[nk-1][i][j].half[5]*25000+myBoardScore[nk-1][i][j].dead[5]*25000;
            s=s+myBoardScore[nk-1][i][j].live[4]*7000+myBoardScore[nk-1][i][j].half[4]*1000+myBoardScore[nk-1][i][j].dead[4]*1;
            s=s+myBoardScore[k-1][i][j].live[4]*10000+myBoardScore[k-1][i][j].half[4]*5000+myBoardScore[k-1][i][j].dead[4]*1;
            s=s+myBoardScore[k-1][i][j].live[3]*2500+myBoardScore[k-1][i][j].half[3]*300+myBoardScore[k-1][i][j].dead[3]*1;
            s=s+myBoardScore[nk-1][i][j].live[3]*600+myBoardScore[nk-1][i][j].half[3]*200+myBoardScore[nk-1][i][j].dead[3]*1;
            s=s+r1*500+r2*500+(fourtag1+fourtag2)*2000;
            if (k-1==0 && (myBoardScore[1][i][j].live[3]>=2 || (myBoardScore[1][i][j].live[4]+myBoardScore[1][i][j].half[4])>=2)) s=s+10000;
            for (l=2;l>0;l--) s=s+myBoardScore[k-1][i][j].live[l]*110*l+myBoardScore[k-1][i][j].half[l]*60*l+myBoardScore[k-1][i][j].dead[l]*1*l;
            for (l=2;l>0;l--) s=s+myBoardScore[nk-1][i][j].live[l]*70*l+myBoardScore[nk-1][i][j].half[l]*20*l+myBoardScore[nk-1][i][j].dead[l]*1*l;
            if (k-1==0 && myBoardScore[0][i][j].forbidden==1){ 
                s=0;
            }
            s=s+myBoardScore[k-1][i][j].live[5]*50000+myBoardScore[k-1][i][j].half[5]*50000+myBoardScore[k-1][i][j].dead[5]*50000;
            if (arrayForInnerBoardLayout[i][j]!=0) s=0;
            myBoardScore[k-1][i][j].score=s;
            }
            
//            for (i=0;i<SIZE;i++){
//                for (j=0;j<SIZE;j++)
//                printf("%d\t",myBoardScore[bow-1][i][j].score);
//                printf("\n");
//           }
            sleep(1);

    int ex=7,ey=7;
    if (z==0 && bow==1) {z=1;}
    else for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++){//取点
            if (myBoardScore[bow-1][i][j].score>myBoardScore[bow-1][ex][ey].score) {ex=i;ey=j;}
            else if (myBoardScore[bow-1][i][j].score==myBoardScore[bow-1][ex][ey].score) {
                srand((unsigned)time(NULL));
                int rd=rand()%2;
                if (rd==1) {ex=i;ey=j;}}
            }

    if (status==1) {arrayForInnerBoardLayout[ex][ey]=1;y=SIZE-ex;x=ey;status=2;return;}
    else if (status==2) {arrayForInnerBoardLayout[ex][ey]=2;y=SIZE-ex;x=ey;status=1;return;}
}

