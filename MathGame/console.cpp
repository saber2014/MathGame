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

#include "console.h"

Console::Console()
{
#if defined(_MSC_VER)
	this->m_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	this->m_foregroundColorDefault = this->GetForegroundColor();
	this->m_backgroundColorDefault = this->GetBackgroundColor();
#endif
}

Console::~Console()
{
#if defined(_MSC_VER)
	if (this->m_hStdOut)
		CloseHandle(this->m_hStdOut);
#endif
}

void Console::Clear()
{
#if defined(_MSC_VER)
	this->SetColor(CONSOLE_COLOR_DEFAULT, CONSOLE_COLOR_DEFAULT);
	system("cls");
#endif
}

void Console::SetTitle(char *pszTitle)
{
#if defined(_MSC_VER)
	SetConsoleTitleA(pszTitle);
#endif
}

void Console::ShowCursor(bool bShow)
{
#if defined(_MSC_VER)
	CONSOLE_CURSOR_INFO cci = {};
	GetConsoleCursorInfo(this->m_hStdOut, &cci);

	cci.bVisible = bShow;

	SetConsoleCursorInfo(this->m_hStdOut, &cci);
#endif
}

void Console::SetColor(CONSOLE_COLOR foregroundColor, CONSOLE_COLOR backgroundColor)
{
#if defined(_MSC_VER)
	if (foregroundColor == CONSOLE_COLOR_DEFAULT) foregroundColor = this->m_foregroundColorDefault;
	if (backgroundColor == CONSOLE_COLOR_DEFAULT) backgroundColor = this->m_backgroundColorDefault;

	SetConsoleTextAttribute(this->m_hStdOut, (backgroundColor << 4) | foregroundColor);
#endif
}

CONSOLE_COLOR Console::GetForegroundColor()
{
#if defined(_MSC_VER)
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return (CONSOLE_COLOR)(csbi.wAttributes & 0x0f);
#else
	return (CONSOLE_COLOR)CONSOLE_COLOR_DEFAULT;
#endif
}

CONSOLE_COLOR Console::GetBackgroundColor()
{
#if defined(_MSC_VER)
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return (CONSOLE_COLOR)((csbi.wAttributes & 0xf0) >> 4);
#else
	return (CONSOLE_COLOR)CONSOLE_COLOR_DEFAULT;
#endif
}

void Console::SetPosition(int nX, int nY)
{
#if defined(_MSC_VER)
	COORD coord = { nX, nY };
	SetConsoleCursorPosition(this->m_hStdOut, coord);
#endif
}

int Console::GetXPosition()
{
#if defined(_MSC_VER)
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);

	return csbi.dwCursorPosition.X;
#else
	return 0;
#endif
}

int Console::GetYPosition()
{
#if defined(_MSC_VER)
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(this->m_hStdOut, &csbi);
	
	return csbi.dwCursorPosition.Y;
#else
	return 0;
#endif
}

void Console::SetBufferSize(int nWidth, int nHeight)
{
#if defined(_MSC_VER)
	COORD coord = { nWidth, nHeight };
	SetConsoleScreenBufferSize(this->m_hStdOut, coord);
#endif
}

void Console::EnableWrap(bool bWrap)
{
#if defined(_MSC_VER)
	DWORD dwOldMode = 0;
	GetConsoleMode(this->m_hStdOut, &dwOldMode);

	if (bWrap) dwOldMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
	else dwOldMode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;

	SetConsoleMode(this->m_hStdOut, dwOldMode);
#endif
}

void Console::Wait(int nMilliseconds)
{
#if defined(_MSC_VER)
	Sleep(nMilliseconds);
#endif
}