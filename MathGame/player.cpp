#include "player.h"
#include "screen.h"

Player::Player(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, PLAYER_MOVE direction)
{
	this->m_points = 0;
	this->m_attempts = 3;
	
	this->m_x = x;
	this->m_y = y;
	this->m_sign = sign;
	this->m_foregroundColor = foregroundColor;
	this->m_backgroundColor = backgroundColor;
	this->m_direction = direction;
}

int Player::GetPoints()
{
	return this->m_points;
}

int Player::GetAttempts()
{
	return this->m_attempts;
}

void Player::SetDirection(PLAYER_MOVE direction)
{
	this->m_direction = direction;
}

void Player::Print()
{
	char buf[2] = { this->m_sign, 0 };

	g_pConsole->SetPosition(this->m_x, this->m_y);
	g_pScreen->PrintAligned(buf, SCREEN_ALIGN_DEFAULT, this->m_foregroundColor, this->m_backgroundColor);
}

void Player::Clear()
{
	g_pConsole->SetPosition(this->m_x, this->m_y);
	g_pScreen->PrintAligned(" ", SCREEN_ALIGN_DEFAULT, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);
}

void Player::Move()
{
	switch (this->m_direction)
	{
	case PLAYER_MOVE_UP:
		this->m_y = g_pScreen->NormalizeGameY(this->m_y - 1);
		break;

	case PLAYER_MOVE_RIGHT:
		this->m_x = g_pScreen->NormalizeGameX(this->m_x + 1);
		break;

	case PLAYER_MOVE_DOWN:
		this->m_y = g_pScreen->NormalizeGameY(this->m_y + 1);
		break;

	case PLAYER_MOVE_LEFT:
		this->m_x = g_pScreen->NormalizeGameX(this->m_x - 1);
		break;
	}

	this->Print();
}