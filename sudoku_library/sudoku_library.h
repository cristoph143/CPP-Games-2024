#pragma once

// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SUDOKULIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SUDOKULIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SUDOKULIBRARY_EXPORTS
#define SUDOKULIBRARY_API __declspec(dllexport)
#else
#define SUDOKULIBRARY_API __declspec(dllimport)
#endif

#include <algorithm>
#include <random>
#include <iostream>
#include <vector>

using namespace std;
typedef int Grid[9][9];

// This class is exported from the dll
class SUDOKULIBRARY_API Csudokulibrary {

private:
	// Private helper methods
	void shuffleArray(vector<int>& arr);  // Internal shuffling logic
	bool generateBoard(Grid grid, int row, int col);  // Board generation logic
public:
    Csudokulibrary(void);
    void generateSudoku(Grid grid);
    bool isValidMove(Grid grid, int row, int col, int num);
    void removeNumbers(Grid grid, int blanks);
};

// The following extern functions replace the methods of the Csudokulibrary class
extern "C" {
    // Function declarations to replace the class methods
    SUDOKULIBRARY_API void generateSudoku(Grid grid);
    SUDOKULIBRARY_API bool isValidMove(Grid grid, int row, int col, int num);
    SUDOKULIBRARY_API void removeNumbers(Grid grid, int blanks);
}

extern SUDOKULIBRARY_API int nsudokulibrary;

SUDOKULIBRARY_API int fnsudokulibrary(void);
