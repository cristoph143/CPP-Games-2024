#pragma once

#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#define PRINT_MESSAGE(format, ...) printf(format "\n", ##__VA_ARGS__)
#define PRINT_ERROR_MESSAGE(format, ...) \
    std::cerr << "Error: " << format << std::endl, __VA_ARGS__
// Function pointer typedefs for dynamic functions
typedef void (*MenuAction)();

// Struct to hold menu option description and associated action
struct MenuOption {
    string description;
    MenuAction action;
};

//void runMenu(const map<int, MenuOption>& menuOptions);
void runMenu(const map<int, MenuOption>& menuOptions, int exitOption);

void exitApp();