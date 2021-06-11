#include <iostream>
#include "functions.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>

//funcitons - 

extern wchar_t *dialogueScreen = new wchar_t[screenW*screenH];

const wchar_t msg[] = L"abcdefg";
int size = sizeof(msg) / sizeof(msg[0]);
bool loop;



void dialogueLoop()
{
	loop = true;
	HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hDialogue);
	DWORD dwBytesWritten = 0;

	WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);

	while (loop)
	{
		primer();
		test();
		

		
	}
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