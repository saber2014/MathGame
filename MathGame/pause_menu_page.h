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

#ifndef PAUSE_MENU_PAGE_H
#define PAUSE_MENU_PAGE_H

#include "common.h"
#include "page.h"

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