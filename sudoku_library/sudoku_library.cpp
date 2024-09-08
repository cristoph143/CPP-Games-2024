// sudoku_library.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "sudoku_library.h"


// This is an example of an exported variable
SUDOKULIBRARY_API int nsudokulibrary=0;

void generateSudoku(Grid grid)
{
}

bool isValidMove(Grid grid, int row, int col, int num)
{
    return false;
}

void removeNumbers(Grid grid, int blanks)
{
}

// This is an example of an exported function.
SUDOKULIBRARY_API int fnsudokulibrary(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Csudokulibrary::Csudokulibrary()
{
    return;
}

void Csudokulibrary::generateSudoku(Grid grid)
{
    // Initialize the grid
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            grid[row][col] = 0;
        }
    }

    // Generate the board using backtracking
    generateBoard(grid, 0, 0);
}

void Csudokulibrary::shuffleArray(vector<int>& arr)
{
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);
}

bool Csudokulibrary::isValidMove(Grid grid, int row, int col, int num)
{
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

bool Csudokulibrary::generateBoard(Grid grid, int row, int col)
{
    if (row == 9) return true;
    if (col == 9) return generateBoard(grid, row + 1, 0);
    if (grid[row][col] != 0) return generateBoard(grid, row, col + 1);

    vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    shuffleArray(numbers);

    for (int num : numbers) {
        if (isValidMove(grid, row, col, num)) {
            grid[row][col] = num;
            if (generateBoard(grid, row, col + 1)) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void Csudokulibrary::removeNumbers(Grid grid, int blanks)
{
    random_device rd;
    mt19937 g(rd());

    int count = blanks;
    while (count > 0) {
        int row = g() % 9;
        int col = g() % 9;

        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            count--;
        }
    }
}
