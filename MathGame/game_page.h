#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "common.h"
#include "page.h"
#include "player.h"

class GamePage : public Page
{
private:
	int m_level;
	int m_counter;
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
	void MoveShots(list<Shot> &shotsList);
	void HalfTick();
	void Tick();
};

#endif