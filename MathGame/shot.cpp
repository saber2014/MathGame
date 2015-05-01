#include "shot.h"
#include "screen.h"

Shot::Shot(int x, int y, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction, float count)
	: MovingObject(x, y, '*', foregroundColor, backgroundColor, direction)
{
	this->m_lastMove = count;
}

void Shot::Move(float count)
{
	if (this->m_lastMove != count)
		MovingObject::Move();

	this->m_lastMove = count;
}

float Shot::GetLastMove()
{
	return this->m_lastMove;
}

OBJECT_TYPE Shot::GetBlockingObject()
{
	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		return g_pScreen->GetObjectAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y - 1));
		break;

	case OBJECT_MOVE_RIGHT:
		return g_pScreen->GetObjectAt(g_pScreen->NormalizeGameX(this->m_x + 1), this->m_y);
		break;

	case OBJECT_MOVE_DOWN:
		return g_pScreen->GetObjectAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y + 1));
		break;

	case OBJECT_MOVE_LEFT:
		return g_pScreen->GetObjectAt(g_pScreen->NormalizeGameX(this->m_x - 1), this->m_y);
		break;
	}

	return OBJECT_TYPE_NONE;
}