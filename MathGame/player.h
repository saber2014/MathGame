#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "moving_object.h"
#include "shot.h"

class Player : public MovingObject
{
private:
	CONSOLE_COLOR m_shotColor;
	int m_defaultX;
	int m_defaultY;
	OBJECT_MOVE m_defaultDirection;
	bool m_killed;
	int m_points;
	int m_attempts;
	int m_shots;
	list<Shot> m_shotsList;

public:
	Player(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction, CONSOLE_COLOR shotColor);

	bool IsKilled();
	int GetPoints();
	int GetAttempts();
	int GetShots();
	list<Shot> &GetShotsList();
	void AddShot();
	void Shoot(float count);
	void Kill();
};

#endif