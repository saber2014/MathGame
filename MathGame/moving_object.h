#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "common.h"

enum CONSOLE_COLOR;

enum OBJECT_MOVE
{
	OBJECT_MOVE_UP = 1,
	OBJECT_MOVE_RIGHT,
	OBJECT_MOVE_DOWN,
	OBJECT_MOVE_LEFT
};

class MovingObject
{
protected:
	int m_x;
	int m_y;
	char m_sign;
	CONSOLE_COLOR m_foregroundColor;
	CONSOLE_COLOR m_backgroundColor;
	OBJECT_MOVE m_direction;

public:
	MovingObject(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction);

	void Clear();
	void Print();
	void SetDirection(OBJECT_MOVE direction);
	bool IsPossibleToMove();
	void Move();
	int GetX();
	int GetY();
	int GetNextX();
	int GetNextY();
	CONSOLE_COLOR GetForegroundColor();
	CONSOLE_COLOR GetBackgroundColor();
	OBJECT_MOVE GetDirection();
};

#endif