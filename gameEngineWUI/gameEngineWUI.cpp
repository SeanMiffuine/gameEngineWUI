// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include "functions.h"

extern const int screenW = 120;
extern const int screenH = 30;
//extern wchar_t *screen = new wchar_t[screenW*screenH];

int main()
{
	wuiEngine game;
	
	while (1)
	{
		
		game.dialogue();
		dialogueLoop(game);
		

	}


}

