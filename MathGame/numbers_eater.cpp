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

#include "numbers_eater.h"
#include "screen.h"
#include "game_page.h"

NumbersEater::NumbersEater(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction)
	: MovingObject(x, y, sign, foregroundColor, backgroundColor, direction)
{
	this->m_defaultX = x;
	this->m_defaultY = y;
	this->m_killed = false;
}

void NumbersEater::Move(vector<GamePageNumber> &numbers)
{
	GamePageNumber gpn = this->FindClosestNumber(numbers);

	if (gpn.number == 0)
		this->m_direction = (OBJECT_MOVE)(1 + rand() % 4);
	else
	{
		int r = rand() % 2;

		if (r == 1 && this->m_x == gpn.x) r = 0;
		if (r == 0 && this->m_y == gpn.y) r = 1;

		if (r)
		{
			if (this->m_x - gpn.x > 0)
			{
				int dist1 = this->m_x - gpn.x;
				int dist2 = (WIDTH - this->m_y) + gpn.x;

				if (dist1 < dist2)
					this->m_direction = OBJECT_MOVE_LEFT;
				else
					this->m_direction = OBJECT_MOVE_RIGHT;
			}
			else
			{
				int dist1 = gpn.x - this->m_x;
				int dist2 = (WIDTH - gpn.x) + this->m_x;

				if (dist1 < dist2)
					this->m_direction = OBJECT_MOVE_RIGHT;
				else
					this->m_direction = OBJECT_MOVE_LEFT;
			}
		}
		else
		{
			if (this->m_y - gpn.y > 0)
			{
				int dist1 = this->m_y - gpn.y;
				int dist2 = (HEIGHT - this->m_y) + gpn.y;

				if (dist1 < dist2)
					this->m_direction = OBJECT_MOVE_UP;
				else
					this->m_direction = OBJECT_MOVE_DOWN;
			}
			else
			{
				int dist1 = gpn.y - this->m_y;
				int dist2 = (HEIGHT - gpn.y) + this->m_y;

				if (dist1 < dist2)
					this->m_direction = OBJECT_MOVE_DOWN;
				else
					this->m_direction = OBJECT_MOVE_UP;
			}
		}
	}

	MovingObject::Move();
}

bool NumbersEater::IsKilled()
{
	return this->m_killed;
}

void NumbersEater::Kill()
{
	this->m_killed = true;
	this->Clear();
}

void NumbersEater::Reset()
{
	this->m_x = this->m_defaultX;
	this->m_y = this->m_defaultY;
	this->m_direction = OBJECT_MOVE_DEFAULT;
	this->m_killed = false;
}

GamePageNumber NumbersEater::FindClosestNumber(vector<GamePageNumber> &numbers)
{
	if (numbers.size() == 0)
	{
		GamePageNumber gpn = { 0, 0, 0 };
		return gpn;
	}

	int min_dist = INT_MAX;
	int min_dist_index = 0;

	int current_number = 0;

	for (vector<GamePageNumber>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		int dx = this->m_x - it->x;
		int dy = this-> m_y - it->y;
		int dist = (int)sqrt((double)(dx * dx + dy * dy));

		if (dist <= min_dist)
		{
			min_dist = dist;
			min_dist_index = current_number;
		}

		current_number++;
	}

	return numbers.at(min_dist_index);
}