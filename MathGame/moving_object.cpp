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

#include "moving_object.h"
#include "screen.h"

MovingObject::MovingObject(int x, int y, int sign, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor, OBJECT_MOVE direction)
{
	this->m_x = x;
	this->m_y = y;
	this->m_sign = sign;
	this->m_foregroundColor = foregroundColor;
	this->m_backgroundColor = backgroundColor;
	this->m_direction = direction;
}

void MovingObject::Clear()
{
	g_pScreen->SetAt(' ', this->m_x, this->m_y);

	char buf[2] = { ' ', 0 };
	g_pScreen->Print(buf, this->m_x, this->m_y, CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);
}

void MovingObject::Print()
{
	g_pScreen->SetAt(this->m_sign, this->m_x, this->m_y);

	char buf[2] = { this->m_sign, 0 };
	g_pScreen->Print(buf, this->m_x, this->m_y, this->m_foregroundColor, this->m_backgroundColor);
}

void MovingObject::SetDirection(OBJECT_MOVE direction)
{
	this->m_direction = direction;
}

bool MovingObject::IsPossibleToMove()
{
	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		if (g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y - 1)) != ' ')
			return false;
		break;

	case OBJECT_MOVE_RIGHT:
		if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x + 1), this->m_y) != ' ')
			return false;
		break;

	case OBJECT_MOVE_DOWN:
		if (g_pScreen->GetAt(this->m_x, g_pScreen->NormalizeGameY(this->m_y + 1)) != ' ')
			return false;
		break;

	case OBJECT_MOVE_LEFT:
		if (g_pScreen->GetAt(g_pScreen->NormalizeGameX(this->m_x - 1), this->m_y) != ' ')
			return false;
		break;
	}

	return true;
}

void MovingObject::Move()
{
	this->Clear();

	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		if (this->IsPossibleToMove())
			this->m_y = g_pScreen->NormalizeGameY(this->m_y - 1);
		break;

	case OBJECT_MOVE_RIGHT:
		if (this->IsPossibleToMove())
			this->m_x = g_pScreen->NormalizeGameX(this->m_x + 1);
		break;

	case OBJECT_MOVE_DOWN:
		if (this->IsPossibleToMove())
			this->m_y = g_pScreen->NormalizeGameY(this->m_y + 1);
		break;

	case OBJECT_MOVE_LEFT:
		if (this->IsPossibleToMove())
			this->m_x = g_pScreen->NormalizeGameX(this->m_x - 1);
		break;
	}

	this->Print();
}

int MovingObject::GetX()
{
	return this->m_x;
}

int MovingObject::GetY()
{
	return this->m_y;
}

int MovingObject::GetNextX()
{
	switch (this->m_direction)
	{
	case OBJECT_MOVE_RIGHT:
		return g_pScreen->NormalizeGameX(this->m_x + 1);
		break;

	case OBJECT_MOVE_LEFT:
		return g_pScreen->NormalizeGameX(this->m_x - 1);
		break;
	}

	return this->m_x;
}

int MovingObject::GetNextY()
{
	switch (this->m_direction)
	{
	case OBJECT_MOVE_UP:
		return g_pScreen->NormalizeGameY(this->m_y - 1);
		break;

	case OBJECT_MOVE_DOWN:
		return g_pScreen->NormalizeGameY(this->m_y + 1);
		break;
	}

	return this->m_y;
}

CONSOLE_COLOR MovingObject::GetForegroundColor()
{
	return this->m_foregroundColor;
}

CONSOLE_COLOR MovingObject::GetBackgroundColor()
{
	return this->m_backgroundColor;
}

OBJECT_MOVE MovingObject::GetDirection()
{
	return this->m_direction;
}