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

#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"
#include "console.h"

class Screen
{
private:
	char m_ppScreen[HEIGHT][WIDTH];

public:
	Screen();
	~Screen();

	int NormalizeX(int nX);
	int NormalizeGameX(int nX);
	int NormalizeY(int nY);
	int NormalizeGameY(int nY);
	void Print(char *pszText, int nX, int nY, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	void PrintAligned(char *pszText, int align, CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	void SetAt(char ch, int nX, int nY);
	char GetAt(int nX, int nY);
	void PrintMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style);
	void PrintBottomMessage(char *pszMessage, SCREEN_MESSAGE_STYLE style);
	OBJECT_TYPE GetObjectAt(int x, int y);
	void Clear();
	void PrintScreenWithNumbers();
};

#endif