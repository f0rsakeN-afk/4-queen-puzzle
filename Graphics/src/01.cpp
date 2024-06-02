#include <bits/stdc++.h>
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
    bool isSafe(int row, int col, vector<string> board, int N)
    {
        int duprow = row;
        int dupcol = col;
        while (row >= 0 && col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
                row--;
                col--;
        }

        col = dupcol;
        row = duprow;

        while (col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
                col--;
        }

        row = duprow;
        col = dupcol;
        while (row < N && col >= 0)
        {
            if (board[row][col] == 'Q')
            {
                return false;
            }
                row++;
                col--;
        }
        return true;
    }

    void Solve(int col, vector<string> &board, vector<vector<string>> &ans, int N)
    {
        if (col == N)
        {
            ans.push_back(board);
            return;
        }

        for (int row = 0; row < N; row++)
        {
            if (isSafe(row, col, board, N))
            {
                board[row][col] = 'Q';
                Solve(col + 1, board, ans, N);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveQueen(int N)
    {
        vector<vector<string>> ans;
        vector<string> board(N);
        string s(N, '.');
        for (int i = 0; i < N; i++)
        {
            board[i] = s;
        }
        Solve(0, board, ans, N);
        return ans;
    }
};
int main()
{
    Queen m,s;
    int N = 4;
    Queen X;
    vector<vector<string>> ans = X.solveQueen(N);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int J = 0; J < ans[0].size(); J++)
        {
            cout << ans[i][J];
            cout << endl;
        }
        cout << endl;
    }
    int x=500,y=100,NEP;
    initwindow(1366,768,"OUTPUT");
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
    readimagefile("black.jpg",100,100,175,175);
    readimagefile("white.jpg",220,100,295,175);
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
                 if(c!=0 &&d!=0)
                 {
                  readimagefile("black.jpg",c,d,c+92,d+92);
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
            if(a>=500 &&a<=900 &&b>=100 && b<=500)
            {
              s=m.getthecell(a,b);
              c=s.x;
              d=s.y;
              if(c!=0 &&d!=0)
              {
			   readimagefile("white.jpg",c,d,c+92,d+92);
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
