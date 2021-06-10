#pragma once

#include <Windows.h>
//just add intro to function
extern wchar_t *screen;

void test();
void primer();
extern const int screenW;
extern const int screenH;

HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten = 0;