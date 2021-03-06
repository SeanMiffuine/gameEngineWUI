#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>
#include <vector>
#include <Windows.h>
#include <string>

// main game screen
class scene {
public:

    scene();                                   // default constructor 
    void clear();                              // clear the screen
    void ui();                                 // update the ui
    void talk(std::wstring msg, int speed);    // update text 
    void render();                             // renders text to console
    void dialogue(event e);                    // updates all dialogue on screen  
    void choice(event e);                      // picking next event
    std::wstring textProgressor(int progress); // returns right string ???

private:
    const int screenW = 120; 
    const int screenH = 30;
    wchar_t* screen; // = new wchar_t[screenW*screenH];
    HANDLE sBuffer;
    DWORD dwBytesWritten = 0;
    int textPos = 9;
    int rowPos = 3; 
    int tempPos;
    event currentEvent;                        // current event on lol

};

// game story events | graph form
class event {
public:

    event(); //blank event
    event(bool cutscene, std::wstring name);        // constructor
    void setText(std::wstring text, int speed);     // sets text and speed it types 
    void setNextEvents(event * next);               // sets next events per choice

private:

    std::wstring eventName;                         // name of current event
    bool isCutscene;                                // 1 for cutscene event, 0 for choice event
    std::vector<event*> nextEvents;                 // event children for next event
    std::vector<std::pair<std::wstring, int>> dialogue;                 // dialogue text
    //std::vector<int> speed;                         // speed per dialogue text, in tandem with <text>

};

#endif