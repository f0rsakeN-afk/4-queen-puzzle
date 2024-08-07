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
};
int main()
{
    Queen m,s,A,t;
    int x=500,y=100,NEP;
    initwindow(1366,768,"OUTPUT");
    
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
	POINT mouse;
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
    settextstyle(BOLD_FONT,HORIZ_DIR,10000);
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
    delay(100);
    }
	getch();
    closegraph();
	return 0;
}

