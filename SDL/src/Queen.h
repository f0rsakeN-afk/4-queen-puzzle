// The following preprocessor directives ensure that the contents of this file are included only once,
// even if the header file is included multiple times in various files. This prevents redefinition errors.
#ifndef QUEEN_H // Check if QUEEN_H is not defined
#define QUEEN_H // Define QUEEN_H to prevent multiple inclusions

// Declaration of the Queen class
class Queen
{
public:
    int x, y; // Public member variables to store the position of the Queen

    // Member function to get the cell at coordinates (a, b)
    Queen getTheCell(int a, int b);

    // Member function to handle a left-click event at coordinates (a, b) on a 4x4 solution array
    Queen leftClick(int solu1[4][4], int a, int b);

    // Member function to handle a right-click event at coordinates (a, b) on a dynamically allocated 2D array
    Queen rightClick(int **arr, int a, int b);

    // Member function to check if placing a Queen at coordinates (x, y) on a dynamically allocated 2D array is safe
    bool isSafe(int **arr, int x, int y, int n);

    // Member function to solve the n-Queen problem on a dynamically allocated 2D array starting from coordinates (x, y)
    bool nQueen(int **arr, int x, int y);

    // Member function to handle invalid operations
    void invalid();
};

#endif // End of include guard for QUEEN_H
