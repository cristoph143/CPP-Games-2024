#include "sudoku_client.h"
#include "CommonTool.h"

int runSudokuGame()
{
    std::wstring dllPath = L"sudokulibrary.dll";  // Path to your DLL
    HMODULE hInstLibrary = loadDLL(dllPath);
    if (!hInstLibrary) {
        return 1;  // Exit if DLL fails to load
    }

    // Load functions
    auto createLibraryInstance = loadFunction<Csudokulibrary * (*)()>(hInstLibrary, "CreateLibraryInstance");
    auto destroyLibraryInstance = loadFunction<void(*)(Csudokulibrary*)>(hInstLibrary, "DestroyLibraryInstance");
    auto generateSudoku = loadFunction<GenerateSudokuFunc>(hInstLibrary, "generateSudoku");
    auto isValidMove = loadFunction<IsValidMoveFunc>(hInstLibrary, "isValidMove");
    auto removeNumbers = loadFunction<RemoveNumbersFunc>(hInstLibrary, "removeNumbers");



    if (!createLibraryInstance || !generateSudoku || !isValidMove || !removeNumbers) {
        std::cerr << "Failed to load necessary functions from the DLL" << std::endl;
        unloadDLL(hInstLibrary);
        return 1;
    }

    // Create the library instance
    Csudokulibrary* library = createLibraryInstance();
    if (!library) {
        std::cerr << "Failed to create library instance" << std::endl;
        unloadDLL(hInstLibrary);
        return 1;
    }

    // Create the grid
    Grid grid = { 0 };

    // Generate Sudoku
    library->generateSudoku(grid);

    // Remove some numbers to create the puzzle
    library->removeNumbers(grid, 40);

    // Display the generated grid
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << (grid[i][j] ? grid[i][j] : '.') << " ";
        }
        std::cout << std::endl;
    }

    // Example: Checking if a move is valid
    int row = 0, col = 0, num = 5;
    if (library->isValidMove(grid, row, col, num)) {
        std::cout << "Valid move!" << std::endl;
    }
    else {
        std::cout << "Invalid move." << std::endl;
    }

    // Clean up
    delete library;
    unloadDLL(hInstLibrary);

    return 0;
}
