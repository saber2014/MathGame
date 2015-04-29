#include "shot.h"
#include "screen.h"

Shot::Shot(int x, int y, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction)
	: MovingObject(x, y, '*', foregroundColor, backgroundColor, direction)
{
}

BLOCKING_OBJECT Shot::GetBlockingObject()
{
	char ch = ' ';

	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		ch = g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y - 1));
		break;

	case OBJECT_MOVE_RIGHT:
		ch = g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x + 1), this->m_y);
		break;

	case OBJECT_MOVE_DOWN:
		ch = g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y + 1));
		break;

	case OBJECT_MOVE_LEFT:
		ch = g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x - 1), this->m_y);
		break;
	}

	if (ch == '#')
		return BLOCKING_OBJECT_PLAYER1;
	else if (ch == '@')
		return BLOCKING_OBJECT_PLAYER2;
	else if ('0' <= ch && ch <= '9')
		return BLOCKING_OBJECT_NUMBER;
	else if (ch == '*')
		return BLOCKING_OBJECT_SHOT;

	return BLOCKING_OBJECT_NONE;
}