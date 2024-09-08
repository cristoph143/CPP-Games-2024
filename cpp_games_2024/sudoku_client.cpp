#include "sudoku_client.h"
#include "CommonTool.h"

// Constructor: Initialize library handle to null
SudokuClient::SudokuClient() : hInstLibrary(nullptr),
createLibraryInstance(nullptr),
destroyLibraryInstance(nullptr),
generateSudoku(nullptr),
isValidMove(nullptr),
removeNumbers(nullptr) {}

// Destructor: Unload the library if it's loaded
SudokuClient::~SudokuClient() {
    unloadLibrary();
}

// Function to load the DLL and retrieve the necessary function pointers
bool SudokuClient::loadLibrary() {
    // Load the Sudoku library DLL
    hInstLibrary = LoadLibrary(L"sudokulibrary.dll");
    if (!hInstLibrary) {
        std::cerr << "Failed to load Sudoku DLL." << std::endl;
        return false;
    }

    // Load the required functions
    createLibraryInstance = (CreateLibraryInstanceFunc)GetProcAddress(hInstLibrary, "CreateLibraryInstance");
    destroyLibraryInstance = (DestroyLibraryInstanceFunc)GetProcAddress(hInstLibrary, "DestroyLibraryInstance");
    generateSudoku = (GenerateSudokuFunc)GetProcAddress(hInstLibrary, "generateSudoku");
    isValidMove = (IsValidMoveFunc)GetProcAddress(hInstLibrary, "isValidMove");
    removeNumbers = (RemoveNumbersFunc)GetProcAddress(hInstLibrary, "removeNumbers");

    // Check if all functions are loaded successfully
    if (!createLibraryInstance || !destroyLibraryInstance || !generateSudoku || !isValidMove || !removeNumbers) {
        std::cerr << "Failed to load necessary functions from the Sudoku DLL." << std::endl;
        unloadLibrary();
        return false;
    }

    return true;
}

// Function to unload the DLL and reset function pointers
void SudokuClient::unloadLibrary() {
    if (hInstLibrary) {
        // Destroy the library instance (if necessary)
        if (destroyLibraryInstance) {
            void* instance = createLibraryInstance();
            destroyLibraryInstance(instance);
        }

        // Free the library
        FreeLibrary(hInstLibrary);
        hInstLibrary = nullptr;
    }
}

// Wrapper to generate a Sudoku puzzle
void SudokuClient::generatePuzzle(Grid grid) {
    if (generateSudoku) {
        generateSudoku(grid);
    }
}

// Wrapper to check if a move is valid
bool SudokuClient::checkMove(Grid grid, int row, int col, int num) {
    if (isValidMove) {
        return isValidMove(grid, row, col, num);
    }
    return false;
}

// Wrapper to remove numbers from the Sudoku grid to create a puzzle
void SudokuClient::makePuzzle(Grid grid, int blanks) {
    if (removeNumbers) {
        removeNumbers(grid, blanks);
    }
}
