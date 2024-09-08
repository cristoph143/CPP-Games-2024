#pragma once
#include "CommonTool.h"
#include "../sudoku_library/sudoku_library.h"

typedef int Grid[9][9];

typedef Csudokulibrary* (*CreateLibraryInstance)();
typedef void (*GenerateSudokuFunc)(int[9][9]);
typedef bool (*IsValidMoveFunc)(int[9][9], int, int, int);
typedef void (*RemoveNumbersFunc)(int[9][9], int);


// Function to run the Sudoku game
int runSudokuGame();