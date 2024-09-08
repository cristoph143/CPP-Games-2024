//#pragma once
//
//// The following ifdef block is the standard way of creating macros which make exporting
//// from a DLL simpler. All files within this DLL are compiled with the SUDOKULIBRARY_EXPORTS
//// symbol defined on the command line. This symbol should not be defined on any project
//// that uses this DLL. This way any other project whose source files include this file see
//// SUDOKULIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
//// defined with this macro as being exported.
//#ifdef SUDOKULIBRARY_EXPORTS
//#define SUDOKULIBRARY_API __declspec(dllexport)
//#else
//#define SUDOKULIBRARY_API __declspec(dllimport)
//#endif
//
//#include <algorithm>
//#include <random>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//typedef int Grid[9][9];
//
//
//// This class is exported from the dll
////class SUDOKULIBRARY_API Csudokulibrary {
////public:
////    typedef Csudokulibrary* (*CreateLibraryInstance)();
////    typedef void (*GenerateSudokuFunc)(int[9][9]);
////    typedef bool (*IsValidMoveFunc)(int[9][9], int, int, int);
////    typedef void (*RemoveNumbersFunc)(int[9][9], int);
////private:
////	// Private helper methods
////	void shuffleArray(vector<int>& arr);  // Internal shuffling logic
////	bool generateBoard(Grid grid, int row, int col);  // Board generation logic
////public:
////    Csudokulibrary(void);
////    void generateSudoku(Grid grid);
////    bool isValidMove(Grid grid, int row, int col, int num);
////    void removeNumbers(Grid grid, int blanks);
////};
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//    // Exported functions
//    SUDOKULIBRARY_API void generateSudoku(Grid grid);
//    SUDOKULIBRARY_API bool isValidMove(Grid grid, int row, int col, int num);
//    SUDOKULIBRARY_API void removeNumbers(Grid grid, int blanks);
//
//    // Library management functions
//    SUDOKULIBRARY_API Csudokulibrary* CreateLibraryInstance();
//    SUDOKULIBRARY_API void DestroyLibraryInstance(Csudokulibrary* instance);
//
//#ifdef __cplusplus
//}
//#endif
//extern SUDOKULIBRARY_API int nsudokulibrary;
//
//SUDOKULIBRARY_API int fnsudokulibrary(void);

#pragma once

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

#ifdef __cplusplus
extern "C" {
#endif

    // Exported functions for generating, validating, and removing numbers from the Sudoku grid
    SUDOKULIBRARY_API void generateSudoku(Grid grid);
    SUDOKULIBRARY_API bool isValidMove(Grid grid, int row, int col, int num);
    SUDOKULIBRARY_API void removeNumbers(Grid grid, int blanks);

    // Library management functions for creating and destroying an instance
    SUDOKULIBRARY_API void* CreateLibraryInstance();
    SUDOKULIBRARY_API void DestroyLibraryInstance(void* instance);

#ifdef __cplusplus
}
#endif

// Exported variable
extern SUDOKULIBRARY_API int nsudokulibrary;

// Example exported function
SUDOKULIBRARY_API int fnsudokulibrary(void);
