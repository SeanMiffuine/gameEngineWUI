#include <iostream>
#include "functions.h"
#include <algorithm>
#include <thread>
#include <chrono>
#include <Windows.h>

//funcitons - 

const wchar_t msg[] = L"abcdefg";
int size = sizeof(msg) / sizeof(msg[0]);


void test()
{
	int size = sizeof(msg) / sizeof(msg[0]); // int of characters in array
	for (int i = 0; i < size; i++)
	{
		screen[i] = msg[i];
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		WriteConsoleOutputCharacter(hConsole, screen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}
}

void primer()
{
	std::fill_n(screen, (screenW * screenH), ' ');
}