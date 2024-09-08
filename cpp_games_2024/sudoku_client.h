#pragma once
#include "CommonTool.h"
#include "../sudoku_library/sudoku_library.h"

typedef int Grid[9][9];

//typedef Csudokulibrary* (*CreateLibraryInstance)();
//typedef void (*GenerateSudokuFunc)(int[9][9]);
//typedef bool (*IsValidMoveFunc)(int[9][9], int, int, int);
//typedef void (*RemoveNumbersFunc)(int[9][9], int);


// Function to run the Sudoku game
//int runSudokuGame();

// Define function pointer types for Sudoku operations
typedef void (*GenerateSudokuFunc)(Grid grid);
typedef bool (*IsValidMoveFunc)(Grid grid, int row, int col, int num);
typedef void (*RemoveNumbersFunc)(Grid grid, int blanks);

// Define function pointer types for library management
typedef void* (*CreateLibraryInstanceFunc)();
typedef void (*DestroyLibraryInstanceFunc)(void* instance);

// Class to manage loading and using the Sudoku library
class SudokuClient {
private:
    HINSTANCE hInstLibrary;
    CreateLibraryInstanceFunc createLibraryInstance;
    DestroyLibraryInstanceFunc destroyLibraryInstance;
    GenerateSudokuFunc generateSudoku;
    IsValidMoveFunc isValidMove;
    RemoveNumbersFunc removeNumbers;

public:
    SudokuClient();
    ~SudokuClient();

    bool loadLibrary();
    void unloadLibrary();

    void generatePuzzle(Grid grid);
    bool checkMove(Grid grid, int row, int col, int num);
    void makePuzzle(Grid grid, int blanks);
};
