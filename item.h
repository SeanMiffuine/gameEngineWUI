#ifndef ITEM_H_
#define ITEM_H_
#include <iostream>
#include <utility>
#include <vector>
#include <Windows.h>
#include <string>

// items
class item {
public:
    item();
    item(std::wstring name, std::wstring description, std::wstring image, bool equipable, bool combinable, int id, int combinableWith);
private:
    std::wstring name;          // name of item
	std::wstring description;   // item description
	std::wstring image;         // ASCII image
    bool equipable;             // equipable 1, consumable 0
	bool combinable;            // combinable 1
    int id;                     // number id
    int combinableWith;         // combinable with
    

};

// game screen for checking inventory
class itemScene {
public:


private:
    std::vector<item> allItems; // all possible items in game
    std::vector<item> inventory;// current items in inventory

};

#endif