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