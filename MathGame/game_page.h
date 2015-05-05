/*
 * MathGame - a competitive math game
 * Copyright (C) 2015  saber2014
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef GAME_PAGE_H
#define GAME_PAGE_H

#include "common.h"
#include "page.h"
#include "player.h"
#include "exercise.h"
#include "numbers_eater.h"
#include "row_flyer.h"
#include "column_flyer.h"

#define TIME_IS_OVER_TIME 1500
#define ADD_SHOT_TIME 200
#define GENERATE_NUMBER_TIME 10
#define TRANSITION_WAIT_TIME 30

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
	RowFlyer m_rowFlyer1;
	RowFlyer m_rowFlyer2;
	ColumnFlyer m_columnFlyer1;
	ColumnFlyer m_columnFlyer2;
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
	int GetLevel();
	int GetPlayerPoints(int player);
	int GetNumberAt(int x, int y);
	Shot *GetShotAt(int x, int y);
	void SetPlayerPoints(int player, int points);
	void MoveShots(list<Shot> &shotsList);
	void RemoveNumber(int x, int y);
	void RemoveShot(int x, int y);
	void RemoveNumbersEater(int x, int y);
	void RemoveObject(int x, int y);
	void GenerateNumber();
	void HalfTick();
	void Tick(Manager *pManager);
	void Reset(Manager *pManager);
	void PlayTransition();
	void Kill(int player);
};

#endif