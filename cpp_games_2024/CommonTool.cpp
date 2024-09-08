#include "CommonTool.h"
#include <iostream>
#include <chrono>   // For std::chrono
#include <thread>   // For std::this_thread::sleep_for
HMODULE loadDLL(const std::wstring& dllPath) {

    HMODULE hLib = LoadLibrary(dllPath.c_str());
    if (hLib == NULL) {
        std::wcerr << L"Failed to load " << dllPath << std::endl;
    }
    return hLib;
}

// Function to unload the DLL
void unloadDLL(HMODULE hLib) {
    if (hLib != NULL) {
        FreeLibrary(hLib);
    }
}


// Function to display menu and handle user choices
void runMenu(const std::map<int, MenuOption<>>& menuOptions, int exitOption) {
    int choice = 0;
    do {

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        clearScreen();  
        // Display menu
        PRINT_MESSAGE("Select an option:");
        for (const auto& option : menuOptions) {
            PRINT_MESSAGE("%d. %s", option.first, option.second.description.c_str());
        }
        PRINT_MESSAGE("Enter your choice: ");
        scanf_s("%d", &choice);  // Use scanf for input

        // Execute corresponding action if valid
        auto it = menuOptions.find(choice);
        if (it != menuOptions.end()) {
            it->second.action();  // Call the corresponding function
        }
        else {
            PRINT_MESSAGE("Invalid choice. Please try again.");
        }
    } while (choice != exitOption); // Use dynamic exit option
}

// Helper function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Clear screen for Windows
    #else
        system("clear");  // Clear screen for Linux/macOS
    #endif
}



// Exit application
void exitApp() {
    PRINT_MESSAGE("Exiting application...");
    exit(0);
}