#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "common.h"
#include "page.h"
#include "player.h"

#define ADD_SHOT_TIME 200
#define GENERATE_NUMBER_TIME 10

class GamePage : public Page
{
private:
	int m_level;
	float m_counter;
	Player m_player1;
	Player m_player2;

public:
	GamePage();

	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintPlayerHeader(int player);
	void PrintCounter();
	void PrintHeader();
	Shot &GetShotAt(int x, int y);
	void MoveShots(list<Shot> &shotsList);
	void RemoveShot(int x, int y);
	void RemoveObject(int x, int y);
	void GenerateNumber();
	void HalfTick();
	void Tick();
};

#endif