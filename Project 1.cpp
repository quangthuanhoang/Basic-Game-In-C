#include <stdio.h>
#include <ctime>
#include <graphics.h>

int timePlay = 30000 ;
char s[100];
int sizeAlphabet = 36;
int trueClicked = 0;
int falseClicked = 0;
int score = 0;
int x=0,y=0;

struct alphabet {
    int x;
    int y;
    char text;
    bool isSpecial;
    void draw () {
        char s[100];
        if (isSpecial) {
            settextstyle(9, 0, 1);
            setcolor(12);
            sprintf (s," %c   ",text);
            outtextxy (x,y,s);
        }
        else {
            settextstyle(9, 0, 1);
            setcolor(15);
            sprintf (s," %c   ",text);
            outtextxy (x,y,s);
        }
    }
    bool checkMouse (int xMouse,int yMouse) {
		if (xMouse > (x-30) && xMouse < (x+30))
		if (yMouse > (y-30) && yMouse < (y+30))
			return true;
		return false;
	}
};

alphabet arrayAlphabet[36];

void createAlphabets(bool isShuffle,int xStart = 250, int yStart = 150,
                     int width = 60) {
    int xRandom = rand() % sizeAlphabet;
    int xOriginal = xStart ;
    for (int i = 0 ; i < sizeAlphabet ; i++) {
        arrayAlphabet[i].x = xStart;
        arrayAlphabet[i].y = yStart;
        xStart += width;
        if((i+1) % 6 == 0){
            yStart += width;
            xStart = xOriginal;
        }
        if(isShuffle)
            arrayAlphabet[i].text = 'A' + rand() % 26 ;
        if(i==xRandom) {
            arrayAlphabet[i].isSpecial = true;
        }
        else
            arrayAlphabet[i].isSpecial = false;
    }
}
void drawAlphabet()
{
    for(int i = 0 ; i < sizeAlphabet ; i++) {
        arrayAlphabet[i].draw();
    }
}
int findObjectClick(int x,int y) {
    for(int i = 0 ; i < sizeAlphabet ; i++) {
        if(arrayAlphabet[i].checkMouse(x,y))
            return i;
    }
    return -1;
}
void check(int x,int y) {
    int indexObjectClick = findObjectClick(x,y);
    if(arrayAlphabet[indexObjectClick].isSpecial == true) {
        createAlphabets(true);
        drawAlphabet();
        score +=5;
        trueClicked ++;
    }
    else {
        createAlphabets(false);
        drawAlphabet();
        falseClicked ++;
    }
}
void process() {
    for (;; delay(100)) {
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
        if (timePlay > 0 ) {
            if (ismouseclick(WM_LBUTTONDOWN)){
                getmouseclick(WM_LBUTTONDOWN, x, y);
                check (x,y);
            }
        }
        else {
            cleardevice();
            setcolor(15);
            settextstyle(6, 0, 3);
            outtextxy (280,230,"GAME OVER !");
            settextstyle(10, 0, 2);
            sprintf (s,"Your score is : %d",score);
            outtextxy (290,270,s);
            break;
        }
    }
}
int main () {
    initwindow(800, 600);
    settextstyle(6, 0, 2);
    setcolor(3);
    outtextxy (220,30,"WELLCOME TO THE GAME");
    srand(time( 0));
    createAlphabets(true);
    drawAlphabet();
    process();
    getch();
    closegraph();

}














