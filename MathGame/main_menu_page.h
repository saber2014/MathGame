#ifndef MAIN_MENU_PAGE_H
#define MAIN_MENU_PAGE_H

#include "common.h"
#include "page.h"

enum MAIN_MENU_ITEM
{
	MAIN_MENU_ITEM_INSTRUCTIONS = 0,
	MAIN_MENU_ITEM_START_GAME,
	MAIN_MENU_ITEM_START_GAME_LEVEL,
	MAIN_MENU_ITEM_EXIT
};

class MainMenuPage : public Page
{
private:
	static const int MENU_ITEMS = 4;

	string m_items[MENU_ITEMS];
	int m_selectedItem;

public:
	MainMenuPage();

	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintItems();
	void PrintMessage();
	int GetSelectedItem();
};

#endif