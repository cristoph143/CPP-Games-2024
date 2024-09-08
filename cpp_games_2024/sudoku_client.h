#pragma once
#include "CommonTool.h"
#include <string>


typedef int Grid[9][9];

// Define function pointer types for Sudoku operations
typedef void (*GenerateSudokuFunc)(Grid grid);
typedef bool (*IsValidMoveFunc)(Grid grid, int row, int col, int num);
typedef void (*RemoveNumbersFunc)(Grid grid, int blanks);

// Define function pointer types for library management
typedef void* (*CreateLibraryInstanceFunc)();
typedef void (*DestroyLibraryInstanceFunc)(void* instance);

struct SudokuSettings {
    string sudokuType;
    bool timerEnabled;
    string difficulty;
};

extern SudokuSettings settings;


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

    static SudokuClient& getInstance() {
        static SudokuClient instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

    // Accessor methods
    string getSudokuType() const { return settings.sudokuType; }

    bool isTimerEnabled() const { return settings.timerEnabled; }
    void setTimerEnabled(bool enabled) { settings.timerEnabled = enabled; }

    string getDifficulty() const { return settings.difficulty; }

    void setSudokuType(const string& type);
    void setDifficulty(const string& difficulty);
    void setTimer(bool enable);

    bool loadLibrary();
    void unloadLibrary();

    void generatePuzzle(Grid grid);
    bool checkMove(Grid grid, int row, int col, int num);
    void makePuzzle(Grid grid, int blanks);

    void play_sudoku();
    void settings_sudoku();
    void quit_sudoku();

    void select_sudoku_type();
    void select_timer();
    void select_difficulty();

    // Show Sudoku types menu
    void showSudokuTypes();
    void showTimerOptions();
    void showDifficultyOptions();

    void enable_timer();
    void disable_timer();
    void set_difficulty(const string& difficulty);
};



