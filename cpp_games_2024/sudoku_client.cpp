#include "sudoku_client.h"
#include "CommonTool.h"

#include <chrono>   // For std::chrono
#include <thread>   // For std::this_thread::sleep_for
// Constructor: Initialize library handle to null
SudokuClient::SudokuClient() : hInstLibrary(nullptr),
createLibraryInstance(nullptr),
destroyLibraryInstance(nullptr),
generateSudoku(nullptr),
isValidMove(nullptr),
removeNumbers(nullptr) {}

SudokuClient sudokuClient;

// Initialization of the global settings variable
SudokuSettings settings = {
    "Classic",    // sudokuType
    false,        // timerEnabled
    "Easy"        // difficulty
};



// Define the menu options for the main menu with lambda functions
map<int, MenuOption<>> mainMenuOptions = {
    {1, {"Playdoku", [&]() { sudokuClient.play_sudoku(); }}},
    {2, {"Settings", [&]() { sudokuClient.settings_sudoku(); }}},
    {0, {"Quit", [&]() { sudokuClient.quit_sudoku(); }}}
};


map<int, MenuOption<>> settingsMenuOptions = {
    {1, {"Select Sudoku Type", [&]() { sudokuClient.select_sudoku_type(); }}},
    {2, {"Select Timer", [&]() { sudokuClient.select_timer(); }}},
    {3, {"Select Difficulty", [&]() { sudokuClient.select_difficulty(); }}},
    {0, {"Back to Main Menu", [&]() { runMenu(mainMenuOptions, 0); }}}
};

// Define the menu options for Sudoku types using the helper function
map<int, MenuOption<>> sudokuTypeMenuOptions = {
    {1, {"Classic Sudoku", [&]() { sudokuClient.setSudokuType("Classic"); }}},
    {2, {"Mini Sudoku", [&]() { sudokuClient.setSudokuType("Mini"); }}},
    {3, {"Samurai Sudoku", [&]() { sudokuClient.setSudokuType("Samurai"); }}},
    {4, {"Hyper Sudoku", [&]() { sudokuClient.setSudokuType("Hyper"); }}},
    {5, {"Killer Sudoku", [&]() { sudokuClient.setSudokuType("Killer"); }}},
    {6, {"Jigsaw Sudoku", [&]() { sudokuClient.setSudokuType("Jigsaw"); }}},
    {7, {"Word Sudoku", [&]() { sudokuClient.setSudokuType("Word"); }}},
    {8, {"Diagonal Sudoku", [&]() { sudokuClient.setSudokuType("Diagonal"); }}},
    {9, {"Sudoku X", [&]() { sudokuClient.setSudokuType("Sudoku X"); }}},
    {10, {"Sudoku with Constraints", [&]() { sudokuClient.setSudokuType("Constraints"); }}},
    {11, {"Multi-Sudoku", [&]() { sudokuClient.setSudokuType("Multi"); }}},
    {12, {"Sudoku with Symmetry", [&]() { sudokuClient.setSudokuType("Symmetry"); }}},
    {0, {"Back to Settings Menu", [&]() { runMenu(settingsMenuOptions, 0); }}}
};

// Define the menu options for difficulty using the helper function
map<int, MenuOption<>> difficultyMenuOptions = {
    {1, {"Easy", [&]() { sudokuClient.setDifficulty("Easy"); }}},
    {2, {"Normal", [&]() { sudokuClient.setDifficulty("Normal"); }}},
    {3, {"Hard", [&]() { sudokuClient.setDifficulty("Hard"); }}},
    {0, {"Back to Settings Menu", [&]() { runMenu(settingsMenuOptions, 0); }}}
};
// Define the menu options for timer settings with lambda functions
map<int, MenuOption<>> timerMenuOptions = {
    {1, {"Enable Timer", [&]() {
        sudokuClient.setTimer(true);  // Call setTimer to enable the timer
    }}},
    {2, {"Disable Timer", [&]() {
        sudokuClient.setTimer(false);  // Call setTimer to disable the timer
    }}},
    {0, {"Back to Settings Menu", [&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        clearScreen();
        runMenu(settingsMenuOptions, 0); // Return to settings menu
    }}}
};
// Helper function for setting Sudoku type
void SudokuClient::setSudokuType(const string& type) {
    settings.sudokuType = type;
    PRINT_MESSAGE("Set Sudoku Type to %s", type.c_str());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen();
    runMenu(settingsMenuOptions, 0);  // Return to settings menu
}


// Helper function for setting the timer
void SudokuClient::setTimer(bool enable) {
    settings.timerEnabled = enable;  // Update the timerEnabled status

    if (enable) {
        enable_timer();
        PRINT_MESSAGE("Timer Enabled");
    }
    else {
        disable_timer();
        PRINT_MESSAGE("Timer Disabled");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen(); // Clear the screen
    runMenu(settingsMenuOptions, 0);  // Return to settings menu
}
// Helper function for setting difficulty
void SudokuClient::setDifficulty(const string& difficulty) {
    settings.difficulty = difficulty;
    PRINT_MESSAGE("Difficulty set to %s", difficulty.c_str());

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    clearScreen();
    runMenu(settingsMenuOptions, 0);  // Return to settings menu
}

// Destructor: Unload the library if it's loaded
SudokuClient::~SudokuClient() {
    unloadLibrary();
}

// Show Sudoku types menu
void SudokuClient::showSudokuTypes() {
    runMenu(sudokuTypeMenuOptions, 0);
}

// Show timer options menu
void SudokuClient::showTimerOptions() {
    runMenu(timerMenuOptions, 0);
}

// Show difficulty options menu
void SudokuClient::showDifficultyOptions() {
    runMenu(difficultyMenuOptions, 0);
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

// Define functions for Sudoku actions
void SudokuClient::play_sudoku() {
    std::cout << "Starting " << settings.sudokuType << " Sudoku with "
        << (settings.timerEnabled ? "Timer Enabled" : "Timer Disabled") << " and Difficulty: "
        << settings.difficulty << "\n";

    //if (sudokuClient.loadLibrary()) {
    //    Grid grid;

    //    // Generate a new Sudoku puzzle
    //    sudokuClient.generatePuzzle(grid);

    //    // Remove numbers to create blanks
    //    sudokuClient.makePuzzle(grid, 20);

    //    // Check if a move is valid
    //    if (sudokuClient.checkMove(grid, 0, 0, 5)) {
    //        PRINT_MESSAGE("Move is valid.");
    //    }
    //    else {
    //        PRINT_MESSAGE("Move is invalid.");
    //    }

    //    sudokuClient.unloadLibrary();
    //}
}

void SudokuClient::enable_timer()
{
    PRINT_MESSAGE("Timer enabled.");
    // Add code to enable the timer
}

void SudokuClient::disable_timer()
{
    PRINT_MESSAGE("Timer disabled.");
    // Add code to disable the timer
}

void SudokuClient::set_difficulty(const string& difficulty)
{
    PRINT_MESSAGE("Difficulty set to: %s", difficulty.c_str());
    // Add code to set the difficulty level
}

void SudokuClient::settings_sudoku() {
    runMenu(settingsMenuOptions, 0);
}

void SudokuClient::quit_sudoku() {
    PRINT_MESSAGE("Quitting Sudoku Menu...");
    // Add functionality to handle quitting the Sudoku submenu
}

void SudokuClient::select_sudoku_type() {
    PRINT_MESSAGE("Current Sudoku Type: %s", settings.sudokuType.c_str());
    runMenu(sudokuTypeMenuOptions, 0);
}

void SudokuClient::select_timer() {
    PRINT_MESSAGE("Timer is %s", (settings.timerEnabled ? "Enabled" : "Disabled"));
    runMenu(timerMenuOptions, 0);
}

void SudokuClient::select_difficulty() {
    PRINT_MESSAGE("Current Difficulty: %s", settings.difficulty.c_str());
    runMenu(difficultyMenuOptions, 0);
}
