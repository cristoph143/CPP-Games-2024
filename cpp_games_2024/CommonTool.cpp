#include "CommonTool.h"
#include <iostream>


// Function to display menu and handle user choices
void runMenu(const std::map<int, MenuOption>& menuOptions, int exitOption) {
    int choice = 0;
    do {
        // Display menu
        PRINT_MESSAGE("\nSelect an option:");
        for (const auto& option : menuOptions) {
            PRINT_MESSAGE("%d. %s", option.first, option.second.description.c_str());
        }
        PRINT_MESSAGE("Enter your choice: ");
        scanf_s("%d", &choice);  // Use scanf for input

        // Execute corresponding action if valid
        if (menuOptions.count(choice)) {
            menuOptions.at(choice).action();
        }
        else {
            PRINT_MESSAGE("Invalid choice. Please try again.");
        }

    } while (choice != exitOption); // Use dynamic exit option
}

// Exit application
void exitApp() {
    PRINT_MESSAGE("Exiting application...");
    exit(0);
}