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
        while (row >= 0 && col >= 0)//checking the LEFT_upper diagonal.
        {
            if (board[row][col] == '1')
            {
                return false;
            }
                row--;
                col--;
        }
        col = dupcol;
        row = duprow;
        while (col >= 0)//checking for each column in a row.
        {
            if (board[row][col] == '1')
            {
                return false;
            }
                col--;
        }
        row = duprow;
        col = dupcol;
        while (col>=0 && row<N)//checking the RIGHT_upper diagonal.
        {
            if (board[row][col] == '1')
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
                board[row][col] = '1';
                Solve(col + 1, board, ans, N);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveQueen(int N)
    {
        vector<vector<string>> ans;//created a 2D-dynamic array/vector name "ans" that is going to store the strings as elements.
        vector<string> board(N);//created a vector name of "board". that has 4 size and going to store string values.
        string s(N, '.');//crreated a sring named "s" and initilize by"-".while N represents the number of occurance time.
        for (int i = 0; i < N; i++)//
        {
            board[i] = s;
        }//all the above stuffs is to create a 2D dynamic arrray named"ans" and initilized with "-".
        Solve(0, board, ans, N);//passing 0,row, 2D array,number of queen.
        return ans;//returns the vector
    }
};
int main()
{
    int N = 4;
    Queen X;
    vector<vector<string>> ans = X.solveQueen(N);
    for (int i = 0; i < ans.size(); i++)//.size() -> returns the no of elements  that is present inside of the dynamic array(vector).
    {
        for (int J = 0; J < ans[0].size(); J++)
        {
            cout << ans[i][J];
            cout << endl;
        }
        cout << endl;
    }
return 0;
}
