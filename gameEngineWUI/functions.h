#pragma once
#include <iostream>
#include <Windows.h>
//just add intro to function


void test();
void primer();
void dialogueLoop();
extern const int screenW;
extern const int screenH;
extern wchar_t *screen;

/* 
class wuiEngine
{
public:
	wuiEngine()
	{
		

		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(hConsole, screen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}
	
};
*/