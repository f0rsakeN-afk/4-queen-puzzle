#include <bits/stdc++.h>
#include<graphics.h>
using namespace std;
class Queen
{
public:
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
     int x=75,y=75,NEP=0;
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    initwindow(1366,768,"OUTPUT");
    POINT mouse;
    GetCursorPos(&mouse);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(NEP==0)
            {
            setcolor(YELLOW);
            setlinestyle(3,0,4);
            setfillstyle(SOLID_FILL,BLACK);
            rectangle(x,y,x+75,y+75);
            floodfill(x+3,y+3,YELLOW);
            NEP=1;
            }
            else
            {
                setcolor(YELLOW);
                setlinestyle(3,0,4);
                setfillstyle(SOLID_FILL,WHITE);
                rectangle(x,y,x+75,y+75);
                floodfill(x+3,y+3,YELLOW);
                NEP=0;
            }
            x=x+75;
        }
        if (NEP==0)
            NEP=1;
        else
            NEP=0;
        x=75;
        y=y+75;
    }
    getch();
    closegraph();
    return 0;

    return 0;
}
