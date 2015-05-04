#ifndef COLUMN_FLYER_H
#define COLUMN_FLYER_H

#include "common.h"
#include "moving_object.h"

class ColumnFlyer : public MovingObject
{
private:
	int m_defaultX;
	int m_defaultY;

public:
	ColumnFlyer(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction);

	void Reset();
};

#endif