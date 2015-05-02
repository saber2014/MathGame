#include "game_page.h"
#include "screen.h"

GamePage::GamePage(int level)
	:
	m_player1(10, 9, '#', CONSOLE_COLOR_LIGHT_PURPLE, CONSOLE_COLOR_DEFAULT, OBJECT_MOVE_RIGHT, CONSOLE_COLOR_PURPLE),
	m_player2(70, 9, '@', CONSOLE_COLOR_LIGHT_AQUA, CONSOLE_COLOR_DEFAULT, OBJECT_MOVE_LEFT, CONSOLE_COLOR_AQUA)
{
	this->m_level = level;
	this->m_counter = 0;

	srand((unsigned int)time(NULL));

	if (1 <= this->m_level && this->m_level <= 20)
	{
		this->m_exercise1.GenerateSimple(this->m_level);
		this->m_exercise2.GenerateSimple(this->m_level);
	}
	else if (21 <= this->m_level && this->m_level <= 40)
	{
		this->m_exercise1.GenerateComplex();
		this->m_exercise2.GenerateComplex();
	}
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
		if (!this->m_player1.Shoot(this->m_counter))
			this->RemoveObject(this->m_player1.GetNextX(), this->m_player1.GetNextY());
		else
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
		if (!this->m_player2.Shoot(this->m_counter))
			this->RemoveObject(this->m_player2.GetNextX(), this->m_player2.GetNextY());
		else
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

void GamePage::PrintExercises()
{
	g_pConsole->SetPosition(0, 2);

	for (int i = 0; i < WIDTH; i++)
		g_pScreen->Print(" ", i, 2, CONSOLE_COLOR_GRAY, CONSOLE_COLOR_GRAY);

	g_pScreen->PrintAligned((char *)this->m_exercise1.GetExercise().c_str(), SCREEN_ALIGN_LEFT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_GRAY);
	g_pScreen->PrintAligned((char *)this->m_exercise2.GetExercise().c_str(), SCREEN_ALIGN_RIGHT, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_GRAY);
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
	this->PrintExercises();
}

int GamePage::GetNumberAt(int x, int y)
{
	int ret = 0;
	int i = x;

	while (i >= 1 && '0' <= g_pScreen->GetAt(i - 1, y) && g_pScreen->GetAt(i - 1, y) <= '9')
		i--;

	while (i < WIDTH && '0' <= g_pScreen->GetAt(i, y) && g_pScreen->GetAt(i, y) <= '9')
	{
		ret *= 10;
		ret += g_pScreen->GetAt(i, y) - '0';

		i++;
	}

	return ret;
}

Shot *GamePage::GetShotAt(int x, int y)
{
	list<Shot>::iterator it = this->m_player1.GetShotsList().begin();

	while (it != this->m_player1.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
			return &*it;

		it++;
	}

	it = this->m_player2.GetShotsList().begin();

	while (it != this->m_player2.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
			return &*it;

		it++;
	}

	return NULL;
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
			if (g_pScreen->GetObjectAt(it->GetNextX(), it->GetNextY()) == OBJECT_TYPE_SHOT)
			{
				Shot *s = this->GetShotAt(it->GetNextX(), it->GetNextY());
				
				if (s->GetLastMove() == this->m_counter)
				{
					it++;
					continue;
				}
			}

			this->RemoveObject(it->GetNextX(), it->GetNextY());

			list<Shot>::iterator temp = it;
			it++;

			temp->Clear();
			shotsList.erase(temp);
		}
	}
}

void GamePage::RemoveNumber(int x, int y)
{
	int i = x;

	while (i >= 1 && '0' <= g_pScreen->GetAt(i - 1, y) && g_pScreen->GetAt(i - 1, y) <= '9')
		i--;

	while (i < WIDTH && '0' <= g_pScreen->GetAt(i, y) && g_pScreen->GetAt(i, y) <= '9')
	{
		g_pScreen->SetAt(' ', i, y);

		char buf[2] = { ' ', 0 };
		g_pScreen->Print(buf, i, y, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);

		i++;
	}
}

void GamePage::RemoveShot(int x, int y)
{
	list<Shot>::iterator it = this->m_player1.GetShotsList().begin();

	while (it != this->m_player1.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
		{
			it->Clear();
			this->m_player1.GetShotsList().erase(it);

			return;
		}

		it++;
	}

	it = this->m_player2.GetShotsList().begin();

	while (it != this->m_player2.GetShotsList().end())
	{
		if (it->GetX() == x && it->GetY() == y)
		{
			it->Clear();
			this->m_player2.GetShotsList().erase(it);

			return;
		}

		it++;
	}
}

void GamePage::RemoveObject(int x, int y)
{
	OBJECT_TYPE ot = g_pScreen->GetObjectAt(x, y);

	switch (ot)
	{
	case OBJECT_TYPE_PLAYER1:
		this->Kill(1);
		this->PrintPlayerHeader(1);
		break;

	case OBJECT_TYPE_PLAYER2:
		this->Kill(2);
		this->PrintPlayerHeader(2);
		break;

	case OBJECT_TYPE_NUMBER:
		this->RemoveNumber(x, y);
		break;

	case OBJECT_TYPE_SHOT:
		this->RemoveShot(x, y);
		break;
	}
}

void GamePage::GenerateNumber()
{
	int x = 0;
	int y = 0;

	int number = 0;

	if (this->m_exercise1.GetType() == EXERCISE_TYPE_COMPLEX && this->m_exercise2.GetType() == EXERCISE_TYPE_COMPLEX)
	{
		int temp = rand() % 5;

		if (temp == 0)
			number = 1 + rand() % (10 + EXERCISE_MAX_VALUE);
		else if (temp == 1)
			number = this->m_exercise1.GetSolution(1);
		else if (temp == 2)
			number = this->m_exercise1.GetSolution(2);
		else if (temp == 3)
			number = this->m_exercise2.GetSolution(1);
		else
			number = this->m_exercise2.GetSolution(2);
	}
	else
	{
		int temp = rand() % 3;

		if (temp == 0)
			number = 1 + rand() % (10 + this->m_level);
		else if (temp == 1)
			number = this->m_exercise1.GetSolution(1);
		else
			number = this->m_exercise2.GetSolution(1);
	}

	char buf[255];
	sprintf(buf, "%d", number);
	int bufLen = strlen(buf);

	for (int i = 0; i < 10; i++)
	{
		x = rand() % WIDTH;
		y = 3 + rand() % (HEIGHT - 3);

		if (x + bufLen > WIDTH)
			continue;

		bool b = false;

		for (int j = -1; j <= bufLen; j++)
		{
			if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(x + j), g_pScreen->NormalizeGameY(y - 1)) != ' ')
				b = true;

			if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(x + j), g_pScreen->NormalizeGameY(y)) != ' ')
				b = true;

			if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(x + j), g_pScreen->NormalizeGameY(y + 1)) != ' ')
				b = true;

			if (b)
				break;
		}

		if (b)
			continue;

		
		for (int j = 0; j < bufLen; j++)
			g_pScreen->SetAt(buf[j], x + j, y);
		
		g_pScreen->Print(buf, x, y, CONSOLE_COLOR_LIGHT_GREEN, CONSOLE_COLOR_GREEN);

		break;
	}
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

	bool reset = false;

	if (!this->m_player1.IsKilled() && !move_player1)
	{
		if (g_pScreen->GetObjectAt(this->m_player1.GetNextX(), this->m_player1.GetNextY()) == OBJECT_TYPE_NUMBER)
		{
			int number = this->GetNumberAt(this->m_player1.GetNextX(), this->m_player1.GetNextY());

			if (this->m_exercise1.GetType() == EXERCISE_TYPE_COMPLEX)
			{
				if (!this->m_exercise1.IsPossibleSolution(number))
				{
					this->Kill(1);
					this->PrintPlayerHeader(1);
				}
				else
					this->PrintExercises();

				if (this->m_exercise1.IsSolved())
				{
					this->m_level++;
					this->m_player1.AddPoint();

					reset = true;
				}
				else
					this->RemoveNumber(this->m_player1.GetNextX(), this->m_player1.GetNextY());
			}
			else
			{
				if (this->m_exercise1.GetSolution(1) == number)
				{
					this->m_level++;
					this->m_player1.AddPoint();

					reset = true;
				}
				else
				{
					this->Kill(1);
					this->PrintPlayerHeader(1);

					this->RemoveNumber(this->m_player1.GetNextX(), this->m_player1.GetNextY());
				}
			}
		}
		else
			this->m_player1.Move();
	}

	if (!this->m_player2.IsKilled() && !move_player2)
	{
		if (g_pScreen->GetObjectAt(this->m_player2.GetNextX(), this->m_player2.GetNextY()) == OBJECT_TYPE_NUMBER)
		{
			int number = this->GetNumberAt(this->m_player2.GetNextX(), this->m_player2.GetNextY());

			if (this->m_exercise2.GetType() == EXERCISE_TYPE_COMPLEX)
			{
				if (!this->m_exercise2.IsPossibleSolution(number))
				{
					this->Kill(2);
					this->PrintPlayerHeader(2);
				}
				else
					this->PrintExercises();

				if (this->m_exercise2.IsSolved())
				{
					this->m_level++;
					this->m_player2.AddPoint();

					reset = true;
				}
				else
					this->RemoveNumber(this->m_player2.GetNextX(), this->m_player2.GetNextY());
			}
			else
			{
				if (this->m_exercise2.GetSolution(1) == number)
				{
					this->m_level++;
					this->m_player2.AddPoint();

					reset = true;
				}
				else
				{
					this->Kill(2);
					this->PrintPlayerHeader(2);

					this->RemoveNumber(this->m_player2.GetNextX(), this->m_player2.GetNextY());
				}
			}
		}
		else
			this->m_player2.Move();
	}

	if (this->m_player1.IsKilled() && this->m_player2.IsKilled())
	{
		reset = true;

		g_pScreen->PrintMessage("BOTH PLAYERS ARE KILLED.\nMOVING TO THE NEXT LEVEL!", SCREEN_MESSAGE_STYLE_RED);
		g_pConsole->Wait(MESSAGE_WAIT_TIME);

		this->m_level++;
	}

	if ((int)this->m_counter == TIME_IS_OVER_TIME)
	{
		reset = true;

		g_pScreen->PrintMessage("TIME IS OVER.\nMOVING TO THE NEXT LEVEL!", SCREEN_MESSAGE_STYLE_RED);
		g_pConsole->Wait(MESSAGE_WAIT_TIME);

		this->m_level++;
	}

	if (reset)
		this->Reset();

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

void GamePage::Reset()
{
	g_pScreen->Clear();

	this->PlayTransition();

	this->m_counter = 0;
	this->m_player1.Reset();
	this->m_player2.Reset();

	if (1 <= this->m_level && this->m_level <= 20)
	{
		this->m_exercise1.GenerateSimple(this->m_level);
		this->m_exercise2.GenerateSimple(this->m_level);
	}
	else if (21 <= this->m_level && this->m_level <= 40)
	{
		this->m_exercise1.GenerateComplex();
		this->m_exercise2.GenerateComplex();
	}

	this->Print();
}

void GamePage::PlayTransition()
{
	char temp1[WIDTH + 1] = { 0 };
	char temp2[WIDTH + 1] = { 0 };

	memset(temp1, ' ', WIDTH);
	memset(temp2, '*', WIDTH);

	for (int i = 0; i < HEIGHT; i++)
	{
		if (i - 1 >= 0)
			g_pScreen->Print(temp1, 0, i - 1, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);

		g_pScreen->Print(temp2, 0, i, CONSOLE_COLOR_LIGHT_YELLOW, CONSOLE_COLOR_YELLOW);
		g_pConsole->Wait(TRANSITION_WAIT_TIME);
	}

	g_pConsole->Clear();
}

void GamePage::Kill(int player)
{
	switch (player)
	{
	case 1:
		if (g_pScreen->GetObjectAt(10, 9) == OBJECT_TYPE_NUMBER)
			this->RemoveNumber(10, 9);

		this->m_player1.Kill();
		break;

	case 2:
		if (g_pScreen->GetObjectAt(70, 9) == OBJECT_TYPE_NUMBER)
			this->RemoveNumber(70, 9);

		this->m_player2.Kill();
		break;
	}
}