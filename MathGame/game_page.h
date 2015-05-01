#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include "common.h"
#include "page.h"
#include "player.h"
#include "exercise.h"

#define ADD_SHOT_TIME 200
#define GENERATE_NUMBER_TIME 10
#define TRANSITION_WAIT_TIME 30

class GamePage : public Page
{
private:
	int m_level;
	float m_counter;
	Player m_player1;
	Player m_player2;
	Exercise m_exercise1;
	Exercise m_exercise2;

public:
	GamePage(int level);

	char *GetName();
	void Print();
	void KeyEvent(char key);

	void PrintPlayerHeader(int player);
	void PrintCounter();
	void PrintExercises();
	void PrintHeader();
	int GetNumberAt(int x, int y);
	Shot *GetShotAt(int x, int y);
	void MoveShots(list<Shot> &shotsList);
	void RemoveNumber(int x, int y);
	void RemoveShot(int x, int y);
	void RemoveObject(int x, int y);
	void GenerateNumber();
	void HalfTick();
	void Tick();
	void Reset();
	void PlayTransition();
};

#endif