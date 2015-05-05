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

#include "keyboard.h"

Keyboard::Keyboard()
{
#if defined(_MSC_VER)
	this->m_hStdIn = GetStdHandle(STD_INPUT_HANDLE);
#endif
}

Keyboard::~Keyboard()
{
#if defined(_MSC_VER)
	if (this->m_hStdIn)
		CloseHandle(this->m_hStdIn);
#endif
}

void Keyboard::Flush()
{
#if defined(_MSC_VER)
	int nNumberOfEvents = 0;
	GetNumberOfConsoleInputEvents(this->m_hStdIn, (LPDWORD)&nNumberOfEvents);

	for (int i = 0; i < nNumberOfEvents; i++)
	{
		INPUT_RECORD buffer = {};
		DWORD nNumberOfEventsRead = 0;

		ReadConsoleInput(this->m_hStdIn, &buffer, 1, &nNumberOfEventsRead);
	}
#endif
}

list<char> Keyboard::GetInput()
{
#if defined(_MSC_VER)
	bool keys[ASCII_COUNT] = { false };

	int nNumberOfEvents = 0;
	GetNumberOfConsoleInputEvents(this->m_hStdIn, (LPDWORD)&nNumberOfEvents);

	for (int i = 0; i < nNumberOfEvents; i++)
	{
		INPUT_RECORD buffer = {};
		DWORD nNumberOfEventsRead = 0;

		ReadConsoleInput(this->m_hStdIn, &buffer, 1, &nNumberOfEventsRead);

		if (buffer.EventType == KEY_EVENT && buffer.Event.KeyEvent.bKeyDown == TRUE)
		{
			if (37 <= buffer.Event.KeyEvent.wVirtualKeyCode && buffer.Event.KeyEvent.wVirtualKeyCode <= 40)
			{
				if (0 <= buffer.Event.KeyEvent.wVirtualKeyCode && buffer.Event.KeyEvent.wVirtualKeyCode < ASCII_COUNT)
					keys[buffer.Event.KeyEvent.wVirtualKeyCode] = true;
			}
			else
			{
				if (0 <= buffer.Event.KeyEvent.uChar.AsciiChar && buffer.Event.KeyEvent.uChar.AsciiChar < ASCII_COUNT)
					keys[buffer.Event.KeyEvent.uChar.AsciiChar] = true;
			}
		}
	}

	list<char> list;

	for (int i = 0; i < ASCII_COUNT; i++)
	{
		if (keys[i])
			list.push_back(i);
	}
#else
	list <char> list;
#endif

	return list;
}