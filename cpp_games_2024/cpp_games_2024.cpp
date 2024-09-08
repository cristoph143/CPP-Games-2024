// cpp_games_2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cpp_games_2024.h"
#include "CommonTool.h"
#include "sudoku_client.h"
#include <map>

int main()
{
    // Define the menu options with their descriptions and associated actions
    map<int, MenuOption<void>> menuOptions = {
        {1, {"Sudoku", run_sudoku_menu}},
        {2, {"Hello World", hello_world}},
        {0, {"Exit", exitApp}}
    };
    // Run the dynamic menu
    // Pass the exit option number to runMenu
    runMenu(menuOptions, 0); // 0 is the exit option number

    return 0;
}

void hello_world()
{
    PRINT_MESSAGE("Hello, World!");
}

void run_sudoku_menu() {
    SudokuClient sudokuClient;
    // Define the menu options with their descriptions and associated actions
    map<int, MenuOption<void>> menuOptions = {
        {1, {"Play", [&]() { sudokuClient.play_sudoku(); }}},
        {2, {"Settings", [&]() { sudokuClient.settings_sudoku(); }}},
        {0, {"Quit", [&]() { sudokuClient.quit_sudoku(); }}}
    };

    // Run the dynamic menu
    // Pass the exit option number to runMenu
    runMenu(menuOptions, 0); // 0 is the exit option number
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


