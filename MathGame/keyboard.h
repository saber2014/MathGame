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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "common.h"

#if !defined(_MSC_VER)
typedef void * HANDLE;
#endif

#define ASCII_COUNT 128

#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_LEFT 37
#define KEY_UP 38
#define KEY_RIGHT 39
#define KEY_DOWN 40

class Keyboard
{
private:
	HANDLE m_hStdIn;

public:
	Keyboard();
	~Keyboard();

	void Flush();
	list<char> GetInput();
};

#endif