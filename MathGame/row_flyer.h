#ifndef ROW_FLYER_H
#define ROW_FLUER_H

#include "common.h"
#include "moving_object.h"

class RowFlyer : public MovingObject
{
private:
	int m_defaultX;
	int m_defaultY;

public:
	RowFlyer(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction);

	void Reset();
};

#endif