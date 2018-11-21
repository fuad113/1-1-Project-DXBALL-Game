#include "iGraphics.h"
#include<stdio.h>
#include<conio.h>

#define xaxis 1000  //xaxis and yaxis are the pixels of the screen
#define yaxis 680
#define Row 20      //Row and Col is the structure array size
#define Col 20
#define rw 5        //row and cl are brick numbers
#define cl 10
#define white 255,255,255 //colors
#define black 0,0,0
#define gray 128,128,128
#define Red 255,0,0

// bool score is a boolean variable for initializing Current Score at the starting of a level

bool score=true;

//function prototypes
void showball();
/* showball() function shows the ball int hte game window */
void showbar();
/* showbar() function shows the bar in the game window */
void control(int counter, int flag);
/* control(int,int) function takes two integers as input. The 1st integer is the number of bricks that exist
in the current level. And the 2nd integer is the number of level that gamer is playing now. If the total numbers
of bricks are zero int the current level, this function will increase the flag number and, change the level. Also
initialize the value of the bricks*/
void ballChange();
/* ballchange() will change the position of the ball according to the values of dx ,dy and direction of the ball*/
void removebrick();
/* removebrick() will remove the bricks by setting the brick values to zero. While the control() function will initialize
them back to one. this function detects collision of the ball with the bricks, and also counts Currentscore */
void BuildScore();
/* This function will Save the High Score in files */
void ShowScore();
/* View score will show Current score int the game window */
void iCredit();
/* For Showing credit of the game */

void iMenu();
/* For Showing game menu */

/*
ball_x,ball_y are X&Y co-ordinates of the ball
dx,dy are movement speed of the ball
r is the radius of the ball
*/

int ball_x, ball_y,dx=5,dy=7,r=10;  //Co-ordinate and radius of the ball

/*
bar_x,bar_y are the co-ordinates of the bar
bar_l,bar_h are length and heigth of the bar
*/
int bar_x,bar_y=26,bar_l=80,bar_h=8; //Ball-change
int i,j,x,y,l,flag=0,mask=0; //Initializing variables
int CurrentScore, HighScore;    //variables for showing scores
double texty;

char str[5];
//variables
//int level=1;

// variables for bricks
struct box{
    int value=1;
    int brick_x,brick_y; //Co-ordinates of the bricks
}brick[Row][Col];
//length an heigth of the bricks
int length=40,height=20;

void iDraw()
{
    iClear();

    //This will show The game menu

    if(flag==0)
    {
        iMenu();
    }

    //Codes for level one

    if(flag==1){

    /*This initializes CurrentScore to zero at staring of level one. The initializer "score" is set true at first of the game.
    when it goes throw if(score) The current score is set to zero and initializer "score" is set false. So when iDraw
    is called frequently, the Current score doesn't initialized all the time. It is initialized only the 1st time.  */

        if(score){
            CurrentScore=0;
            score=false;
        }

        //variable for counting number of bricks

        int counter =0;
        y=yaxis-height;

        //color codes

        int Rbrick=0,Gbrick=20,Bbrick=89;

        //for showing brick on level 1

        for(i=0;i<rw;i++)    //Showing row
        {
            x=300;
            for(j=0;j<cl;j++)   //Showing column
            {
                iSetColor(Rbrick+=5,Gbrick+=2,Bbrick+=3);
                if(brick[i][j].value)
                {
                    iFilledRectangle(x,y,length,height);
                    brick[i][j].brick_x=x;
                    brick[i][j].brick_y=y;
                }
                x=x+length;
                iSetColor(black);
                iLine(x,y+height,x,y);
                //Changing position of the brick, in x axis
            }
            iSetColor(black);
            iLine(0,y,xaxis,y);
            y=y-height;     //Changing position of the brick in y axis
        }

        // Showing ball and bar if the game is over, the ball and bar won't be seen

         if(ball_y-r> bar_y)
         {
            showball();
            showbar();
         }


        // Ending the GAME
        if(ball_y < bar_y)
        {
            //mask variable for pausing the game
            mask=1;
            iPauseTimer(0);
            iSetColor(white);
            iText(xaxis/2-100, yaxis/2, "Game Over.... Press END.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iSetColor(white);
            iText(10, 10, "Press p for pause, r for resume, END for exit.");
            ShowScore();
        }

        //Counts, How many brick exist

        for(i=0;i<5;i++)
        {
            for(j=0;j<10;j++)
            {
                if(brick[i][j].value)
                    counter++;
            }
        }

        //control function changes the level ind initializes brick values to 1

        control(counter,flag);

    }

    //flag 2 for level two

    if(flag==2)
    {

    /*This initializes CurrentScore to zero at staring of level one. The initializer "score" is set true at first of the game.
    when it goes throw if(score) The current score is set to zero and initializer "score" is set false. So when iDraw
    is called frequently, the Current score doesn't initialized all the time. It is initialized only the 1st time.  */

        if(score){
            CurrentScore=0;
            score=false;
        }
        // counter for counting existing bricks

        int counter=0;

        {
            int gap=80;
            y=yaxis-130;
            int Rbrick=120,Gbrick=140,Bbrick=100;

          //For showing bricks
          for(i=0;i<rw;i++)
            {
              x=300;
              for(j=0;j<cl;j++)
              {
                     if(brick[i][j].value)
                        {
                            iSetColor(Rbrick,Gbrick,Bbrick);
                            iFilledRectangle(x,y,length,height);
                            brick[i][j].brick_x=x;
                            brick[i][j].brick_y=y;


                        }
                        x=x+length;    //Changing position of the brick, in x axis
                        x=x+l;
                        iSetColor(black);
                        iLine(x,y+height,x,y); // For drawing wall
                }
                iSetColor(black);
                iLine(0,y,xaxis,y);
                y=y-gap;    //Changing position of the brick, in y axis
            }

        if(ball_y-r>bar_y)
         {
            showball();
            showbar();
         }

        // Ending the GAME
        if(ball_y< bar_y)
        {
            mask=1;
            iPauseTimer(0);
            iSetColor(255, 255, 255);
            iText(xaxis/2-100, yaxis/2, "Game Over.... Press END.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iSetColor(255, 255, 255);
            iText(10, 10, "Press p for pause, r for resume, END for exit.");

            //For showing score

            ShowScore();
        }

        //for counting bricks
        for(i=10;i<12;i++)
        {
            for(j=0;j<20;j++)
            {
                if(brick[i][j].value)
                    counter++;
            }
        }
        control(counter,flag);
    }

    }

    //Level 3

    if(flag==3)
    {

    /*This initializes CurrentScore to zero at staring of level one. The initializer "score" is set true at first of the game.
    when it goes throw if(score) The current score is set to zero and initializer "score" is set false. So when iDraw
    is called frequently, the Current score doesn't initialized all the time. It is initialized only the 1st time.  */

        if(score){
            CurrentScore=0;
            score=false;
        }
        //Counter for counting the existing bricks
        int counter=0;
        int Rbrick=255,Gbrick=0,Bbrick=0;

        y=yaxis-100;


        //Loop for showing brick

        for(i=0;i<5;i++)
        {

            int x=120;
            for(j=0;j<10;j++)
            {
                iSetColor(Rbrick,Bbrick,Gbrick);
                if(brick[i][j].value)
                {
                    iFilledRectangle(x,y,length,height);
                    brick[i][j].brick_x=x;
                    brick[i][j].brick_y=y;

                }
              x=x+(2*length);
            }
            y=y-55;

            //If-only conditions for changing color of the bricks after  two rows
            if(i==1)
            {
                Rbrick=0;
                Bbrick=255;
                Gbrick=0;
            }
            if(i==3)
            {
                Rbrick=0;
                Bbrick=0;
                Gbrick=255;
            }
        }


        //For showing ball and bar
        if(ball_y-r>bar_y)
         {
            showball();
            showbar();
         }

        //Ending game conditions

        if(ball_y < bar_y)
        {
            mask=1;
            iPauseTimer(0);
            iSetColor(255, 255, 255);
            iText(xaxis/2-100, yaxis/2, "Game Over.... Press END.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iSetColor(255, 255, 255);
            iText(10, 10, "Press p for pause, r for resume, END for exit.");
            ShowScore();

        }

        //for counting bricks
        for(i=10;i<12;i++)
        {
            for(j=0;j<20;j++)
            {
                if(brick[i][j].value)
                    counter++;
            }
        }

        //Changing level
        control(counter,flag);

    }

    //level 4

    if(flag==4)
    {
    /*This initializes CurrentScore to zero at staring of level one. The initializer "score" is set true at first of the game.
    when it goes throw if(score) The current score is set to zero and initializer "score" is set false. So when iDraw
    is called frequently, the Current score doesn't initialized all the time. It is initialized only the 1st time.  */

        if(score){
            CurrentScore=0;
            score=false;
        }
        int counter=0;

        int y=yaxis-100;

        //Loop for showing brick

        for(i=0;i<2;i++)
        {
            x=270;
            for(j=0;j<5;j++)
            {
                if(brick[i][j].value)
                {
                    iSetColor(120,120,120);
                    iFilledRectangle(x,y,length,height);
                    brick[i][j].brick_x=x;
                    brick[i][j].brick_y=y;
                }
                x=x+length;
                iSetColor(black);
                iLine(x,y+height,x,y);
            }
            x=270;
            iSetColor(black);
            iLine(x,y,xaxis,y);
            y=y-height;
        }

        y=yaxis-200;

        for(i=0;i<2;i++)
        {
            x=570;
            for(j=5;j<10;j++)
            {
                if(brick[i][j].value)
                {
                    iSetColor(130,10,100);
                    iFilledRectangle(x,y,length,height);
                    brick[i][j].brick_x=x;
                    brick[i][j].brick_y=y;
                }
                x=x+length;
                iSetColor(black);
                iLine(x,y+height,x,y);
            }
            x=570;
            iSetColor(black);
            iLine(x,y,xaxis,y);
            y=y-height;
        }


        y=yaxis-400;

        for(i=2;i<5;i++)
        {
            x=300;
            for(j=0;j<10;j++)
            {
                if(brick[i][j].value)
                {
                    iSetColor(0,255,0);
                    iFilledRectangle(x,y,length,height);
                    brick[i][j].brick_x=x;
                    brick[i][j].brick_y=y;
                }
                x=x+length;
                iSetColor(black);
                iLine(x,y+height,x,y);
            }
            x=300;
            iSetColor(black);
            iLine(x,y,xaxis,y);
            y=y-height;
        }

        if(ball_y-r > bar_y)
        {
            showball();
            showbar();
        }

        if(ball_y < bar_y)
        {
            mask=1;
            iPauseTimer(0);
            iSetColor(255, 255, 255);
            iText(xaxis/2-100, yaxis/2, "Game Over.... Press END.",GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iSetColor(255, 255, 255);
            iText(10, 10, "Press p for pause, r for resume, END for exit.");
            ShowScore();

        }

        //for counting bricks
        for(i=10;i<12;i++)
        {
            for(j=0;j<20;j++)
            {
                if(brick[i][j].value)
                    counter++;
            }
        }

        //For initializing game;
        control(counter,flag);

    }
    if(flag==10||flag==9)
    {
        iCredit();
        texty+=.1;
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    if(mx>xaxis-(bar_l+bar_h/2))
        bar_x=xaxis-(bar_l+bar_h/2);
    else if(mx < bar_h/2)
        bar_x=4;
    else if(flag==5||mask==1);
    //else if(ball_y-r<20);
	else
        bar_x=mx;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(flag==0)
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if((mx>150&&mx<300)&&(my>550&&my<630))
            flag=1;
        else if((mx>40&&mx<550)&&(my>550&&my<630))
            exit(0);
        else if((mx>150&&mx<300)&&(my>420&&my<500))
            flag=1;
        else if((mx>400&&mx<550)&&(my>450&&my<500))
            flag=2;
        else if((mx>150&&mx<300)&&(my>290&&my<370))
            flag=3;
        else if((mx>400&&mx<550)&&(my>290&&my<370))
            flag=4;
        else if((mx>270&&mx<430)&&(my>190&&my<280))
            flag=10;
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is < brick[i][j].brick_y+20 called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if(key == 'p')
	{
		//do something with 'q'
		iPauseTimer(0);
	}
	else if(key == 'b')
    {
        flag=0;
        texty=0;
        /*iResumeTimer(0);
        for(i=0;i<rw;i++)
            for(j=0;j<cl;i++)
        {
            brick[i][j].value=1;
        }*/
    }
    if(ball_y-r<bar_y)
    {}
	else
    {
        if(key == 'r')
        {
            iResumeTimer(0);
        }
    }
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	else if(key == GLUT_KEY_LEFT)
    {
        if(bar_x>0)
            bar_x-=10;
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        if(bar_x<xaxis-bar_l)
        bar_x+=10;
    }
	//place your codes for other keys here
}

void iMenu()
{
        int l=150,h=80;
        iSetColor(255,255,255);
        iRectangle(150,550,l,h);
        iRectangle(400,550,l,h);
        iRectangle(150,420,l,h);
        iRectangle(400,420,l,h);
        iRectangle(150,290,l,h);
        iRectangle(400,290,l,h);
        iRectangle(270,190,l,h);

        iSetColor(75,255,75);
        iText(170,580, "New Game",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(440,580,"EXIT",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(170,450, "Level-1",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(440,450,"Level-2",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(170,320, "Level-3",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(440,320,"Level-4",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,220,"Credit",GLUT_BITMAP_TIMES_ROMAN_24);

        score=true;
}

void iCredit()
{
    if(flag==10)
    {
        texty=0;
        flag=9;
    }
    if(flag==9)
    {
        iSetColor(255,255,255);
        iText(300,texty,"Home made Dx_ball GAME :p",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,texty-30,"Members:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,texty-60,"ADITYA CHAKMA(120)",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,texty-90,"AHMED NAFIS FUAD(113)",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(300,texty-120,"Thanks for letting us play...",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400,texty-150,"\\m/",GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void ShowScore(){
    int i,x,temp=CurrentScore;
    for(i=0;i<5;i++)
    {
        x=temp%10;
        temp=temp/10;
        str[4-i]=x+'0';
    }
    //S[5]='\0';
    iSetColor(Red);
    iText(xaxis-200,10,"Score : ");
    iText(xaxis-100, 10, str  );
}

/*void BuildScore(){
    int a;
    FILE *fp;

    switch(flag){
    case 1:
        fp=fopen("Score1.txt","r");

        fscanf(fp,"%d",&a);
        fclose(fp);
        if(CurrentScore>a)
            a=CurrentScore;

        fp=fopen("Score1.txt","w");
        fprintf(fp,"%d",a);
        fclose(fp);
        break;
    case 2:
        fp=fopen("Score2.txt","r");

        fscanf(fp,"%d",&a);
        fclose(fp);
        if(CurrentScore>a)
            a=CurrentScore;

        fp=fopen("Score2.txt","w");
        fprintf(fp,"%d",a);
        fclose(fp);
        break;
    case 3:
        fp=fopen("Score3.txt","r");

        fscanf(fp,"%d",&a);
        fclose(fp);
        if(CurrentScore>a)
            a=CurrentScore;

        fp=fopen("Score3.txt","w");
        fprintf(fp,"%d",a);
        fclose(fp);
        break;
    case 4:
        fp=fopen("Score4.txt","r");

        fscanf(fp,"%d",&a);
        fclose(fp);
        if(CurrentScore>a)
            a=CurrentScore;

        fp=fopen("Score4.txt","w");
        fprintf(fp,"%d",a);
        fclose(fp);
        break;
    case 5:
        fp=fopen("Score5.txt","r");

        fscanf(fp,"%d",&a);
        fclose(fp);
        if(CurrentScore>a)
            a=CurrentScore;

        fp=fopen("Score5.txt","w");
        fprintf(fp,"%d",a);
        fclose(fp);
        break;

    }


}*/

void control(int counter, int flag)
{
    if(counter==0)
        {
            //iPauseTimer(0);
            iSetColor(255, 255, 255);
            iText(xaxis/2-100, yaxis/2, "Level-1 Complete");
            flag++;
            for(i=0;i<Row;i++)
            {
                for(j=0;j<Col;j++)
                    brick[i][j].value=1;
            }
            score=true;
        }
}

void showbar()
{
        iSetColor(gray);
        iFilledRectangle(bar_x,bar_y,bar_l,bar_h);
        iFilledCircle(bar_x,bar_y + (bar_h)/2 , bar_h/2);
        iFilledCircle(bar_x + bar_l,bar_y + (bar_h)/2 , bar_h/2);
}

// function for moving the ball
void ballChange(){

    if(!mask)
    if(flag)
    {
        ball_x += dx;
        ball_y += dy;

        if(ball_x-r <0 || ball_x +r > xaxis) dx=-dx;
        if(ball_y+r > yaxis) dy=-dy;
        printf("ball_x =%d, ball_y=%d, bar_x= %d\n",ball_x,ball_y,bar_x);
    }
}

void barchange()
{
    if(ball_x+r > bar_x && ball_x-r < bar_x+80 && ball_y <40){
        if(ball_x > bar_x && ball_x <= bar_x+bar_l/3){
            dx-=2;
            //dy+=1;
            dy=-dy;
        }
        else if(ball_x > bar_x + bar_l/3 && ball_x <= bar_x + (bar_l - bar_l/3)) dy=-dy;
        else if(ball_x > bar_x + (bar_l - bar_l/3) && ball_x < bar_x + bar_l){
            dx+=2;
            //dy-=1;
            dy=-dy;
        }

    }
    /*if(ball_y< bar_y)
    {
        iPauseTimer(0);
    }*/

}

void showball()
{
        iSetColor(255, 0, 0);
        iFilledCircle(ball_x, ball_y, r);
        iSetColor(255,255, 0);
        iFilledCircle(ball_x, ball_y, r-3);
        iSetColor(255, 139, 87);
        iFilledCircle(ball_x, ball_y, r-6);
        iSetColor(255, 255, 255);
        iLine(0,25,xaxis,25);
}



void removebrick(){
    for(i=0;i<rw;i++)
        {
            for(j=0;j<cl;j++)
            {
                int topx,topy,bottomx,bottomy,leftx,lefty,rightx,righty,a,b,v;
                topx=ball_x; topy=ball_y+r;
                bottomx=ball_x; bottomy=ball_y-r;
                leftx=ball_x-r; lefty=ball_y;
                rightx=ball_x+r; righty=ball_y;

                a=brick[i][j].brick_x;
                b=brick[i][j].brick_y;
                v=brick[i][j].value;

                if(v && topx >= a && topx <= (a+length) && topy >= b && topy <= (b+height) )
                {
                    brick[i][j].value--;
                    ball_y-=7;
                    dy=-dy;
                    CurrentScore+=rand()%5;
                    break;
                }
                else if(v && bottomx >= a && bottomx <= (a+length) && bottomy >= b && bottomy <= (b+height) )
                {
                    brick[i][j].value--;
                    ball_y-=7;
                    dy=-dy;
                    CurrentScore+=rand()%5;
                    break;
                }
                else if(v && leftx >= a && leftx <= (a+length) && lefty >= b && leftx <= (b+height) )
                {
                    brick[i][j].value--;
                    ball_x-=5;
                    dx=-dx;
                    CurrentScore+=rand()%5;
                    break;
                }
                else if(v && rightx >= a && rightx <= (a+length) && righty >= b && righty <= (b+height) )
                {
                    brick[i][j].value--;
                    ball_x-=5;
                    dx=-dx;
                    CurrentScore+=rand()%5;
                    break;
                }

            }
        }
}

//main function
int main()
{
    bar_x=xaxis/2-bar_l/2;
    //iPauseTimer(0);
    ball_x =bar_x+bar_l/2;
	ball_y =bar_y+50;

	//place your own initialization codes here.
   PlaySound("DX-Ball_2_Soundtrack-_Barnicle.wav",NULL,SND_ASYNC|SND_LOOP);
	//rate of changing ball
	iSetTimer(1, removebrick);
	iSetTimer(10, ballChange);
	iSetTimer(1, barchange);
	//iSetTimer(10, ShowScore);
	//dx = 5;
	//dy = 7;
	iInitialize(xaxis, yaxis, "Dx_Ball");   //Screen Size

	getch();

	return 0;
}
