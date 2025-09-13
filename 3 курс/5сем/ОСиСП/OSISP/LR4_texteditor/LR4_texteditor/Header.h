#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>

// √лобальные переменные
extern bool fileSaved;
extern HANDLE mutex;
extern HWND hEditControl;
extern HWND hStaticControl;
extern HDC hdcStatic;
extern HFONT fontRectangle;
extern HFONT fontStatic;
extern RECT windowRectangle;
extern COLORREF fontColor;
extern int colorR, colorG, colorB;
extern OPENFILENAMEA ofn;
extern char filename[260];
extern PAINTSTRUCT ps;
extern const int TextBufferSize;
extern char Buffer[1024];

// ќбъ€влени€ функций
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
void SetOpenFileParams(HWND hWnd);
void SaveDataThread(LPCSTR path);
void LoadDataThread(LPCSTR path);

#endif
