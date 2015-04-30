#include "game_page.h"
#include "screen.h"

GamePage::GamePage()
	:
	m_player1(10, 9, '#', CONSOLE_COLOR_LIGHT_PURPLE, CONSOLE_COLOR_DEFAULT, OBJECT_MOVE_RIGHT, CONSOLE_COLOR_PURPLE),
	m_player2(70, 9, '@', CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_DEFAULT, OBJECT_MOVE_LEFT, CONSOLE_COLOR_AQUA)
{
	this->m_level = 1;
	this->m_counter = 0;

	srand((unsigned int)time(NULL));
}

char *GamePage::GetName()
{
	return "Game";
}

void GamePage::Print()
{
	this->PrintHeader();

	this->m_player1.Print();
	this->m_player2.Print();
}

void GamePage::KeyEvent(char key)
{
	switch (key)
	{
	case 'w':
		this->m_player1.SetDirection(OBJECT_MOVE_UP);
		break;

	case 'd':
		this->m_player1.SetDirection(OBJECT_MOVE_RIGHT);
		break;

	case 'x':
		this->m_player1.SetDirection(OBJECT_MOVE_DOWN);
		break;

	case 'a':
		this->m_player1.SetDirection(OBJECT_MOVE_LEFT);
		break;

	case 'z':
		this->m_player1.Shoot(this->m_counter);
		this->PrintPlayerHeader(1);
		break;

	case 'i':
		this->m_player2.SetDirection(OBJECT_MOVE_UP);
		break;

	case 'l':
		this->m_player2.SetDirection(OBJECT_MOVE_RIGHT);
		break;

	case 'm':
		this->m_player2.SetDirection(OBJECT_MOVE_DOWN);
		break;

	case 'j':
		this->m_player2.SetDirection(OBJECT_MOVE_LEFT);
		break;

	case 'n':
		this->m_player2.Shoot(this->m_counter);
		this->PrintPlayerHeader(2);
		break;
	}
}

void GamePage::PrintPlayerHeader(int player)
{
	char buf[255] = {};

	g_pConsole->SetPosition(0, 1);

	switch (player)
	{
	case 1:
		sprintf(buf, "PLAYER 1: %d / %d / %d", this->m_player1.GetPoints(), this->m_player1.GetAttempts(), this->m_player1.GetShots());
		g_pScreen->PrintAligned(buf, SCREEN_ALIGN_LEFT, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_GRAY);
		break;

	case 2:
		sprintf(buf, "PLAYER 2: %d / %d / %d", this->m_player2.GetPoints(), this->m_player2.GetAttempts(), this->m_player2.GetShots());
		g_pScreen->PrintAligned(buf, SCREEN_ALIGN_RIGHT, CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_GRAY);
		break;
	}
}

void GamePage::PrintCounter()
{
	char buf[255] = {};
	sprintf(buf, "%d", (int)this->m_counter);

	g_pConsole->SetPosition(0, 1);
	g_pScreen->PrintAligned("          ", SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_GRAY);
	g_pScreen->PrintAligned(buf, SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_BRIGHT_WHITE, CONSOLE_COLOR_GRAY);
}

void GamePage::PrintHeader()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			g_pConsole->SetPosition(j, i);
			g_pScreen->PrintAligned(" ", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_GRAY);
		}
	}

	char buf[255] = {};
	sprintf(buf, "LEVEL %d", this->m_level);

 	g_pConsole->SetPosition(0, 0);
	g_pScreen->PrintAligned(buf, SCREEN_ALIGN_HCENTER, CONSOLE_COLOR_LIGHT_BLUE, CONSOLE_COLOR_GRAY);

	this->PrintPlayerHeader(1);
	this->PrintPlayerHeader(2);

	this->PrintCounter();
}

bool GamePage::FindAndRemoveShot(int x, int y)
{
	list<Shot>::iterator it = this->m_player1.GetShotsList().begin();

	while (it != this->m_player1.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
		{
			if (this->m_counter != it->GetLastMove())
			{
				it->Clear();
				this->m_player1.GetShotsList().erase(it);

				return true;
			}

			return false;
		}

		it++;
	}

	it = this->m_player2.GetShotsList().begin();

	while (it != this->m_player2.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
		{
			if (this->m_counter != it->GetLastMove())
			{
				it->Clear();
				this->m_player2.GetShotsList().erase(it);

				return true;
			}

			return false;
		}

		it++;
	}

	return false;
}

void GamePage::MoveShots(list<Shot> &shotsList)
{
	list<Shot>::iterator it = shotsList.begin();

	while (it != shotsList.end())
	{
		if (it->IsPossibleToMove())
		{
			it->Move(this->m_counter);
			it++;
		}
		else
		{
			bool b = false;

			BLOCKING_OBJECT bo = it->GetBlockingObject();

			switch (bo)
			{
			case BLOCKING_OBJECT_PLAYER1:
				this->m_player1.Kill();
				this->PrintPlayerHeader(1);
				break;

			case BLOCKING_OBJECT_PLAYER2:
				this->m_player2.Kill();
				this->PrintPlayerHeader(2);
				break;

			case BLOCKING_OBJECT_SHOT:
				b = this->FindAndRemoveShot(it->GetNextX(), it->GetNextY());
				break;
			}

			list<Shot>::iterator temp = it;
			it++;

			if (b)
			{
				temp->Clear();
				shotsList.erase(temp);
			}
		}
	}
}

void GamePage::GenerateNumber()
{
	int x = rand() % WIDTH;
	int y = 3 + rand() % (HEIGHT - 3);
	int number = rand() % (10 + this->m_level);

	char buf[255];
	sprintf(buf, "%d", number);

	g_pScreen->SetAt(buf[0], x, y);
	g_pScreen->Print(buf, x, y, CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);
}

void GamePage::HalfTick()
{
	this->MoveShots(this->m_player1.GetShotsList());
	this->MoveShots(this->m_player2.GetShotsList());

	this->m_counter += 0.5;
}

void GamePage::Tick()
{
	this->PrintCounter();

	bool move_player1 = this->m_player1.IsPossibleToMove();

	if (!this->m_player1.IsKilled())
		this->m_player1.Move();

	bool move_player2 = this->m_player2.IsPossibleToMove();
	
	if (!this->m_player2.IsKilled())
		this->m_player2.Move();

	if (!this->m_player1.IsKilled() && !move_player1) this->m_player1.Move();
	if (!this->m_player2.IsKilled() && !move_player2) this->m_player2.Move();

	if ((int)this->m_counter % ADD_SHOT_TIME == 0)
	{
		if (!this->m_player1.IsKilled())
		{
			this->m_player1.AddShot();
			this->PrintPlayerHeader(1);
		}
		
		if (!this->m_player2.IsKilled())
		{
			this->m_player2.AddShot();
			this->PrintPlayerHeader(2);
		}
	}

	if ((int)this->m_counter % GENERATE_NUMBER_TIME == 0)
		this->GenerateNumber();
}