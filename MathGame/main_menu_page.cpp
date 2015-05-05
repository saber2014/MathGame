/*
 * MathGame - a competitive math game
 * Copyright (C) 2015  saber2014
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "main_menu_page.h"
#include "screen.h"
#include "keyboard.h"

MainMenuPage::MainMenuPage()
{
	this->m_items[MAIN_MENU_ITEM_INSTRUCTIONS] = "1. Instructions";
	this->m_items[MAIN_MENU_ITEM_START_GAME] = "2. Start game";
	this->m_items[MAIN_MENU_ITEM_START_GAME_LEVEL] = "3. Start game from specific level";
	this->m_items[MAIN_MENU_ITEM_EXIT] = "9. Exit";

	this->m_selectedItem = 0;
}

char *MainMenuPage::GetName()
{
	return (char *)"Main Menu";
}

void MainMenuPage::Print()
{
	g_pConsole->SetPosition(0, 2);
	g_pScreen->PrintAligned((char *)"MATH GAME", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);

	this->PrintItems();
	this->PrintMessage();
}

void MainMenuPage::KeyEvent(char key)
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
		this->m_selectedItem = MAIN_MENU_ITEM_INSTRUCTIONS;
		break;

	case '2':
		this->m_selectedItem = MAIN_MENU_ITEM_START_GAME;
		break;

	case '3':
		this->m_selectedItem = MAIN_MENU_ITEM_START_GAME_LEVEL;
		break;

	case '9':
		this->m_selectedItem = MAIN_MENU_ITEM_EXIT;
		break;
	}

	this->PrintItems();
}

void MainMenuPage::PrintItems()
{
	int y = 5;

	for (int i = 0; i < MENU_ITEMS; i++)
	{
		g_pConsole->SetPosition(2, y);
		g_pScreen->PrintAligned((char *)this->m_items[i].c_str(), SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_PURPLE, this->m_selectedItem == i ? CONSOLE_COLOR_PURPLE : CONSOLE_COLOR_DEFAULT);

		y += 2;
	}
}

void MainMenuPage::PrintMessage()
{
	g_pConsole->SetPosition(0, 4 + MENU_ITEMS * 2 + 2);
	g_pScreen->PrintAligned((char *)"USE UP AND DOWN ARROWS TO SELECT AN ITEM\nALTERNATIVELY, TYPE AN ITEM NUMBER.\nTHEN PRESS ENETER", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_AQUA);
}

int MainMenuPage::GetSelectedItem()
{
	return this->m_selectedItem;
}