#include <bits/stdc++.h>
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

    return 0;
}
