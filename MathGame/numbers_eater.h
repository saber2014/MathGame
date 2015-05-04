#ifndef NUMBERS_EATER_H
#define NUMBERS_EATER_H

#include "common.h"
#include "moving_object.h"

struct GamePageNumber;

class NumbersEater : public MovingObject
{
private:
	int m_defaultX;
	int m_defaultY;
	bool m_killed;

public:
	NumbersEater(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction);

	void Move(vector<GamePageNumber> &numbers);

	bool IsKilled();
	void Kill();
	void Reset();
	GamePageNumber FindClosestNumber(vector<GamePageNumber> &numbers);
};

#endif