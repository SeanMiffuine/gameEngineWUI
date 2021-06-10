// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <string>
#include "functions.h"




int main()
{
	

	//screenbuffer
	
	
	SetConsoleActiveScreenBuffer(hConsole);
	

	while (1)
	{
		test();
		//finsh all render/draw
		WriteConsoleOutputCharacter(hConsole, screen, screenW * screenH, { 0,0 }, &dwBytesWritten);

	}


}

