// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <algorithm>
#include <chrono>
#include <vector>
#include "functions.h"

int screenW = 120;
int screenH = 80; 
extern wchar_t *screen = new wchar_t[screenW*screenH];
extern wchar_t *dialogueScreen = new wchar_t[screenW*screenH]; //maybe just one file?

//indexes of vector correspond to each choice. e.g. int[] = {1, 2, 3, 7, 10} <- select1, select2, etc.
std::vector<std::wstring> allChoices = { select1, select2, select3, select4};
// not to be confused with temp choice; this is list of all possible choices; 

int scene;
int textProgress;
int size;
static bool skip = false;
bool screenMain = true;
bool newLoad = true;
static int textPos = 9; //text left right 10 - 80
static int rowPos = 3; // text row 4 - 26

/* list of features
-----------------------
-type speeds xxx
-wait for input to next line (++ to textProgress), enter to next line?  xxx
-putting sentences at line numbers (every 3n*120?) xxx
-UI ascii xxx

-starting and ending menu
-dialogue system tempaltes
-select menu xxx
-ascii filled in and out like cursor??? 
-choice xxx
-sound FX, music etc. 
-starting and ending menu
*/

//thoughts
/*
	when items on hand, then can interact with certain things. E.g. combine two paper clips = lockpick, then equip to open door.

	choices menu is seperate, pauses dialogue.  "third person dialogue", contextual clues
*/

class Item {
private:
	std::wstring name;
	std::wstring description;
	std::wstring image;
	bool equipable;
	bool combinable;
	int combinedItems; // index for set of items needed for combination

public:
	Item(std::wstring n, std::wstring desc, std::wstring img, bool eq, bool comb, int combItems) {
		name = n;
		description = desc;
		image = img;
		equipable = eq;
		combinable = comb;
		combinedItems = combItems;
	}

	bool combine(Item* item) {
		if (combinedItems == item->combinedItems) {
			return true;
		}
		return false;
	}

	std::wstring getName() {
		return name;
	}

	std::wstring getDescription() {
		return description;
	}

	std::wstring getImage() {
		return image;
	}

	bool getEquipable() {
		return equipable;
	}

	bool getCombinable() {
		return combinable;
	}

	int getCombineNumber() {
		return combinedItems;
	}
};

class Inventory {
private:
	//Item* equipped;
	std::vector<Item*> allItems;
	std::vector<Item*> inven;

public:

	void addItem(Item* i) {
		inven.push_back(i);
	}

	void equip(int i) { // int i is index of item
		//equipped = inven.at(i);
	}

	void use(int i) {
		//some sort of functions on player !!!
		removeItem(i);
	}

	void removeItem(int i) {
		inven.erase(inven.begin() + i);
	}

	void clearAll() {
		inven.clear();
	}

	std::vector<Item*> getItems() {
		return inven;
	}

};



class Scene {
public:

	int speed;
	int lowB = (3 * 120 + 10);
	int highB = (3 * 120 + 80);
	int tempPos;

	Inventory inventory;


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
			if (GetAsyncKeyState(VK_RETURN) & 0x0001) // prevent hold down craziness
			{
				
				for (int j = i; j <= msg.length(); j++) // !!! need primer() for when full 
				{
					if (textPos > 81)// we want dialogue to be from 10 ~ 80?
					{
						textPos = 9;
						rowPos++;
					}
					if (rowPos > 26)// rows 4 - 26
					{
						// possible primer() here?
						rowPos = 3;
					}
					tempPos = rowPos * 120 + textPos;
					dialogueScreen[(tempPos)] = msg[j];
					textPos++;
				}
				//i = msg.length();
				std::this_thread::sleep_for(std::chrono::microseconds(10));
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

	//set screen blank / prime CLEAR
	void primer()
	{
		std::fill_n(dialogueScreen, (screenW * screenH), ' ');
		WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}

	//sets up ui and personal info
	void ui()
	{
		//starting from row 3 to row 27, col 10 - 80
		// row 2 - 29, col 8, 82

		//rows render ascii 0x2592
		for (int x = 120 + 6; x <= 120 + 83; x++)
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 28 + 6; x <= 120 * 28 + 83; x++)
		{
			dialogueScreen[x] = 0x2593;
		}
		//column render
		for (int x = 120 * 2 + 5; x <= 120 * 27 + 6; x += 120)
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
		for (int x = 120 * 18 + 88; x <= 120 * 18 + 113; x++) //row divider 
		{
			dialogueScreen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 114; x <= 120 * 28 + 113; x += 120) //col
		{
			dialogueScreen[x] = 0x2593;
		}
		WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}

	std::wstring textProgressor(int progress) // for dialogue.cpp
	{
		switch (progress)
		{
		case 1:
			return msg;
			break;
		case 2:
			return msga;
			break;

		}
	}

	void choice(int scene[])
	{
		//underside of ui right
		//choice state.
		//loop goes dialogue -> choice state -> dialogue ; with escape menu? w/ save?

		//choices during dialogue: map, inven, interact, dialogue choices;
		//choices during map: NOTHING. should just display information. such as "freezer seems cold". esc to go back to dialogue,
		//	then you can interact
		//choices during inven: up, down, combine, equip.

		////code for dialogue choices
		// clicking choice calls talk function by passing # for textProgresor. choices are also represented by
		// array of numbers -> huge dialogue array to pull from.
		// e.g. [1,2,3] -> outputs shorthand choice 1 2 and 3 (index of functions.h replies) as well as prints 1, 2 or 3 in dialogue box when selected.
		// int -> wstring grabber()

		//print blank
		int txtPos = 0;
		int rowPos = 0;
		int choice = 0; //index for choice for scene[]

		int tempIndex; // current index of allChoices

		//print choices - 5 choices + "select choice". index 4 is null
		for (int i = 0; i < 7; i++)
		{
			tempIndex = scene[choice];
			std::wstring tempChoice = allChoices[tempIndex];
			//for (int j = 120 * (20 + i) + 90; i <= 120 * (20 + i) + 90; i++) //improper for. use for loop of tempChoice.
			for (int j = 0; j < tempChoice.size(); j++)
			{
				//loop through indexes of scene
				txtPos = 120 * (20 + rowPos) + 90 + j;
				dialogueScreen[txtPos] = tempChoice[j];
			}
			rowPos++;
			choice++;
		}
		//print menu and shit
		
		bool isInput = false;
		int xPos = 0;
		int choiceState = 0; // 0-5
		//select choice
		while (!isInput)
		{
			// blank + dialogue choices + map + inven
			//arrow keys ++ or --, going up or down. sets scene or prints dialogue
			//take old x and replace with  ' ' , put x at next space (20, 21, 22, 23, 24, 25) <- total 7 choices
			

			//up func
		
			if (GetAsyncKeyState((unsigned short)'S') & 0x0001)
			{
				if (choiceState < 6)
				{
					xPos = 120 * (20 + choiceState) + 89;
					dialogueScreen[xPos] = ' ';
					choiceState++;
				}
			}

			//down func
			if (GetAsyncKeyState((unsigned short)'W') & 0x0001)
			{
				if (choiceState > 0)
				{
					xPos = 120 * (20 + choiceState) + 89;
					dialogueScreen[xPos] = ' ';
					choiceState--;
				}
			}
			//render x mark

			xPos = 120 * (20 + choiceState) + 89;
			dialogueScreen[xPos] = 'x';
			
			if ((GetAsyncKeyState(VK_RETURN) & 0x0001) && (choiceState != 0)) { // prevent hold down craziness 
				// INPUT CHOICE RIGHT HERE 

				//FILLER; implement choices !!!


				//primer();
				screenMain = false;
				isInput = true;
				newLoad = true;

				/*
				while (1) {
				
					dialogueScreen[xPos] = 'x';
					WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
				}
				*/
				//maybe while(input! = enter), exit. grab the current choice and use.
			}
			//render scene
			WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));

		}

	}

	//inventory scene methods
	void showItems() {
		std::vector<Item*> inven = inventory.getItems();
		for (Item* item : inven) {
			printItem(item);
		}

	}

	void printItem(Item* item) {
		std::wstring name = item->getName();
		std::wstring description = item->getDescription();
		std::wstring image = item->getImage();

		for (int i = 0; i <= name.length(); i++) // need primer() for when full !!!
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
			dialogueScreen[(tempPos)] = msg[i]; //textPos is position of text going to be written.
			textPos++;
		}
		WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
	}

	void itemChoice() {
		//choices for items. left / right goes from item select to function select. up down goes from item scrolling or function selecting.
	}
};


// MAIN MAIN MAIN
	int main()
	{
#pragma region variables and stuff in main 
		HANDLE hDialogue = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hDialogue);
		DWORD dwBytesWritten = 0;

		//talk speeds prefab
		int slow = 1;
		int reg = 2;
		int fast = 3;

		int textProgress = 1;
		

		Scene dialogueScene;
		
		Item* key = new Item(L"Key", L"just a cup", L"xx xxx xx", true, false, 1);


#pragma endregion


		while (1)
		{ //main game loop

			if (screenMain)	// main dialogue
			{
				if (newLoad) {
					dialogueScene.primer();
					dialogueScene.ui();
					newLoad = false;
				}
				dialogueScene.talk(dialogueScene.textProgressor(textProgress), slow);
				//tempchoice must have 7 choices; 
				int tempChoice[7] = { 0, 1, 2, 2, 2, 2, 2}; //where we pick from allChoices;
				dialogueScene.choice(tempChoice); // all the choices passed through
				textProgress = 2;
				
			}
			//inventory
			if (!screenMain)
			{
				if (newLoad) {
					dialogueScene.primer();
					dialogueScene.ui();
					newLoad = false;
				}
				dialogueScene.showItems();
				//instead of having inventoryscreen n dialogue screen, have each seperate copy onto screen each tiem you switch??? !!!
				//inventory scene with own class system. however, still implement WriteConsoleOutput.?
				
			}

			WriteConsoleOutputCharacter(hDialogue, dialogueScreen, screenW * screenH, { 0,0 }, &dwBytesWritten);
		}
	}
