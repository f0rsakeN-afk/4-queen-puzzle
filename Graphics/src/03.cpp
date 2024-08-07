#include <iostream>
#include<graphics.h>
using namespace std;
class Queen
{
public:
  int x,y;
  Queen getthecell(int a,int b)
   {
    x=a;
    y=b;
    int m,n;
     m=a/100;
     n=b/100;
     Queen temp;
     if(x>=100*m && x<100*(m+1) &&y>=100*n && y<100*(n+1))
     {
        temp.x=100*m+4; 
        temp.y=100*n+4;
        return temp;
     }
   }
   Queen leftclick(int solu1[4][4],int a,int b)
    { 
        Queen temp;
        temp.x=0;
        temp.y=0;
        cout<<"suceffully passed array(solu1)  as an argument."<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
              cout<<solu1[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
              if(solu1[i][j]==1)
               {
                 cout<<"LEFT-CLICK\t"<<i<<" "<<j<<endl;
                 int s=0,r=0;
                 s=((i+5)*100)+4;
                 r=((j+1)*100)+4;
                 if(a==s && b==r)
                  {
                    temp.x=s;
                    temp.y=r;
                    return temp;
                  }
               }
            }
        } 
    }
    Queen rightclick(int **arr,int a,int b)
    { 
        Queen temp;
        temp.x=0;
        temp.y=0;
        cout<<"suceffully passed array(SOLU1)  as an argument."<<endl;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
              cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
              if(arr[i][j]==1)
               {
                 cout<<"RIGHT-CHECKED\t"<<i<<" "<<j<<endl;
                 int s=0,r=0;
                 s=((i+5)*100)+4;
                 r=((j+1)*100)+4;
                 if(a==s && b==r)
                  {
                    temp.x=s;
                    temp.y=r;
                    return temp;
                  }
               }
            }
        } 
    }

   bool issafe(int**arr,int x,int y,int n)
   {
    for(int row=0;row<4;row++)//checking the columns.
    {
        if(arr[row][y]==1)
        return false;
    }
    int row=x;
    int col=y;
    while(row>=0 && col>=0)//checking the left diagonal column.
    {
        if (arr[row][col]==1)
        {
            return false;
        }
        row--;
        col--;
    }
     row=x;
    col=y;
    while(row>=0 && col<4)//checking the right diagonal column.
    {
        if(arr[row][col]==1)
        {
            return false;
        }
        row--;
        col++;
    }
    return true;
}
bool nQueen(int **arr,int x, int )
{
    if(x>=4)
    {
        return true;
    }
    for(int col=0;col<4;col++)
    {
        if(issafe(arr,x,col,4)==1)
        {
            arr[x][col]=1;
            if(nQueen(arr,x+1,4))
            {
                return true;
            }
            arr[x][col]=0;//backtracing.
        }
    }
    return false;
}
void invalid()
{
    settextstyle(BOLD_FONT,HORIZ_DIR,4);
    outtextxy(1000,150,"INVALID CLICK.");
} 
};
int main()
{
    Queen m,s,A,t,I;
    int NEP;
    Home:
    initwindow(1366,768,"OUTPUT1");
    readimagefile("frontbg3.jpg",0,0,1366,768);
    POINT mouse;
    for(int i=0;i<500;i++)
     {
        setcolor(YELLOW);
        readimagefile("frontbg1.jpg",1000,0,1366,300);
        setbkcolor(BLUE);
        settextstyle(BOLD_FONT,HORIZ_DIR,8);
        outtextxy(380,50,"4 QUEEN PUZZLE.");
        setcolor(RED+i);
         setbkcolor(BLUE+i);
        rectangle(610+i,530+i,820+i,580+i);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        outtextxy(615+i,535+i,"PLAY NOW");
        rectangle(570+i,600+i,880+i,650+i);
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        outtextxy(575+i,605+i,"INSTRUCTIONS");
        settextstyle(BOLD_FONT,HORIZ_DIR,5);
        rectangle(655+i,670+i,790+i,720+i);
        outtextxy(660+i,675+i,"ABOUT");
        i=i%3;
        if(GetAsyncKeyState(VK_LBUTTON))
         {
           int c=0,d=0;
           GetCursorPos(&mouse);
           c=mouse.x;
           d=mouse.y;
           cout<<"THE CURSOR POSITION IS "<<c<<" "<<d<<endl;
           if(c>=610 && c<=823 && d>=530 && d<=583)
           {
            closegraph();
            goto Play;
           }
           if(c>=570 && c<=883 && d>=600 && d<=653)
           {
            closegraph();
            goto Instruction;
           }
           if(c>=655 && c<=793 && d>=670 && d<=723)
           {
            closegraph();
            goto About;
           }
          }
        delay(100);
    }
    Instruction:
    initwindow(1366,768,"output-Instruction");
    readimagefile("instruction.jpg",0,0,1366,768);
    readimagefile("solu1.jpg",1000,120,1300,420);
    readimagefile("solu2.jpg",50,400,350,700);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    setcolor(RED);
    setbkcolor(YELLOW);
    outtextxy(200,200,"1.No Two Queens Should Present In The Same Row.");
    outtextxy(200,250,"2.No Two Queens Should Present In The Same Column.");
    outtextxy(200,300,"3.No Two Queens Should Be Diagonally Attacked .");
    outtextxy(380,450,"4.There Might Be two Combinations,So,for one combination ");
    outtextxy(380,500,"Black Queen Which Appears On the Right-click of Mouse,");
    outtextxy(380,550,"And For Another Their occurs the White Queen on Left-click of Mouse");
    outtextxy(380,600,"While Clicking on the Right Position's combination On The Chess Board.");
    readimagefile("home1.jpg",1200,630,1300,730);
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
    setcolor(RED);
    setbkcolor(GREEN);
    outtextxy(25,50,"SOME BASIC INFORMATIONS ARE:-");
    for(int j=0;j<100;j++)
    {
    //setcolor(RED+j);
    //settextstyle(BOLD_FONT,HORIZ_DIR,7);
    //outtextxy(1105,655,"HOME");
    if(GetAsyncKeyState(VK_LBUTTON))
         {
           int c=0,d=0;
           GetCursorPos(&mouse);
           c=mouse.x;
           d=mouse.y;
           cout<<"THE CURSOR POSITION IS "<<c<<" "<<d<<endl;
           if(c>=1200 && c<=1300 && d>=630 && d<=730)
           {
            closegraph();
            goto Home;
           }
         }
     delay(2000);
    }
   
    About:
    initwindow(1366,768,"output-About");
    for(int i=0;i<100;i++)
    {
        setbkcolor(WHITE);
    setcolor(RED+i);
    readimagefile("about.jpg",0,0,1366,768);
    readimagefile("home1.jpg",1200,50,1300,150);
    //settextstyle(BOLD_FONT,HORIZ_DIR,7);
    //outtextxy(1205,55,"HOME");
    if(GetAsyncKeyState(VK_LBUTTON))
         {
           int c=0,d=0;
           GetCursorPos(&mouse);
           c=mouse.x;
           d=mouse.y;
           cout<<"THE CURSOR POSITION IS "<<c<<" "<<d<<endl;
           if(c>=1200 && c<=1300 &&d>=50 && d<=150)
           {
            closegraph();
            goto Home;
           }
         }
    settextstyle(BOLD_FONT,HORIZ_DIR,8);
    outtextxy(350,25,"CONTRIBUTERS");
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    readimagefile("priya.jpg",15,350,325,650);
    outtextxy(60,665,"PRIYA MISHRA");
    readimagefile("ramesh3.jpg",360,350,660,650);
    outtextxy(390,665,"RAMESH Kr.MAHATO");
    readimagefile("naresh.jpg",695,350,995,650);
    outtextxy(750,665,"NARESH RAJBANSHI");
    readimagefile("suraj1.jpg",1030,350,1330,650);
    outtextxy(1080,665,"SURAJ SINGH");
    i=i%4;
    delay(2000);
    }
    Play:
    int x=500,y=100;
    initwindow(1366,768,"output-Play");
    readimagefile("play.jpg",0,0,1366,768);
    readimagefile("home1.jpg",1100,620,1265,720);
    readimagefile("restart.jpg",1100,490,1265,590);
    //settextstyle(BOLD_FONT,HORIZ_DIR,1);
    int **arr=new int *[4];//creating the 2D array.
    for(int i=0;i<4;i++)
    {
        arr[i]=new int[4];
        for(int j=0;j<4;j++)
        {
            arr[i][j]=0;
        }
    }
     if(A.nQueen(arr,0,4)==true)
    {
        cout<<"THE ONE SOLUTION'S COMBINATION  IS"<<endl;
        for(int i=0;i<4;i++)// for displaying the output.
        {
            for(int j=0;j<4;j++)
            {
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    } 
    cout<<"THE ANOTHER SOLUTION'S COMBINATION IS"<<endl;
    int solu1[4][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
         solu1[i][j]=0;
        }
    }
    for(int i=0;i<4;i++)
     {
      for(int j=0;j<4;j++)
        {
         if(arr[i][j]==1) 
           {
            solu1[j][i]=1;
            }
        }
     }
    for(int i=0;i<4;i++)
     {
       for (int j=0;j<4;j++)
        {
        cout<<solu1[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arr[i][j]==1)
            {
                i=((i+1)*100)+4;
                j=((j+5)*100)+4;
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(NEP==0)
            {
            setcolor(YELLOW);
            setlinestyle(3,0,4);
            setfillstyle(SOLID_FILL,RED);
            rectangle(x,y,x+100,y+100);
            floodfill(x+3,y+3,YELLOW);
            NEP=1;
            }
            else
            {
                setcolor(YELLOW);
                setlinestyle(3,0,4);
                setfillstyle(SOLID_FILL,BLUE);
                rectangle(x,y,x+100,y+100);
                floodfill(x+3,y+3,YELLOW);
                NEP=0;
            }
            x=x+100;
        }
        if (NEP==0)
            NEP=1;
        else
            NEP=0;
        x=500;
        y=y+100;
    }
    setbkcolor(BLUE);
    readimagefile("white.jpg",100,100,175,175);
    readimagefile("black.jpg",220,100,295,175);
    outtextxy(90,185,"* LEFT CLICK");
    outtextxy(210,185,"* RIGHT CLICK");
    outtextxy(132,70,"(A)");
    outtextxy(252,70,"(B)");
    outtextxy(620,560," (4*4) CHESS BOARD.");
    outtextxy(100,245,"THE POSSIBLE SOUTIONS ARE : ");
    outtextxy(50,345,"[A]");
    readimagefile("solu1.jpg",90,265,340,465);
    outtextxy(50,574,"[B]");
    readimagefile("solu2.jpg",90,485,340,685);
    //lower horizontal.
    outtextxy(540,515,"[ 0 ]");
    outtextxy(640,515,"[ I ]");
    outtextxy(740,515,"[ II ]");
    outtextxy(840,515,"[ III ]");
    //upper horizontal.
    outtextxy(540,70,"[ 0 ]");
    outtextxy(640,70,"[ 1 ]");
    outtextxy(740,70,"[ 2 ]");
    outtextxy(840,70,"[ 3 ]");
    //left vertical.
    outtextxy(460,145,"[ 0 ]");
    outtextxy(460,245,"[ 1 ]");
    outtextxy(460,345,"[ 2 ]");
    outtextxy(460,445,"[ 3 ]");
    //right vertical.
    outtextxy(915,145,"[ 0 ]");
    outtextxy(915,245,"[ I ]");
    outtextxy(915,345,"[ II ]");
    outtextxy(915,445,"[ III ]");
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
	while(1)
	{
		if(GetAsyncKeyState(VK_LBUTTON))
		{
            int c=0,d=0;
            GetCursorPos(&mouse);
            int a=mouse.x;
            int b=mouse.y;
            if(a>=500 && a<=900 && b>=100 && b<=500)
            {
                s=m.getthecell(a,b);
                 c=s.x;
                 d=s.y;
                t=m.leftclick(solu1,c,d);
                int f,g;
                f=t.x;
                g=t.y;
                cout<<"THE RETURN CORDINATE IS"<<f<<"  "<<g;
                if(f!=0 && g!=0)
                 {
                     
                      readimagefile("white.jpg",f,g,f+92,g+92);
                      cout<<"THE LEFT_CLICKED CORDINATE IS\t("<<c<<","<<d<<")"<<endl;
                 }
            }
		}
		else if(GetAsyncKeyState(VK_RBUTTON))
		{
            int c=0,d=0;
            GetCursorPos(&mouse);
            int a=mouse.x;
            int b=mouse.y;
            //cout<<"THE RIGHT_CLICKED CORDINATE before checked IS\t("<<a<<","<<b<<")"<<endl;
            if(a>=500 &&a<=900 &&b>=100 && b<=500)
            {
              s=m.getthecell(a,b);
              c=s.x;
              d=s.y;
              t=m.rightclick(arr,c,d);
              int m=0,n=0;
              m=t.x;
              n=t.y;
              cout<<"THE RETURNED CORDINATE IS\t"<<m<<" "<<n<<endl;
              if(m!=0 &&n!=0)
              {
			      readimagefile("black.jpg",m,n,m+92,n+92);
                  cout<<"THE RIGHT_CLICKED CORDINATE IS\t("<<c<<","<<d<<")"<<endl;
              }
            }
		}
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
     //outtextxy(1105,655,"HOME");
    // outtextxy(1105,525,"CLEAR");
     if(GetAsyncKeyState(VK_LBUTTON))
         {
           int c=0,d=0;
           GetCursorPos(&mouse);
           c=mouse.x;
           d=mouse.y;
           cout<<"THE CURSOR POSITION IS "<<c<<" "<<d<<endl;
           if(c>=1100 && c<=1265 && d>=620 && d<=720)
           {
            closegraph();
            goto Home;
           }
         }
          if(GetAsyncKeyState(VK_LBUTTON))
         {
           int c=0,d=0;
           GetCursorPos(&mouse);
           c=mouse.x;
           d=mouse.y;
           cout<<"THE CURSOR POSITION IS "<<c<<" "<<d<<endl;
           if(c>=1100 && c<=1265 && d>=490 && d<=590)
           {
            closegraph();
            goto Play;
           }
         }
         delay(100);
    }
	getch();
    closegraph();
	return 0;
}

