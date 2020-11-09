#include <stdio.h>
#include <ctime>
#include <graphics.h>
#define ROW 6
char s[100];
int sizeAlphabet = ROW*ROW;
int timePlay = 20000 ;
int trueClicked = 0;
int falseClicked = 0;
int score = 0;

struct alphabet
{
    int x;
    int y;
    char text;
    bool isSpecial;
    void draw ()
    {
        char s[100];
        if (isSpecial)
        {
            settextstyle(9, 0, 1);
            setcolor(12);
            sprintf (s," %c   ",text);
            //rectangle (x-15,y-10,x+25,y+25);
            outtextxy (x,y,s);
        }
        else
        {
            settextstyle(9, 0, 1);
            setcolor(15);
            sprintf (s," %c   ",text);
            //rectangle (x-15,y-10,x+25,y+25);
            outtextxy (x,y,s);
        }
    }
    bool checkMouse (int xMouse,int yMouse,int widthX=30,int widthY=30)
    {
        if (xMouse > (x-widthX) && xMouse < (x+widthX))
            if (yMouse > (y-widthY) && yMouse < (y+widthY))
                return 1;
        return 0;
    }
};

alphabet arrayAlphabet[1000];

void createAlphabets(bool isShuffle,int xStart = 250, int yStart = 150, int widthX = 60,int widthY = 60)
{
    int xRandom = rand() % sizeAlphabet;
    int xOriginal = xStart ;
    for (int i = 0 ; i < sizeAlphabet ; i++)
    {
        arrayAlphabet[i].x = xStart;
        arrayAlphabet[i].y = yStart;
        if(i==xRandom)
        {
            arrayAlphabet[i].isSpecial = 1;
        }
        else
            arrayAlphabet[i].isSpecial = 0;
        xStart += widthX;
        if((i+1) % ROW == 0)
        {
            yStart += widthY;
            xStart = xOriginal;
        }
        if(isShuffle)
            arrayAlphabet[i].text = 'A' + rand() % 26 ;
    }
}
void drawAlphabet()
{
    for(int i = 0 ; i < sizeAlphabet ; i++)
    {
        arrayAlphabet[i].draw();
    }
}
int findObjectClick(int x,int y)
{
    bool isCheck = 0 ;
    for(int i = 0 ; i < sizeAlphabet ; i++)
    {
        isCheck = arrayAlphabet[i].checkMouse(x,y);
        if(isCheck)
            return i;
    }
    return -1;
}
void check(int x,int y)
{
    int indexObjectClick = findObjectClick(x,y);
    bool isWin = 0;
    isWin = arrayAlphabet[indexObjectClick].isSpecial;
    if(isWin == 1)
    {
        createAlphabets(true);
        drawAlphabet();
        score +=5;
        trueClicked ++;
    }
    else
    {
        createAlphabets(false);
        drawAlphabet();
        falseClicked ++;
    }
}
void process(int x,int y)
{
    for (;; delay(100))
    {
        timePlay -=100;
        setcolor(14);
        settextstyle(8, 0, 1);
        sprintf (s,"Time: %02d:%02d",timePlay/60000,(timePlay/1000)%60);
        rectangle(780,70, 640, 110);
        outtextxy (650,80,s);
        setcolor(14);
        sprintf (s,"True: %d",trueClicked);
        rectangle(30, 60, 170, 140);
        outtextxy (50,70,s);
        sprintf (s,"False: %d",falseClicked);
        outtextxy (50,90,s);
        sprintf (s,"Score : %d",score);
        outtextxy (50,110,s);
        if (timePlay > 0 )
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                check (x,y);
            }
        }
        else
        {
            cleardevice();
            setcolor(15);
            settextstyle(6, 0, 3);
            outtextxy (300,230,"GAME OVER !");
            settextstyle(10, 0, 2);
            sprintf (s,"Your score is : %d",score);
            outtextxy (305,270,s);
            getch();
        }
    }
}
int main ()
{
    initwindow(800, 600);
    settextstyle(6, 0, 2);
    setcolor(3);
    outtextxy (220,30,"WELLCOME TO THE GAME");
    srand(time( 0));
    int x=0,y=0;
    createAlphabets(true);
    drawAlphabet();
    process(x,y);
    closegraph();

}














