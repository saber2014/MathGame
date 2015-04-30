#ifndef SHOT_H
#define SHOT_H

#include "common.h"
#include "moving_object.h"

enum OBJECT_TYPE;

class Shot : public MovingObject
{
private:
	float m_lastMove;

public:
	Shot(int x, int y, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction, float count);

	void Move(float count);

	float GetLastMove();
	OBJECT_TYPE GetBlockingObject();
};

#endif