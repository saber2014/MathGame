#ifndef SHOT_H
#define SHOT_H

#include "common.h"
#include "moving_object.h"

enum BLOCKING_OBJECT
{
	BLOCKING_OBJECT_NONE = 0,
	BLOCKING_OBJECT_PLAYER1,
	BLOCKING_OBJECT_PLAYER2,
	BLOCKING_OBJECT_NUMBER,
	BLOCKING_OBJECT_SHOT
};

class Shot : public MovingObject
{
private:
	float m_lastMove;

public:
	Shot(int x, int y, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction, float count);

	void Move(float count);

	float GetLastMove();
	BLOCKING_OBJECT GetBlockingObject();
};

#endif