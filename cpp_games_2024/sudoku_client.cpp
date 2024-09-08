#include "sudoku_client.h"
#include "CommonTool.h"

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

// Define the menu options for Sudoku types with lambda functions
map<int, MenuOption<>> sudokuTypeMenuOptions = 
{
    {1, {"Classic Sudoku", [&]() { 
        settings.sudokuType = "Classic"; 
        PRINT_MESSAGE("Set Sudoku Type to Classic"); 
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {2, {"Mini Sudoku", [&]() { 
        settings.sudokuType = "Mini"; 
        PRINT_MESSAGE("Set Sudoku Type to Mini");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {3, {"Samurai Sudoku", [&]() { 
        settings.sudokuType = "Samurai"; 
        PRINT_MESSAGE("Set Sudoku Type to Samurai");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {4, {"Hyper Sudoku", [&]() { 
        settings.sudokuType = "Hyper"; 
        PRINT_MESSAGE("Set Sudoku Type to Hyper");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {5, {"Killer Sudoku", [&]() { 
        settings.sudokuType = "Killer"; 
        PRINT_MESSAGE("Set Sudoku Type to Killer");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {6, {"Jigsaw Sudoku", [&]() { 
        settings.sudokuType = "Jigsaw"; 
        PRINT_MESSAGE("Set Sudoku Type to Jigsaw");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {7, {"Word Sudoku", [&]() { 
        settings.sudokuType = "Word"; 
        PRINT_MESSAGE("Set Sudoku Type to Word");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {8, {"Diagonal Sudoku", [&]() { 
        settings.sudokuType = "Diagonal"; 
        PRINT_MESSAGE("Set Sudoku Type to Diagonal");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {9, {"Sudoku X", [&]() { 
        settings.sudokuType = "Sudoku X"; 
        PRINT_MESSAGE("Set Sudoku Type to Sudoku X");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {10, {"Sudoku with Constraints", [&]() { 
        settings.sudokuType = "Constraints"; 
        PRINT_MESSAGE("Set Sudoku Type to Constraints");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {11, {"Multi-Sudoku", [&]() { 
        settings.sudokuType = "Multi"; 
        PRINT_MESSAGE("Set Sudoku Type to Multi");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {12, {"Sudoku with Symmetry", [&]() { 
        settings.sudokuType = "Symmetry"; 
        PRINT_MESSAGE("Set Sudoku Type to Symmetry");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {0, {"Back to Settings Menu", [&]() { 
        runMenu(settingsMenuOptions, 0); 
    }}}
};
// Define the menu options for difficulty settings with lambda functions
map<int, MenuOption<>> difficultyMenuOptions = {
    {1, {"Easy", [&]() { 
        settings.difficulty = "Easy"; 
        PRINT_MESSAGE("Difficulty set to Easy");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {2, {"Normal", [&]() { 
        settings.difficulty = "Normal"; 
        PRINT_MESSAGE("Difficulty set to Normal"); 
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {3, {"Hard", [&]() { 
        settings.difficulty = "Hard"; 
        PRINT_MESSAGE("Difficulty set to Hard");
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {0, {"Back to Settings Menu", [&]() { 
        runMenu(settingsMenuOptions, 0); 
    }}}
};
// Define the menu options for timer settings with lambda functions
map<int, MenuOption<>> timerMenuOptions = {
    {1, {"Enable Timer", [&]() { 
        sudokuClient.enable_timer(); 
        PRINT_MESSAGE("Timer Enabled"); 
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {2, {"Disable Timer", [&]() { 
        sudokuClient.disable_timer(); 
        PRINT_MESSAGE("Timer Disabled"); 
        runMenu(settingsMenuOptions, 0);  // Return to settings menu
    }}},
    {0, {"Back to Sudoku Type Menu", [&]() { 
        runMenu(sudokuTypeMenuOptions, 0); 
    }}}
};
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
