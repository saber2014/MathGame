#ifndef GAME_PAGE_H
#define GAME_PAGE_H

#include "common.h"
#include "page.h"
#include "player.h"
#include "exercise.h"
#include "numbers_eater.h"

#define TIME_IS_OVER_TIME 1500
#define ADD_SHOT_TIME 200
#define GENERATE_NUMBER_TIME 10
#define TRANSITION_WAIT_TIME 30

enum MANAGER_CALLBACK;
class Manager;

struct GamePageNumber
{
	int x;
	int y;
	int number;
};

class GamePage : public Page
{
private:
	int m_level;
	float m_counter;
	Player m_player1;
	Player m_player2;
	Exercise m_exercise1;
	Exercise m_exercise2;
	NumbersEater m_numbersEater1;
	NumbersEater m_numbersEater2;
	vector<GamePageNumber> m_numbers;

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
	void Tick(Manager *pManager);
	void Reset(Manager *pManager);
	void PlayTransition();
	void Kill(int player);
};

#endif