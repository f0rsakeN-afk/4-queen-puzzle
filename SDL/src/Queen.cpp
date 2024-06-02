#include "Queen.h"
#include <iostream>
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

    // Check if the provided coordinates are within valid range
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

    // Output message indicating that solution1 has been successfully passed as an argument
    cout << "Successfully passed solution1 as an argument" << endl;

    // Output the elements of the solution1 array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << solu1[i][j] << " ";
        }
        cout << endl;
    }

    // Iterate over each element of the solution1 array
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Check if the current element of the solution1 array is 1 (indicating a Queen)
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

Queen Queen::rightClick(int **arr, int a, int b)
{
    Queen temp;

    temp.x = 0;
    temp.y = 0;

    cout << "Successfully passed solution1 as an argument" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (arr[i][j] == 1)
            {
                cout << "Right click\t" << i << " " << j << endl;

                int s = ((i + 5) * 100 + 4);
                int r = ((j + 1) * 100 + 4);

                if (a == s && b == r)
                {
                    temp.x = s;
                    temp.y = r;
                    return temp;
                }
            }
        }
    }
    return temp;
}
