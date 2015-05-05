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

#ifndef CONSOLE_H
#define CONSOLE_H

#include "common.h"

#if !defined(_MSC_VER)
typedef void * HANDLE;
#endif

class Console
{
private:
	HANDLE m_hStdOut;
	CONSOLE_COLOR m_foregroundColorDefault;
	CONSOLE_COLOR m_backgroundColorDefault;

public:
	Console();
	~Console();

	void Clear();
	void SetTitle(char *pszTitle);
	void ShowCursor(bool bShow);
	void SetColor(CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor);
	CONSOLE_COLOR GetForegroundColor();
	CONSOLE_COLOR GetBackgroundColor();
	void SetPosition(int nX, int nY);
	int GetXPosition();
	int GetYPosition();
	void SetBufferSize(int nWidth, int nHeight);
	void EnableWrap(bool bWrap);
	void Wait(int nMilliseconds);
};

#endif