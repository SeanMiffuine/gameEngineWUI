#pragma once
#include <iostream>
#include <Windows.h>

//add function type, name, and inputs
// as well include ".h" in both function file to call from and main file (using);

extern const wchar_t msg[];
extern const wchar_t msga[];

extern const wchar_t one[];
extern const wchar_t two[];
extern const wchar_t three[];

extern const wchar_t select1[];
extern const wchar_t select2[];
extern const wchar_t select3[];
extern const wchar_t select4[];



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