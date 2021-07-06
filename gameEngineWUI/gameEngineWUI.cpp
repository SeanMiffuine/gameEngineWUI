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

int scene;
int textProgress;
int size;
static bool skip = false;
static int textPos = 9; //text left right 10 - 80
static int rowPos = 3; // text row 4 - 26

/* list of features
-----------------------
-type speeds xxx
-wait for input to next line (++ to textProgress), enter to next line?  xxx
-putting sentences at line numbers (every 3n*120?) xxx
-UI ascii xxx

-dialogue system tempaltes
-select menu
-ascii filled in and out like cursor???
-choices
-sound FX, music etc. 
*/


class dialogueScene {
public:

	int speed;
	int lowB = (3 * 120 + 10);
	int highB = (3 * 120 + 80);
	int tempPos;

	HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD dwBytesWritten = 0;

	void talk(std::wstring msg, int speedC) // regular talkspeed
	{
		SetConsoleActiveScreenBuffer(hDialogue);
		switch (speedC)
		{
		case 1: // slow
			speed = 80000;
			break;
		case 2: // regular
			speed = 20000;
			break;
		case 3: //fast
			speed = 1;
			break;
		default:
			speed = 100;
			break;
		}

		for (int i = 0; i <= msg.length(); i++) // need primer() for when full !!!
		{
			if ((GetAsyncKeyState(VK_RETURN) < 0) != skip)
			{
				while (GetAsyncKeyState(VK_RETURN) < 0)
				{
					WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
				}
				//skip = !skip;
				for (int j = i; j <= msg.length(); j++) // !!! need primer() for when full 
				{
					if (textPos > 81)// we want dialogue to be from 10 ~ 80?
					{
						textPos = 9;
						rowPos++;
					}
					if (rowPos > 26)// rows 4 - 26
					{
						rowPos = 3;
					}
					tempPos = rowPos * 120 + textPos;
					dialogueScreen[(tempPos)] = msg[j];
					textPos++;
				}
				//i = msg.length();
				std::this_thread::sleep_for(std::chrono::microseconds(100));
				return;
			}

			if (textPos > 81)// we want dialogue to be from 10 ~ 80?
			{
				textPos = 9;
				rowPos++;
			}
			if (rowPos > 26)// rows 4 - 26
			{
				rowPos = 3;
			}
			tempPos = rowPos * 120 + textPos;
			dialogueScreen[(tempPos)] = msg[i]; //textPos is position of text going to be written.
			textPos++;
			
			//check for skip text
			
			std::this_thread::sleep_for(std::chrono::microseconds(speed));
			WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
		}	
	}

	//set screen blank / prime
	void primer()
	{
		std::fill_n(dialogueScreen, (screenW * screenH), ' ');
	}

	//sets up ui
	void ui()
	{
		//starting from row 3 to row 27, col 10 - 80
		// row 2 - 29, col 8, 82
		
		//rows render ascii 0x2592
		for(int x = 120 + 7; x <= 120 + 83; x++)
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 28 + 7; x <= 120 * 28 + 83; x++)
		{
			dialogueScreen[x] = 0x2593;
		}
		//column render
		for (int x = 120 * 2 + 6; x <= 120 * 27 + 6; x += 120)
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 84; x <= 120 * 27 + 84; x += 120)
		{
			dialogueScreen[x] = 0x2593;
		}

		// right side UI
		for (int x = 120 + 88; x <= 120 + 113; x++) //row
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 87; x <= 120 * 28 + 86; x += 120) // col
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 28 + 88; x <= 120 * 28 + 113; x++) //row 
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 114; x <= 120 * 28 + 113; x += 120) //col
		{
			dialogueScreen[x] = 0x2593;
		}


	}

	std::wstring textProgressor(int progress) // for dialogue.cpp
	{
		switch(progress)
		{
		case 1:
			return msg;
			break;
		case 2:
			return msga;
			break;

		}
	}

	void pause()
	{
		// repaste written code for enter.
	}
};

int main()
{
#pragma region variables and stuff in main 
	HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hDialogue);
	DWORD dwBytesWritten = 0;

	int scene = 1;
	int textProgress = 1;

	//talk speeds prefab
	int slow = 1;
	int reg = 2;
	int fast = 3;

	dialogueScene scene1;
#pragma endregion

	scene1.primer();
	scene1.ui();
	while (1)
	{ //main game loop
		
		while (scene == 1)	//main dialogue <=== HERE START
		{
			scene1.talk(scene1.textProgressor(textProgress), slow);
			// waiting for input
			// next line
			scene1.pause();
			textProgress = 2;
			WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
		}
		//inventory
		while (scene == 2)
		{

		} 
		// map
		while (scene == 3)
		{

		}

		
	}
}

