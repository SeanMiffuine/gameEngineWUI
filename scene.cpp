#define UNICODE

#include "scene.h"

scene::scene() {
    sBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); 
    screen = new wchar_t[screenW*screenH];
}

void scene::clear() {
    std::fill_n(screen, (screenW * screenH), L' ');
}

void scene::ui() {
    //starting from row 3 to row 27, col 10 - 80
		// row 2 - 29, col 8, 82

		//rows render ascii 0x2592
		for (int x = 120 + 6; x <= 120 + 83; x++)
		{
            screen[x] = 0x2593;
        }
		for (int x = 120 * 28 + 6; x <= 120 * 28 + 83; x++)
		{
			screen[x] = 0x2593;
		}
		//column render
		for (int x = 120 * 2 + 5; x <= 120 * 27 + 6; x += 120)
		{
			screen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 84; x <= 120 * 27 + 84; x += 120)
		{
			screen[x] = 0x2593;
		}

		// right side UI
		for (int x = 120 + 88; x <= 120 + 113; x++) //row
		{
			screen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 87; x <= 120 * 28 + 86; x += 120) // col
		{
			screen[x] = 0x2593;
		}
		for (int x = 120 * 28 + 88; x <= 120 * 28 + 113; x++) //row 
		{
			screen[x] = 0x2593;
		}
		for (int x = 120 * 18 + 88; x <= 120 * 18 + 113; x++) //row divider 
		{
			screen[x] = 0x2593;
		}
		for (int x = 120 * 2 + 114; x <= 120 * 28 + 113; x += 120) //col
		{
			screen[x] = 0x2593;
		}
        render();
}

void scene::talk(std::wstring msg, int speed) {
    switch (speed)
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
    
	for (int i = 0; i <= msg.length(); i++) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) { // prevent hold down
			for (int j = i; j <= msg.length(); j++) // !!! need primer() for when full 
			{
				if (textPos > 81)// we want dialogue to be from 10 ~ 80?
				{
					textPos = 9;
					rowPos++;
				}
				if (rowPos > 26) // rows 4 - 26
				{
					// possible primer() here?
					rowPos = 3;
				}
				tempPos = rowPos * 120 + textPos;
                screen[(tempPos)] = msg[j];
                textPos++;
			}
			std::this_thread::sleep_for(std::chrono::microseconds(10));
            render(); // !!!
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
		screen[(tempPos)] = msg[i]; //textPos is position of text going to be written.
		textPos++;
		//check for skip text
		std::this_thread::sleep_for(std::chrono::microseconds(speed));
		render();
	}
}

void scene::render() {
    SetConsoleActiveScreenBuffer(sBuffer);
    WriteConsoleOutputCharacterW(sBuffer, screen, screenW * screenH, { 0,0 }, &dwBytesWritten);
}

void scene::dialogue(event e) {

}         

void scene::choice(event e) {

}

std::wstring scene::textProgressor(int progress) {

}


event::event() {
	eventName = L"blank";
	isCutscene = true;
}

event::event(bool cutscene, std::wstring name) {
	eventName = name;
	isCutscene = cutscene;
}

void event::setText(std::wstring text, int speed) {
	dialogue.push_back(std::make_pair(text, speed));
}

void event::setNextEvents(event * next) {

}



