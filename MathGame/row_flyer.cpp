#include "row_flyer.h"

RowFlyer::RowFlyer(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction)
	: MovingObject(x, y, sign, foregroundColor, backgroundColor, direction)
{
	this->m_defaultX = x;
	this->m_defaultY = y;
}

void RowFlyer::Reset()
{
	this->m_x = this->m_defaultX;
	this->m_y = this->m_defaultY;
}