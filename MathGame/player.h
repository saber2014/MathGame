#ifndef PLAYER_H
#define PLAYER_H

enum CONSOLE_COLOR;

enum PLAYER_MOVE
{
	PLAYER_MOVE_UP = 1,
	PLAYER_MOVE_RIGHT,
	PLAYER_MOVE_DOWN,
	PLAYER_MOVE_LEFT
};

class Player
{
private:
	int m_points;
	int m_attempts;

	int m_x;
	int m_y;
	char m_sign;
	CONSOLE_COLOR m_foregroundColor;
	CONSOLE_COLOR m_backgroundColor;
	PLAYER_MOVE m_direction;

public:
	Player(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, PLAYER_MOVE direction);

	int GetPoints();
	int GetAttempts();
	void SetDirection(PLAYER_MOVE direction);
	void Print();

	void Clear();
	void Move();
};

#endif