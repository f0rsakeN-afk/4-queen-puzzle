#include "Queen.h"
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

// Member function definition for getting the cell at coordinates (a, b)
Queen Queen::getTheCell(int a, int b)
{
    // Update the member variables with the provided coordinates
    x = a;
    y = b;

    // Calculate the block indices based on provided coordinates
    int m = a / 100;
    int n = b / 100;

    // Create a temporary Queen object
    Queen temp;

    // Check if the provided coordinates are within the valid range
    if (x >= 100 * m && x < 100 * (m + 1) && y >= 100 * n && y < 100 * (n + 1))
    {
        // Set the coordinates of the temporary Queen object to the center of the block
        temp.x = 100 * m + 4;
        temp.y = 100 * n + 4;
        return temp; // Return the temporary Queen object
    }

    // Return an empty Queen object if the coordinates are invalid
    return temp;
}

// Member function definition for handling left-click events on a 4x4 solution array
Queen Queen::leftClick(int solu1[4][4], int a, int b)
{
    // Create a temporary Queen object
    Queen temp;

    // Initialize coordinates of the temporary Queen object to (0, 0)
    temp.x = 0;
    temp.y = 0;

    // Output message indicating that solu1 has been successfully passed as an argument
    cout << "Successfully passed solu1 as an argument" << endl;

    // Output the elements of the solu1 array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << solu1[i][j] << " ";
        }
        cout << endl;
    }

    // Iterate over each element of the solu1 array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Check if the current element of the solu1 array is 1 (indicating a Queen)
            if (solu1[i][j] == 1)
            {
                // Output message indicating left-click event and corresponding coordinates
                cout << "Left click\t" << i << " " << j << endl;

                // Calculate the expected coordinates of the left-click event
                int s = ((i + 5) * 100) + 4;
                int r = ((j + 1) * 100) + 4;

                // Check if the provided coordinates match the expected coordinates
                if (a == s && b == r)
                {
                    // Update coordinates of the temporary Queen object
                    temp.x = s;
                    temp.y = r;
                    return temp; // Return the temporary Queen object
                }
            }
        }
    }

    // Return an empty Queen object if the left-click event does not match any Queen position
    return temp;
}

// Member function definition for handling right-click events on a dynamic 2D array
Queen Queen::rightClick(int **arr, int a, int b)
{
    // Create a temporary Queen object
    Queen temp;

    // Initialize coordinates of the temporary Queen object to (0, 0)
    temp.x = 0;
    temp.y = 0;

    // Output message indicating that arr has been successfully passed as an argument
    cout << "Successfully passed arr as an argument" << endl;

    // Output the elements of the arr array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Iterate over each element of the arr array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Check if the current element of the arr array is 1 (indicating a Queen)
            if (arr[i][j] == 1)
            {
                // Output message indicating right-click event and corresponding coordinates
                cout << "Right click\t" << i << " " << j << endl;

                // Calculate the expected coordinates of the right-click event
                int s = ((i + 5) * 100 + 4);
                int r = ((j + 1) * 100 + 4);

                // Check if the provided coordinates match the expected coordinates
                if (a == s && b == r)
                {
                    // Update coordinates of the temporary Queen object
                    temp.x = s;
                    temp.y = r;
                    return temp; // Return the temporary Queen object
                }
            }
        }
    }

    // Return an empty Queen object if the right-click event does not match any Queen position
    return temp;
}

// Member function definition to check if placing a Queen at (x, y) is safe
bool Queen::isSafe(int **arr, int x, int y, int n)
{
    // Check the column for any Queens
    for (int row = 0; row < 4; row++)
    {
        if (arr[row][y] == 1)
        {
            return false;
        }
    }

    // Check the upper left diagonal for any Queens
    int row = x, col = y;
    while (row >= 0 && col >= 0)
    {
        if (arr[row][col] == 1)
        {
            return false;
        }
        row--;
        col--;
    }

    // Check the upper right diagonal for any Queens
    row = x;
    col = y;
    while (row >= 0 && col < 4)
    {
        if (arr[row][col] == 1)
        {
            return false;
        }
        row--;
        col++;
    }

    // Return true if the position is safe
    return true;
}

// Member function definition to solve the N-Queen problem using backtracking
bool Queen::nQueen(int **arr, int x, int n)
{
    // If all Queens are placed, return true
    if (x >= 4)
    {
        return true;
    }

    // Try placing a Queen in each column of the current row
    for (int col = 0; col < 4; col++)
    {
        // Check if placing a Queen at (x, col) is safe
        if (isSafe(arr, x, col, n))
        {
            // Place a Queen at (x, col)
            arr[x][col] = 1;

            // Recur to place the rest of the Queens
            if (nQueen(arr, x + 1, n))
            {
                return true;
            }

            // Backtrack and remove the Queen from (x, col)
            arr[x][col] = 0;
        }
    }

    // Return false if no solution is found
    return false;
}
