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

#ifndef COMMON_H
#define COMMON_H

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include <math.h>
#include <string.h>
#include <time.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

#define	WIDTH 80
#define	HEIGHT 25

#define WAIT_TIME 100
#define GAME_WAIT_TIME 200
#define MESSAGE_WAIT_TIME 2000

#include "enums.h"

extern class Console *g_pConsole;
extern class Screen *g_pScreen;
extern class Keyboard *g_pKeyboard;

CONSOLE_COLOR GetStylizedForeground(SCREEN_MESSAGE_STYLE style);
CONSOLE_COLOR GetStylizedBackground(SCREEN_MESSAGE_STYLE style);
void OutputDebugMessage(char *message);

#endif