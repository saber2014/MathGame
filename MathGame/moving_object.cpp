#include "moving_object.h"
#include "screen.h"

MovingObject::MovingObject(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction)
{
	this->m_x = x;
	this->m_y = y;
	this->m_sign = sign;
	this->m_foregroundColor = foregroundColor;
	this->m_backgroundColor = backgroundColor;
	this->m_direction = direction;
}

void MovingObject::Clear()
{
	g_pScreen->SetAt(' ', this->m_x, this->m_y);

	char buf[2] = { ' ', 0 };
	g_pScreen->Print(buf, this->m_x, this->m_y, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);
}

void MovingObject::Print()
{
	g_pScreen->SetAt(this->m_sign, this->m_x, this->m_y);

	char buf[2] = { this->m_sign, 0 };
	g_pScreen->Print(buf, this->m_x, this->m_y, this->m_foregroundColor, this->m_backgroundColor);
}

void MovingObject::SetDirection(OBJECT_MOVE direction)
{
	this->m_direction = direction;
}

bool MovingObject::IsPossibleToMove()
{
	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		if (g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y - 1)) != ' ')
			return false;
		break;

	case OBJECT_MOVE_RIGHT:
		if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x + 1), this->m_y) != ' ')
			return false;
		break;

	case OBJECT_MOVE_DOWN:
		if (g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y + 1)) != ' ')
			return false;
		break;

	case OBJECT_MOVE_LEFT:
		if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x - 1), this->m_y) != ' ')
			return false;
		break;
	}

	return true;
}

void MovingObject::Move()
{
	this->Clear();

	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		if (this->IsPossibleToMove())
			this->m_y = g_pScreen->NormalizeGameY(this->m_y - 1);
		break;

	case OBJECT_MOVE_RIGHT:
		if (this->IsPossibleToMove())
			this->m_x = g_pScreen->NormalizeGameX(this->m_x + 1);
		break;

	case OBJECT_MOVE_DOWN:
		if (this->IsPossibleToMove())
			this->m_y = g_pScreen->NormalizeGameY(this->m_y + 1);
		break;

	case OBJECT_MOVE_LEFT:
		if (this->IsPossibleToMove())
			this->m_x = g_pScreen->NormalizeGameX(this->m_x - 1);
		break;
	}

	this->Print();
}