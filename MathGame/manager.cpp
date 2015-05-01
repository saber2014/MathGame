#include "manager.h"
#include "console.h"
#include "screen.h"
#include "keyboard.h"
#include "main_menu_page.h"
#include "instructions_page.h"
#include "game_page.h"
#include "start_game_level_page.h"

Manager::Manager()
{
	this->m_pCurrentPage = NULL;

	g_pConsole = new Console();
	g_pScreen = new Screen();
	g_pKeyboard = new Keyboard();

	g_pConsole->SetTitle("Math Game");
	g_pConsole->ShowCursor(false);
	g_pConsole->SetBufferSize(WIDTH, HEIGHT);
}

Manager::~Manager()
{
	if (this->m_pCurrentPage)
		delete this->m_pCurrentPage;

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

					this->SwitchPage(new GamePage(levelNumber));
				}
			}
			else
			{
				this->m_pCurrentPage->KeyEvent(*it);

				if (!strcmp(this->m_pCurrentPage->GetName(), "Main Menu"))
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
			GamePage *pGamePage = dynamic_cast<GamePage *>(this->m_pCurrentPage);

			pGamePage->HalfTick();
			pGamePage->Tick();

			g_pConsole->Wait(GAME_WAIT_TIME / 2);

			pGamePage->HalfTick();

			g_pConsole->Wait(GAME_WAIT_TIME / 2);
		}
	}
}