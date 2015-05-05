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

#include "start_game_level_page.h"
#include "screen.h"
#include "keyboard.h"

StartGameLevelPage::StartGameLevelPage()
{
	this->m_levelNumber = "1";
}

StartGameLevelPage::~StartGameLevelPage()
{
	g_pConsole->ShowCursor(false);
}

char *StartGameLevelPage::GetName()
{
	return (char *)"Start Game Level";
}

void StartGameLevelPage::Print()
{
	g_pConsole->SetPosition(0, 2);
	g_pScreen->PrintAligned((char *)"START GAME FROM SPECIFIC LEVEL", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);

	g_pConsole->SetPosition(2, 5);
	g_pScreen->PrintAligned((char *)"Level number:", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);

	this->PrintMessage();

	this->PrintLevel();
	g_pConsole->ShowCursor(true);
}

void StartGameLevelPage::KeyEvent(char key)
{
	if ('0' <= key && key <= '9' && this->m_levelNumber.length() < 4)
	{
		this->m_levelNumber += key;
		this->PrintLevel();
	}
	else if (key == KEY_BACKSPACE && this->m_levelNumber.length() > 0)
	{
		this->m_levelNumber = this->m_levelNumber.substr(0, this->m_levelNumber.length() - 1);
		this->PrintLevel();
	}
}

void StartGameLevelPage::PrintLevel()
{
	g_pConsole->SetPosition(2 + strlen("Level number:") + 1, 5);
	g_pScreen->PrintAligned((char *)"      ", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_BRIGHT_WHITE, CONSOLE_COLOR_GRAY);

	g_pConsole->SetPosition(2 + strlen("Level number:") + 2, 5);
	g_pScreen->PrintAligned((char *)this->m_levelNumber.c_str(), SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_BRIGHT_WHITE, CONSOLE_COLOR_GRAY);
}

void StartGameLevelPage::PrintMessage()
{
	g_pConsole->SetPosition(0, 8);
	g_pScreen->PrintAligned((char *)"PRESS ENTER TO CONTINUE\nPRESS ESC TO GO BACK TO THE MAIN MENU", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_AQUA);
}

int StartGameLevelPage::GetLevelNumber()
{
	return atoi(this->m_levelNumber.c_str());
}