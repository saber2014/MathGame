#ifndef PAUSE_MENU_PAGE_H
#define PAUSE_MENU_PAGE_H

#include "common.h"
#include "page.h"

enum PAUSE_MENU_ITEM
{
	PAUSE_MENU_ITEM_EXIT = 0,
	PAUSE_MENU_ITEM_BACK_MAIN_MENU,
	PAUSE_MENU_ITEM_CONTINUE_PLAY,
	PAUSE_MENU_ITEM_RESTART,
	PAUSE_MENU_ITEM_NEXT
};

class PauseMenuPage : public Page
{
private:
	static const int MENU_ITEMS = 5;

	string m_items[MENU_ITEMS];
	int m_selectedItem;

public:
	PauseMenuPage();

	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintItems();
	void PrintMessage();
	int GetSelectedItem();
};

#endif