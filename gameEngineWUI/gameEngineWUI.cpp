// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <algorithm>
#include <chrono>
#include "functions.h"

const int screenW = 120;
const int screenH = 30;

extern wchar_t *screen = new wchar_t[screenW*screenH];
extern wchar_t *dialogueScreen = new wchar_t[screenW*screenH];

const wchar_t msg[] = L"abcdefg";
int size = sizeof(msg) / sizeof(msg[0]);

int main()
{
	while (1)
	{
		dialogueLoop();
		primer();
		test();
	}
}

void dialogueLoop()
{
	HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hDialogue);
	DWORD dwBytesWritten = 0;

	WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);

}

void test()
{
	int size = sizeof(msg) / sizeof(msg[0]); // int of characters in array
	for (int i = 0; i < size; i++)
	{
		dialogueScreen[i] = msg[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}
}

void primer()
{
	std::fill_n(dialogueScreen, (screenW * screenH), ' ');
}
