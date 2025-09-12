#pragma once
#include <iostream>
#include <string>
#include <conio.h>

#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

extern "C" DLL1_API int   __stdcall inputArraySize(std::string input);
extern "C" DLL1_API double   __stdcall inputElementArray(int p, int q, int size_row, int size_col);
extern "C" DLL1_API double*  __stdcall inputArray(double* array, int array_size_row, int array_size_col);
extern "C" DLL1_API void  __stdcall outputArray(double* array, int array_size_row, int array_size_col);
extern "C" DLL1_API bool  __stdcall rec(double* array, int size_low, int size_high);