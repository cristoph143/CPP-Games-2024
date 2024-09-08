#pragma once

#include <iostream>
#include <windows.h>
#include <map>
#include <string>
#include <sstream>
#include <cstdlib>
#include <functional>

using namespace std;

#define PRINT_MESSAGE(format, ...) printf(format "\n", ##__VA_ARGS__)
#define PRINT_ERROR_MESSAGE(format, ...) \
    cerr << "Error: " << format << endl, __VA_ARGS__

// Template for function pointer
template<typename Ret = void, typename... Args>
using MenuAction = function<Ret(Args...)>;

// Struct to hold menu option description and associated action
template<typename Ret = void, typename... Args>
struct MenuOption {
    string description;
    MenuAction<Ret, Args...> action;
};



template<typename T>
T loadFunction(HMODULE hLib, const char* functionName) {
    // Get the address of the function
    auto function = reinterpret_cast<T>(GetProcAddress(hLib, functionName));
    if (!function) {
        cerr << "Failed to load function: " << functionName << endl;
    }
    return function;
}


//void runMenu(const map<int, MenuOption>& menuOptions);
void runMenu(const map<int, MenuOption<>>& menuOptions, int exitOption);

void exitApp();

HMODULE loadDLL(const wstring& dllPath);

// Function to unload the DLL
void unloadDLL(HMODULE hLib);