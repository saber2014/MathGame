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

#include "manager.h"
#include "console.h"
#include "screen.h"
#include "keyboard.h"
#include "main_menu_page.h"
#include "instructions_page.h"
#include "game_page.h"
#include "start_game_level_page.h"
#include "pause_menu_page.h"

Manager::Manager()
{
	this->m_pCurrentPage = NULL;
	this->m_gameOver = false;

	this->m_savedGamePage = NULL;

	g_pConsole = new Console();
	g_pScreen = new Screen();
	g_pKeyboard = new Keyboard();

	g_pConsole->SetTitle((char *)"Math Game");
	g_pConsole->ShowCursor(false);
	g_pConsole->SetBufferSize(WIDTH, HEIGHT);

	Exercise::InitLookupTable();
}

Manager::~Manager()
{
	if (this->m_pCurrentPage)
		delete this->m_pCurrentPage;

	if (this->m_savedGamePage)
		delete this->m_savedGamePage;

	g_pConsole->Clear();

	if (g_pConsole)
		delete g_pConsole;

	if (g_pScreen)
		delete g_pScreen;

	if (g_pKeyboard)
		delete g_pKeyboard;
}

void Manager::SwitchPage(Page *pNewPage)
{
	if (this->m_pCurrentPage)
		delete this->m_pCurrentPage;

	this->m_pCurrentPage = pNewPage;
	this->m_pCurrentPage->Print();
}

void Manager::Run()
{
	this->SwitchPage(new MainMenuPage());

	bool run = true;

	while (run)
	{
		list<char> myList = g_pKeyboard->GetInput();

		for (list<char>::iterator it = myList.begin(); it != myList.end(); it++)
		{
			if (*it == KEY_ESC)
			{
				if (!strcmp(this->m_pCurrentPage->GetName(), "Main Menu"))
					run = false;
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Instructions"))
					this->SwitchPage(new MainMenuPage());
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Start Game Level"))
					this->SwitchPage(new MainMenuPage());
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Game"))
				{
					this->m_savedGamePage = new GamePage(*dynamic_cast<GamePage *>(this->m_pCurrentPage));
					this->SwitchPage(new PauseMenuPage());
				}
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Pause Menu"))
				{
					g_pConsole->Clear();
					g_pScreen->PrintScreenWithNumbers();

					this->SwitchPage(new GamePage(*this->m_savedGamePage));

					delete this->m_savedGamePage;
					this->m_savedGamePage = NULL;
				}
			}
			else if (*it == KEY_ENTER)
			{
				if (!strcmp(this->m_pCurrentPage->GetName(), "Main Menu"))
				{
					MainMenuPage *pMainMenuPage = dynamic_cast<MainMenuPage *>(this->m_pCurrentPage);

					switch (pMainMenuPage->GetSelectedItem())
					{
					case MAIN_MENU_ITEM_INSTRUCTIONS:
						this->SwitchPage(new InstructionsPage());
						break;

					case MAIN_MENU_ITEM_START_GAME:
						this->SwitchPage(new GamePage(1));
						break;

					case MAIN_MENU_ITEM_START_GAME_LEVEL:
						this->SwitchPage(new StartGameLevelPage());
						break;

					case MAIN_MENU_ITEM_EXIT:
						run = false;
						break;
					}
				}
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Start Game Level"))
				{
					StartGameLevelPage *pStartGameLevelPage = dynamic_cast<StartGameLevelPage *>(this->m_pCurrentPage);
					int levelNumber = pStartGameLevelPage->GetLevelNumber();

					if (levelNumber < 1 || levelNumber > 40)
					{
						g_pConsole->ShowCursor(false);
						g_pScreen->PrintMessage((char *)"INCORRECT LEVEL NUMBER!\nPLEASE TRY AGAIN.", SCREEN_MESSAGE_STYLE_RED);
						g_pConsole->Wait(MESSAGE_WAIT_TIME);

						g_pConsole->Clear();
						pStartGameLevelPage->Print();
						g_pConsole->ShowCursor(true);
					}
					else
						this->SwitchPage(new GamePage(levelNumber));
				}
				else if (!strcmp(this->m_pCurrentPage->GetName(), "Pause Menu"))
				{
					PauseMenuPage *pPauseMenuPage = dynamic_cast<PauseMenuPage *>(this->m_pCurrentPage);

					switch (pPauseMenuPage->GetSelectedItem())
					{
					case PAUSE_MENU_ITEM_EXIT:
						run = false;
						break;

					case PAUSE_MENU_ITEM_BACK_MAIN_MENU:
						this->SwitchPage(new MainMenuPage());
						break;

					case PAUSE_MENU_ITEM_CONTINUE_PLAY:
						g_pConsole->Clear();
						g_pScreen->PrintScreenWithNumbers();
						
						this->SwitchPage(new GamePage(*this->m_savedGamePage));
						break;

					case PAUSE_MENU_ITEM_RESTART:
						this->SwitchPage(new GamePage(this->m_savedGamePage->GetLevel()));
						
						dynamic_cast<GamePage *>(this->m_pCurrentPage)->SetPlayerPoints(1, this->m_savedGamePage->GetPlayerPoints(1));
						dynamic_cast<GamePage *>(this->m_pCurrentPage)->SetPlayerPoints(2, this->m_savedGamePage->GetPlayerPoints(2));
						dynamic_cast<GamePage *>(this->m_pCurrentPage)->PrintHeader();
						break;

					case PAUSE_MENU_ITEM_NEXT:
						if (this->m_savedGamePage->GetLevel() + 1 > 40)
						{
							g_pScreen->PrintMessage((char *)"CONGRATULATIONS! YOU COMPLETED THE GAME.", SCREEN_MESSAGE_STYLE_RED);
							g_pConsole->Wait(MESSAGE_WAIT_TIME);

							this->SwitchPage(new MainMenuPage());
						}
						else
						{
							this->SwitchPage(new GamePage(this->m_savedGamePage->GetLevel() + 1));
							
							dynamic_cast<GamePage *>(this->m_pCurrentPage)->SetPlayerPoints(1, this->m_savedGamePage->GetPlayerPoints(1));
							dynamic_cast<GamePage *>(this->m_pCurrentPage)->SetPlayerPoints(2, this->m_savedGamePage->GetPlayerPoints(2));
							dynamic_cast<GamePage *>(this->m_pCurrentPage)->PrintHeader();
						}
						break;
					}

					delete this->m_savedGamePage;
					this->m_savedGamePage = NULL;
				}
			}
			else
			{
				this->m_pCurrentPage->KeyEvent(*it);

				if (!strcmp(this->m_pCurrentPage->GetName(), "Main Menu") || !strcmp(this->m_pCurrentPage->GetName(), "Pause Menu"))
				{
					g_pConsole->Wait(WAIT_TIME);

					list<char> myList2 = g_pKeyboard->GetInput();

					for (list<char>::iterator it2 = myList2.begin(); it2 != myList2.end(); it2++)
					{
						if (*it != *it2)
							myList.push_back(*it2);
					}
				}
			}
		}

		if (!strcmp(this->m_pCurrentPage->GetName(), "Game"))
		{
			if (this->m_gameOver)
			{
				this->m_gameOver = false;

				this->SwitchPage(new MainMenuPage());
			}
			else
			{
				GamePage *pGamePage = dynamic_cast<GamePage *>(this->m_pCurrentPage);

				pGamePage->HalfTick();
				pGamePage->Tick(this);

				g_pConsole->Wait(GAME_WAIT_TIME / 2);

				pGamePage->HalfTick();

				g_pConsole->Wait(GAME_WAIT_TIME / 2);
			}
		}
	}
}

void Manager::Callback(MANAGER_CALLBACK value)
{
	switch (value)
	{
	case MANAGER_CALLBACK_GAME_OVER:
		this->m_gameOver = true;
		break;
	}
}