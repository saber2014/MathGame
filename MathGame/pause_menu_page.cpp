#include "pause_menu_page.h"
#include "screen.h"
#include "keyboard.h"

PauseMenuPage::PauseMenuPage()
{
	this->m_items[PAUSE_MENU_ITEM_EXIT] = "1. Exit";
	this->m_items[PAUSE_MENU_ITEM_BACK_MAIN_MENU] = "2. Back to main menu";
	this->m_items[PAUSE_MENU_ITEM_CONTINUE_PLAY] = "3. Continue to play";
	this->m_items[PAUSE_MENU_ITEM_RESTART] = "4. Restart the current level";
	this->m_items[PAUSE_MENU_ITEM_NEXT] = "5. Go to the next level";

	this->m_selectedItem = 0;
}

char *PauseMenuPage::GetName()
{
	return "Pause Menu";
}

void PauseMenuPage::Print()
{
	g_pConsole->SetPosition(0, 2);
	g_pScreen->PrintAligned("PAUSE MENU", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);

	this->PrintItems();
	this->PrintMessage();
}

void PauseMenuPage::KeyEvent(char key)
{
	switch (key)
	{
	case KEY_UP:
		this->m_selectedItem = this->m_selectedItem - 1 < 0 ? MENU_ITEMS - 1 : this->m_selectedItem - 1;
		break;

	case KEY_DOWN:
		this->m_selectedItem = (this->m_selectedItem + 1) % MENU_ITEMS;
		break;

	case '1':
		this->m_selectedItem = PAUSE_MENU_ITEM_EXIT;
		break;

	case '2':
		this->m_selectedItem = PAUSE_MENU_ITEM_BACK_MAIN_MENU;
		break;

	case '3':
		this->m_selectedItem = PAUSE_MENU_ITEM_CONTINUE_PLAY;
		break;

	case '4':
		this->m_selectedItem = PAUSE_MENU_ITEM_RESTART;
		break;

	case '5':
		this->m_selectedItem = PAUSE_MENU_ITEM_NEXT;
		break;
	}

	this->PrintItems();
}

void PauseMenuPage::PrintItems()
{
	int y = 5;

	for (int i = 0; i < MENU_ITEMS; i++)
	{
		g_pConsole->SetPosition(2, y);
		g_pScreen->PrintAligned((char *)this->m_items[i].c_str(), SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_PURPLE, this->m_selectedItem == i ? CONSOLE_COLOR_PURPLE : CONSOLE_COLOR_DEFAULT);

		y += 2;
	}
}

void PauseMenuPage::PrintMessage()
{
	g_pConsole->SetPosition(0, 4 + MENU_ITEMS * 2 + 2);
	g_pScreen->PrintAligned("PRESS ESC TO GO BACK TO THE GAME.\n\nUSE UP AND DOWN ARROWS TO SELECT AN ITEM\nALTERNATIVELY, TYPE AN ITEM NUMBER.\nTHEN PRESS ENETER", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_AQUA);
}

int PauseMenuPage::GetSelectedItem()
{
	return this->m_selectedItem;
}