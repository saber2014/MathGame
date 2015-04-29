#include "player.h"
#include "screen.h"

Player::Player(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction, CONSOLE_COLOR shotColor)
	: MovingObject(x, y, sign, foregroundColor, backgroundColor, direction)
{
	this->m_shotColor = shotColor;
	this->m_defaultX = x;
	this->m_defaultY = y;
	this->m_defaultDirection = direction;
	this->m_killed = false;
	this->m_points = 0;
	this->m_attempts = 3;
	this->m_shots = 5;
}

bool Player::IsKilled()
{
	return this->m_killed;
}

int Player::GetPoints()
{
	return this->m_points;
}

int Player::GetAttempts()
{
	return this->m_attempts;
}

int Player::GetShots()
{
	return this->m_shots;
}

list<Shot> &Player::GetShotsList()
{
	return this->m_shotsList;
}

void Player::Shoot()
{
	if (this->m_shots > 0)
	{
		this->m_shots--;

		switch (this->m_direction)
		{
		case OBJECT_MOVE_UP:
			this->m_shotsList.push_back(Shot(this->m_x, g_pScreen->NormalizeGameY(this->m_y - 1), this->m_shotColor, CONSOLE_COLOR_DEFAULT, this->m_direction));
			break;

		case OBJECT_MOVE_RIGHT:
			this->m_shotsList.push_back(Shot(g_pScreen->NormalizeGameX(this->m_x + 1), this->m_y, this->m_shotColor, CONSOLE_COLOR_DEFAULT, this->m_direction));
			break;

		case OBJECT_MOVE_DOWN:
			this->m_shotsList.push_back(Shot(this->m_x, g_pScreen->NormalizeGameY(this->m_y + 1), this->m_shotColor, CONSOLE_COLOR_DEFAULT, this->m_direction));
			break;

		case OBJECT_MOVE_LEFT:
			this->m_shotsList.push_back(Shot(g_pScreen->NormalizeGameX(this->m_x - 1), this->m_y, this->m_shotColor, CONSOLE_COLOR_DEFAULT, this->m_direction));
			break;
		}

		this->m_shotsList.back().Print();
	}
}

void Player::Kill()
{
	this->Clear();

	if (this->m_attempts > 0)
	{
		this->m_attempts--;

		this->m_x = this->m_defaultX;
		this->m_y = this->m_defaultY;
		this->m_direction = this->m_defaultDirection;
		
		this->Print();
	}
	else
		this->m_killed = true;
}