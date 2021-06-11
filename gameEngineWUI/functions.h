#pragma once
#include <iostream>
#include <Windows.h>
//just add intro to function


void test();
void primer();

extern const int screenW;
extern const int screenH;
//extern wchar_t *dialogueScreen;


class wuiEngine
{
public:

	wchar_t *dialogueScreen = new wchar_t[screenW*screenH];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	wuiEngine()
	{
		
	}

	void dialogue() //set to dialogue scene
	{
		SetConsoleActiveScreenBuffer(hDialogue);
		DWORD dwBytesWritten = 0;
		WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}

	
};

void dialogueLoop(wuiEngine game);